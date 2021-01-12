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
void handler(int sig, siginfo_t *siginfo, void *context)
{   siginfo->si_pid=getpid();
    printf("handler: from PID=%d ; SIGNO=%d ; CODE=%d Errno=%d count=%d\n",
           siginfo->si_pid, siginfo->si_signo, siginfo->si_code ,siginfo->si_errno, ++count);
    if (count >= 4) // let it occur up to 4 times
        longjmp(env, 1234);
}

void sing(int signo){
    printf("imprime algo");
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
		//printf("digito = %d\n",rptr->buffer[rptr->out]);
        rptr->out = (rptr->out+1)%BUFSIZE;
    }
    //FIN MEMORIA COMPARTIDA
    int r;
    struct sigaction act;
    memset(&act, 0, sizeof(act));
    //act.sa_sigaction = &handler;
    act.sa_handler=sing;
    act.sa_flags = SA_SIGINFO;
    
    sigaction(SIGINT, &act, NULL); 
    sigaction(SIGINT, &act, NULL); 
    sigaction(SIGINT, &act, NULL); 
    
    printf("proceso no terminado");
    /*if ((r = setjmp(env)) == 0) // call setjmp(env)
        BAD(); 
    

    else 
        printf("proc %d survived SEGMENTATION FAULT: r=%d\n", getpid(), r);
    */

    
    return 0;
}
