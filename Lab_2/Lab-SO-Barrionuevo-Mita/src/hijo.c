#include <stdio.h>
#include <stdbool.h>
#include <sys/mman.h>
#include <sys/time.h> 
#include <fcntl.h>
#include <unistd.h>   
#include <stdlib.h>   
#include <sys/wait.h> 

#include <time.h> 
#include <sys/time.h> 
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
int main()
{
    struct region *rptr;        // Puntero a estructura region
    int fd;                     
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
    int a[]={11,11,3,4,6,8,9,11,13,14,15,17,19,20};
    for(int i=0;i<14;i++){
        rptr->buffer[rptr->in] = a[i];
        rptr->in = (rptr->in+1)%BUFSIZE; 
    }
    
    //FIN MEMORIA COMPARTIDA

    pid_t pidC;
    printf("** proc PID= %d comienza ihjo_0** \n",getpid());

    pidC = fork();
    
    

    if(pidC > 0){           //Se esta ejecutando el padre
        printf("** proc PID= %d comienza hijo_1** \n",getpid());
        int status;
        wait(&status);

    }
    else if(pidC == 0){     //Se esta ejecutando el hijo
        printf("** proc PID= %d comienza hijo_2** \n",getpid());
        
        /** lee el codigo del hijo.c */
        execlp ("./bin/nieto","", NULL);
		printf("Si ves esto, no se pudo ejecutar el programa nieto\n");
    }
    else{
        //si es -1 es error, el hijo no ha podido ser creado
    }
}
