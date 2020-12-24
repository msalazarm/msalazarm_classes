/*
Name: Marco Salazar
Date: 11/5/2020
Username for canvas: marcoams
Username for CS lab: msalazar

Purpose: To check how different process synchronization mechanisms work. With Pthreads and semaphores.
*/

#define _REENTRANT
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <semaphore.h>

/* key number */
#define SHMKEY ((key_t) 1497)

// Semaphores, space available to place characters
sem_t space;
// how many characters are ready to be read.
sem_t ready;
// only one thread per critical section.
sem_t mutex;

// function protottypes for the threads.
void *producer(void * arg);
void *consumer(void * arg);

// Struct to hold the shared circular buffer
typedef struct 
{
	char array[15];
} shared_mem;

shared_mem *buffer;

int main(){
  // 15 positions in the buffer, 0 characters to read right away
  sem_init(&space, 0, 15);
  sem_init(&ready, 0, 0);
  sem_init(&mutex, 0, 1);

	int shmid, pid1, pid2, ID, status;
	char *shmadd;
	shmadd = (char *) 0;

	// Creates and connects to a shared memory segment
	if ((shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
    	perror ("shmget");
      	exit (1);     
  	}
	if ((buffer = (shared_mem *) shmat(shmid, shmadd, 0)) == (shared_mem *) -1) {
      	perror ("shmat");
      	exit (0);
  	}

	// Initialize the shared memory to 0 in all places
  for(int val = 0; val < 15; val++){
    buffer->array[val] = 0;
  }

  pthread_t tid1[1]; //process id for producer
  pthread_t tid2[1]; //process id for consumer
  pthread_attr_t attr[1]; // attribute pointer array

  fflush(stdout);
  /* Required to schedule thread independently.*/
  pthread_attr_init(&attr[0]);
  pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);
  /* end to schedule thread independently */

  /* Create the threads */
  pthread_create(&tid1[0], &attr[0], producer, NULL);
  pthread_create(&tid2[0], &attr[0], consumer, NULL);

  /* Wait for the threads to finish */
  pthread_join(tid1[0], NULL);
  pthread_join(tid2[0], NULL);

	// Detaching the Shared Memory.
	if(shmdt(buffer) == -1){
		perror("shmdt");
		exit(-1);
	}
	shmctl(shmid, IPC_RMID, NULL);

  // Destroy the semaphores
  sem_destroy(&space);
  sem_destroy(&ready);
  sem_destroy(&mutex);

  // terminate threads
  pthread_exit(NULL);

	return 0;
}

// function for producer to read items into the buffer
void *producer(void * arg){
  // position that should next be filled
  int point = 0;
	char nextChar;
  FILE* fp;
  fp = fopen("mytest.dat", "r");
  // while there is characters to read
  while(fscanf(fp,"%c",&nextChar) != EOF){
    // if there is space put in a character
    sem_wait(&space);

    sem_wait(&mutex);
    buffer->array[point] = nextChar; 
    // circular buffer array
    point = (point + 1) % 15;
    sem_post(&mutex);

    // there is a chracter available to be read
    sem_post(&ready);
  }

  // at end of file put in the end of buffer * character.
  sem_wait(&space);
  sem_wait(&mutex);
  buffer->array[point] = '*'; 
  sem_post(&mutex);
  sem_post(&ready);
  fclose(fp);
}

// function for consumer to print items from the buffer
void *consumer(void * arg){
  // position that should next be read
	int point = 0;
  char current;
  while(true){
    // if there are characters available to read, then print them out
    sem_wait(&ready);

    sem_wait(&mutex);
    // save current character
    current = buffer->array[point];

    // if the star character indicates end of buffer, then exit
    if(current == '*'){
      sem_post(&mutex);
      sem_post(&space);
      break;
    }
    printf("%c", current); 
    point = (point + 1) % 15;
    sem_post(&mutex);

    sem_post(&space);
    /*
    according to https://stackoverflow.com/questions/338273/why-does-printf-not-print-anything-before-sleep
    the buffer isn't flushed by the time sleep is called, so without fflush(stdout),
    nothing will be printed.
    */
    fflush(stdout);
    sleep(1);
  }
}