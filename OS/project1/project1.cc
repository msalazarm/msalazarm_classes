/*
Name: Marco Salazar
Date: 10/4/2020
Username for canvas: marcoams
Username for CS lab: msalazar

Purpose: To check how shared memory is affected by concurrent processes, and it uses and problems.
*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

/* key number */
#define SHMKEY ((key_t) 1497)

// function protottypes.
void process1();
void process2();
void process3();
void process4();

// Struct to hold the shared memory
typedef struct 
{
	int value;
} shared_mem;

shared_mem *total;

int main(){
	int shmid, pid1, pid2, pid3, pid4, ID, status;
	char *shmadd;
	shmadd = (char *) 0;

	// Creates and connects to a shared memory segment
	if ((shmid = shmget(SHMKEY, sizeof(int), IPC_CREAT | 0666)) < 0)
    {
    	perror ("shmget");
      	exit (1);     
  	}
	if ((total = (shared_mem *) shmat(shmid, shmadd, 0)) == (shared_mem *) -1) {
      	perror ("shmat");
      	exit (0);
  	}

  	// Initialize the shared memory to 0
  	total->value = 0;

  	// forks and creates the new processes. Since they exit in the functions process#(), none of the children processes
  	// will ever execute the code in front of it. Only the parent process will.
  	if((pid1 = fork()) == 0) process1();
  	if((pid2 = fork()) == 0) process2();
  	if((pid3 = fork()) == 0) process3();
  	if((pid4 = fork()) == 0) process4();

  	// Wait for the processes to finish before outputting that they are done.
  	// I am waiting individually so that we can get a better sense of when a process is finished
  	// relative to the other children processes.
  	waitpid(pid1, NULL, 0);
  	printf("Child %d pid has just exited.\n", pid1);
  	waitpid(pid2, NULL, 0);
  	printf("Child %d pid has just exited.\n", pid2);
  	waitpid(pid3, NULL, 0);
  	printf("Child %d pid has just exited.\n", pid3);
  	waitpid(pid4, NULL, 0);
  	printf("Child %d pid has just exited.\n", pid4);

  	// Detaching the Shared Memory.
  	if(shmdt(total) == -1){
  		perror("shmdt");
  		exit(-1);
  	}
  	shmctl(shmid, IPC_RMID, NULL);


	return 0;
}

// function for process 1
void process1(){
	while(total->value < 100000){
		total->value = total->value+1;
	}
	printf("From Process 1: Counter = %d\n", total->value);	
	exit(1);
}

// function for process 2
void process2(){
	while(total->value < 200000){
		total->value = total->value+1;
	}
	printf("From Process 2: Counter = %d\n", total->value);	
	exit(1);
}

// function for process 3
void process3(){
	while(total->value < 300000){
		total->value = total->value+1;
	}
	printf("From Process 3: Counter = %d\n", total->value);	
	exit(1);
}

// function for process 4
void process4(){
	while(total->value < 500000){
		total->value = total->value+1;
	}
	printf("From Process 4: Counter = %d\n", total->value);	
	exit(1);
}