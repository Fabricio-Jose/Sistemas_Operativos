#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <signal.h> 
#include <string.h>
#include <setjmp.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <fcntl.h>   
#include <sys/wait.h> 
#include <stdint.h> 
#include <inttypes.h>
#include <math.h>

#define BUFSIZE 14

struct region
{
    int in;
    int out;
    int buffer[BUFSIZE];        // Guarda el PID del proceso
};

jmp_buf env; // for saving longjmp environment
int count = 0;


void handler(int sig, siginfo_t *siginfo, void *context){ 
    siginfo->si_pid=getpid();
    printf("Handler: Signal number=%d; Signal code=%d; errno value=%d; Sending process ID PID=%d\n",
           siginfo->si_signo, siginfo->si_code ,siginfo->si_errno, siginfo->si_pid);
    count++;
    if (count >= 1) 
        longjmp(env, 1234);
}

void BAD()
{
    int *ip = 0;
    printf("in BAD(): try to dereference NULL pointer\n");
    *ip = 123; // dereference a NULL pointer
    printf("should not see this line\n");
}

int main(int argc, char *argv[]){ 

    struct region *rptr;        // Puntero a estructura region
    int fd;

    int pid;                    // PID de un proceso
    int i, item;                // Item hijo

    /*      Creaccion memoria compartida     */
    fd=shm_open("/myregion", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if(fd==-1)
	{
		printf("Map failed\n");
		return -1;
	}

	if(ftruncate(fd, sizeof(struct region)) == 1)
	{
		printf("Map failed\n");
		return -1;
	}

    /*      Map de memoria compartida     */
	rptr=mmap(NULL, sizeof(struct region), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(rptr == MAP_FAILED)
	{
		printf("Map failed\n");
		return -1;
	}

    rptr->in = 0;
    rptr->out = 0; 

    for(int i=0; i<14; i++){        // 14 senhales 
        item = rptr->buffer[rptr->out];
        printf("%d\n", item);

        /**     Sigaction   **/
        int r;
        struct sigaction act;
        memset(&act, 0, sizeof(act));
        act.sa_sigaction = &handler;
        act.sa_flags = item;
        sigaction(item, &act, NULL); 


        if ((r = setjmp(env)) == 0) // call setjmp(env)
            BAD(); 
        else
            printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
        /**    Sigaction   **/

        rptr->out = (rptr->out+1)%BUFSIZE;

    }
    
    return 0;
}
/*---------------------------------------------*/

            /* PRUEBAS FALLIDAS: */
            
/*---------------------------------------------*/

/*#include <stdio.h>

int main()
{
    printf("hola\n");
}*/

//#include <sys/siginfo.h> 
/*static void hdl (int sig, siginfo_t *siginfo, void *context) { 
printf ("Sending PID: %ld, UID: %ld\n",(long)siginfo->si_pid, (long)siginfo->si_uid); 
}
int main (int argc, char *argv[]) {
        printf("entraaa crj T_T");

    struct sigaction act;
    memset (&act, 0, sizeof(act));
    act.sa_sigaction = &hdl;
    act.sa_flags = SA_SIGINFO;
    if (sigaction(SIGTERM, &act, NULL) < 0) {
        perror ("sigaction");
        return 1;
        
    }
    while (1)
        sleep (10);
    return 0;
}*/
/*
static int exit_flag = 0; 
static void hdl (int sig){ 
    exit_flag = 1;     
} 
int main (int argc, char *argv[]){ 
    struct sigaction act;  
    memset (&act, '\0', sizeof(act)); 
    act.sa_handler = &hdl;   
    if (sigaction(SIGTERM, &act, NULL) < 0) {  
        perror ("sigaction");      
        return 1;       }   
        while (!exit_flag)  
            ;   
return 0; }

*/
/*
jmp_buf env; // for saving longjmp environment
int count = 0;

void handler(int sig, siginfo_t *siginfo, void *context)
{ siginfo->si_pid=getpid();
    printf("handler: from PID=%d ; SIGNO=%d ; CODE=%d Errno=%d count=%d\n",
           siginfo->si_pid, siginfo->si_signo, siginfo->si_code ,siginfo->si_errno,            ++count);
    if (count >= 4) // let it occur up to 4 times
        longjmp(env, 1234);
}

void BAD()
{
    int *ip = 0;
    printf("in BAD(): try to dereference NULL pointer\n");
    *ip = 123; // dereference a NULL pointer
    printf("should not see this line\n");
}

int main(int argc, char *argv[])
{  // printf("here pir=%d y su padre = %d",getpid(),getppid());
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL); // install SIGSEGV catcher 

    //sigaction(SIGHUP, &act, NULL); // install SIGSEGV catcher 

    //sigaction(SIGINT, &act, NULL); // install SIGSEGV catcher 

    //sigaction(SIGTSTP, &act, NULL); // install SIGSEGV catcher 
    /*act.sa_flags =0;
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaction(SIGTERM, &act, NULL); // install SIGSEGV catcher 
    act.sa_mask = mask;
    pause();*/
   // if ((r = setjmp(env)) == 0) // call setjmp(env)
     //   BAD(); 
    
    // call BAD()
  //  else 
    //    printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
    
    //printf("proc %d looping\n", getpid());
    //while (1)
      //  ;
    
    /*struct sigaction act2;
    memset(&act2, 0, sizeof(act2));
    act2.sa_sigaction = &handler;
    act2.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act2, NULL); // install SIGSEGV catcher */

    //sigaction(SIGHUP, &act, NULL); // install SIGSEGV catcher 

    //sigaction(SIGINT, &act, NULL); // install SIGSEGV catcher 

    //sigaction(SIGTSTP, &act, NULL); // install SIGSEGV catcher 
    /*act.sa_flags =0;
    
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGTERM);
    sigaction(SIGTERM, &act, NULL); // install SIGSEGV catcher 
    act.sa_mask = mask;
    pause();*/
    /*--------------------------------------------------------*/
    /*if ((r = setjmp(env)) == 0) // call setjmp(env)
        BAD(); 
    
    // call BAD()
    else 
        printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
    
    printf("proc %d looping\n", getpid());*/
    
  //  return 0;
//}

