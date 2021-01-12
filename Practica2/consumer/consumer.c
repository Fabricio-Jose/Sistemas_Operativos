/**
 * Simple program demonstrating shared memory in POSIX systems.
 *
 * This is the consumer process
 *
 * Figure 3.18
 *
 * To compile, enter
 *	gcc shm-posix-consumer.c -lrt
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts - Tenth Edition
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
#include <stdbool.h>

#include <time.h>
#include <sys/time.h> 
#include <signal.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <stddef.h>

#define BUFFER_SIZE 10000

 typedef struct region{
	int in;
    int buffer[BUFFER_SIZE];
}Seg;

int main()
{
    
    time_t tiempo = time(0);
    struct tm *tlocal = localtime(&tiempo);
    char output[128];
    strftime(output,128,"%d/%m/%y %H:%M:%S",tlocal);
    //printf("%s\n",output);
        
    int out = 0;
    pid_t pid;
    int item;
    int duration;
    
	const char *name = "OS";

    Seg *rptr;
    int fd;

	fd = shm_open(name, O_RDONLY, S_IRUSR | S_IWUSR);//0666);
	if (fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

    rptr = mmap(NULL,sizeof(struct region), PROT_READ, MAP_SHARED, fd, 0);
	if (rptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}
    
	//rptr->in = 0;
	//rptr->out = 0;
    pid=rptr->buffer[out];
    
    while(1){
		//if(pid==0){
            //printf("valor de inf[%d]\n", out);//rptr->in);
            sleep(5);

			//while ((rptr->in) == rptr->out);

            item = rptr->buffer[out];//rptr->out];
            printf("[%s] C(%d) Matando Proceso %d (duracion)\n", output, item, item);//rptr->out);
            kill(item,SIGKILL);
            //rptr->out = ((rptr->out)+2)%BUFFER_SIZE;
            out=out+1;
            sleep(5);

		/*	rptr->buffer[rptr->in] = pid;
			printf("Producer produced %d in buf[%d]\n", rptr->buffer[rptr->in], rptr->in);
            sleep(5);
			rptr->in = (rptr->in+1)%BUFFER_SIZE;*/
		//}
	}
    
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
