/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the producer process that writes to the shared memory region.
 *
 * Figure 3.16
 * 
 * To compile, enter
 * 	gcc shm-posix-producer.c -lrt
 *
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <stdio.h>
#include <stdlib.h> 
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <time.h>

#include <stdbool.h>

#include <sys/time.h> 
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h> 

#define BUFFER_SIZE 10000

typedef struct region{
	int in;
    int buffer[BUFFER_SIZE];
}estructura;

int main()
{
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    
    int out = 0;
    pid_t pid;
    pid_t padre;
    int pidP;
    int duration;

        
	const char *name = "OS";

    estructura *rptr;
    int fd;
    
    fd = shm_open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);//0666);
	if (fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}
	if(ftruncate(fd, sizeof(struct region))==-1){
        printf("struct failed\n");
		return -1;
    }

   	rptr = mmap(NULL,sizeof(struct region),PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	rptr->in=0;

    padre = getpid();
	//printf("Referencia: %d \n", pidP);

      while(1){
		pid = fork();
   		//pidP = getpid();

        sleep(5);
        /*if(pid==0){
            sleep(5);
            while (((rptr->in+1)%BUFFER_SIZE) == out)  ;
            rptr->buffer[rptr->in] = pid;
			printf("[%s] P(%d): Creando Proceso %d (hora)\n", output, padre,rptr->buffer[rptr->in]);
            sleep(5);
			rptr->in = (rptr->in+1)%BUFFER_SIZE;
        }else{
            			sleep(5);
            while (((rptr->in+1)%BUFFER_SIZE) == out) /* do nothing!  ;
            rptr->buffer[rptr->in] = pid;
			printf("[%s] P(%d): Creando Proceso %d (hora)\n", output, padre,rptr->buffer[rptr->in]);
            sleep(5);
			rptr->in = (rptr->in+1)%BUFFER_SIZE;
        }*/

		if(pid>0){
			sleep(5);
            while (((rptr->in+1)%BUFFER_SIZE) == out) /* do nothing! */ ;
            rptr->buffer[rptr->in] = pid;
			printf("[%s] P(%d): Creando Proceso %d (hora)\n", output, padre,rptr->buffer[rptr->in]);
            sleep(5);
			rptr->in = (rptr->in+1)%BUFFER_SIZE;
		}else{
            sleep(5);
            while (((rptr->in+1)%BUFFER_SIZE) == out) /* do nothing! */ ;
            rptr->buffer[rptr->in] = pid;
			printf("[%s] P(%d): Creando Proceso %d (hora)\n", output, padre,rptr->buffer[rptr->in]);
            sleep(5);
			rptr->in = (rptr->in+1)%BUFFER_SIZE;
        }
		
		//sleep(0);
        //shm_unlink(name); -< Cierra proceso en consumer
	}

    
  
/*  item next_produced;
    
    printf("Struct PID = %d \n",getpid());
    
    pidC=fork();
    
    printf("Fork Father PID = %d , Son pidC=%d \n",getpid(),pidC);
*/
	return 0;
}
