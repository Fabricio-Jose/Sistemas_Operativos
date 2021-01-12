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

item next produced;
while (true) {
// produce an item in next produced 
while (((in + 1) % BUFFER SIZE) == out)
; // do nothing 
buffer[in] = next produced;
in = (in + 1) % BUFFER SIZE;
}
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

int main()
{
	const int SIZE = 4096;
	const char *name = "OS";
	const char *message0= "Studying ";
	const char *message1= "Operating Systems ";
	const char *message2= "Is Fun!";

	int shm_fd;
	void *ptr;

	/* create the shared memory segment */
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

	/* configure the size of the shared memory segment */
	ftruncate(shm_fd,SIZE);

	/* now map the shared memory segment in the address space of the process */
	ptr = mmap(0,SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
	if (ptr == MAP_FAILED) {
		printf("Map failed\n");
		return -1;
	}

	/**
	 * Now write to the shared memory region.
 	 *
	 * Note we must increment the value of ptr after each write.
	 */
	sprintf(ptr,"%s",message0);
	ptr += strlen(message0);
	printf("Enviando mensage [%s] y durmiendo\n", message0);
	sleep(5);

	sprintf(ptr,"%s",message1);
	ptr += strlen(message1);
	printf("Enviando mensage [%s] y durmiendo\n", message1);
	sleep(5);

	sprintf(ptr,"%s",message2);
	printf("Enviando mensage [%s] y durmiendo\n", message2);
	ptr += strlen(message2);
	sleep(5);

	return 0;
}
