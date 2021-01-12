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





/*pid t pid;
int status;
pid = wait(&status);

#define BUFFER SIZE 10
typedef struct {
...
} item;
item buffer[BUFFER SIZE];
int in = 0;
int out = 0;

 
 
 item next consumed;
while (true) {
while (in == out)
//;  do nothing 
next consumed = buffer[out];
out = (out + 1) % BUFFER SIZE;
// consume the item in next consumed 
}*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <string.h>

int main()
{
	const char *name = "OS";
	const int SIZE = 4096;

	int shm_fd;
	void *ptr;
	int i;

	/* open the shared memory segment */
	shm_fd = shm_open(name, O_RDONLY, 0666);
	if (shm_fd == -1) {
		printf("shared memory failed\n");
		exit(-1);
	}

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		exit(-1);
	}

	/* now read from the shared memory region */
	printf("%s\n",(char *)ptr);
	sleep(5);

	printf("%s\n",(char *)ptr);
	sleep(5);

	printf("%s\n",(char *)ptr);
	sleep(5);

	/* remove the shared memory segment */
	if (shm_unlink(name) == -1) {
		printf("Error removing %s\n",name);
		exit(-1);
	}

	return 0;
}
