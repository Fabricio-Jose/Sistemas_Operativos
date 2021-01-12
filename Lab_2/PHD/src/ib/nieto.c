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

int n_env;

void handler(){
    printf("handler: from PID=%d ; SIGNO=%d ; CODE=%d Errno=%d count=%d\n",
           siginfo->si_pid, siginfo->si_signo, siginfo->si_code ,siginfo->si_errno, ++count);
    if(signum==SIGINT){
        cout<<"CONTROL SIGNAL IS PRESSED";
    }
    
}

/*void handler(int sig, siginfo_t *siginfo, void *context)
{ siginfo->si_pid=getpid();
    printf("handler: from PID=%d ; SIGNO=%d ; CODE=%d Errno=%d count=%d\n",
           siginfo->si_pid, siginfo->si_signo, siginfo->si_code ,siginfo->si_errno, ++count);
    if (count >= 4) // let it occur up to 4 times
        longjmp(env, 1234);
}

void BAD()
{
    int *ip = 0;
    printf("in BAD(): try to dereference NULL pointer\n");
    *ip = 123; // dereference a NULL pointer
    printf("should not see this line\n");
}*/

int main(int argc, char *argv[]){ 

    struct region *rptr;        // Puntero a estructura region
    int fd;

    int pid;                    // PID de un proceso
    int i, item;                // Item hijo
    int duration;               // Duracion para el sleep()

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

    for(int i=0; i<14; i++){
        item = rptr->buffer[rptr->out];
//		printf("digito = %d\n",rptr->buffer[rptr->out]);
        rptr->out = (rptr->out+1)%BUFSIZE;
    }


    //FIN MEMORIA COMPARTIDA
    
    
    
    struct sigaction sa;
    sa.sa_handler = handler;
    
    while(1){
        cerr<<"/";
        usleep(1000000);
        if(sigaction(SIGINT, & sa,NULL)==-1)
            perror("SIGACTION");
    }

    
/*
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    act.sa_sigaction = &handler;
    act.sa_flags = SA_SIGINFO;
    sigaction(SIGSEGV, &act, NULL); 


    if ((r = setjmp(env)) == 0) // call setjmp(env)
        BAD(); 
    

    else 
        printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
    
    printf("proc %d looping\n", getpid());*/

    
    return 0;
}
