/*
Name: Marco Salazar and Catalina Sanchez-Maes
Date: 11/20/2020
Username for canvas: marcoams
                   :
Username for CS lab: msalazar
                   :

Description:
This program will print out the order that the monkeys leave in the form of L/R#: (#, #, #)
          Where L or R indicate whether the monkey is going left to right, or right to left respectively.
          Where the first number indicates which monkey it is, and the array of numbers indicates
          What monkeys were on the rope the moment before it left. If working correctly, the first
          number should be equal to the lowest nonzero number in the array next to it.
Note: The array position of the numbers in the array do not indicate the postion of the baboons on the rope. Only the values do.

Purpose: To Simulate the Monkey Baboon problem, making sure 
1. We must guarantee that once a baboon begins to cross that it reaches the other side
without meeting another baboon.
2. There should only be 3 Baboons on the rope at a time, and the order of them should be
preserved, such that it is a first in first out queue.
3. We should never permit them to be starvation for either side, such that there is a
continuous stream of baboons going one direction and not starving the other baboons on
the other side that want to travel.
4. We shall assume that all Baboons take the same amount of time to cross the rope.
5. This shall be implemented in C with the Pthreads library.
Catalina Sanchez-Maes Project 3 Proposal 11/2/2020
Marco Salazar
6. The rope will be represented with a Critical Section, and each baboon will be represented
with a thread that sleeps as long as it takes the baboon to cross the bridge.
7. The input to this program will be the time that each baboon takes to cross, and a text file
that contains the order of arrival for each monkey in the format “L,R,R,L,etc”.
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

// only one thread per critical section.
sem_t left2right;
sem_t right2left;
sem_t mutex;

// Struct to hold the rope buffer
typedef struct 
{
  char array[3];
} shared_rope;


shared_rope *rope;

// function protottypes for the threads.
void *leftbaboon(void * arg);
void *rightbaboon(void * arg);

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("Error, file not given.");
    exit(1);
  } else if(argc < 3){
    printf("Error, time for monkeys to cross not given.");
    exit(1);
  }
  //explanation statement
  printf("This program will print out the order that the monkeys leave in the form of L/R#: (#, #, #)\nWhere L or R indicate whether the monkey is going left to right, or right to left respectively.\nWhere the first number indicates which monkey it is, and the array of numbers indicates\nWhat monkeys were on the rope the moment before it left. If working correctly, the first\nnumber should be equal to the lowest nonzero number in the array next to it.\nNote: The array position of the numbers in the array do not indicate the postion of the baboons on the rope. Only the values do.\n\n");

  // mutex to protect the shared rope
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
  if ((rope = (shared_rope *) shmat(shmid, shmadd, 0)) == (shared_rope *) -1) {
        perror ("shmat");
        exit (0);
    }

  // Initialize the shared memory to 0 in all places which indicates no baboons are on the rope
  for(int val = 0; val < 3; val++){
    rope->array[val] = 0;
  }

  // each semaphore controls how many monkeys are traveling on the rope currently in each group
  // eg. left to right group, and right to left group.
  sem_init(&left2right, 0, 3);
  sem_init(&right2left, 0, 3);

  pthread_t tid[1]; //process id for every baboon, we
  pthread_attr_t attr[1]; // attribute pointer array

  fflush(stdout);
  /* Required to schedule thread independently.*/
  pthread_attr_init(&attr[0]);
  pthread_attr_setscope(&attr[0], PTHREAD_SCOPE_SYSTEM);
  /* end to schedule thread independently */

  // Variable to check how many monkeys of the other side are on the rope.
  // If onRope is 3, then each group would be able to put a monkey respectively.
  // that way if no one is on the rope a group would get 3, which is the go ahead to put a monkey.
  // however, if it is any number less than three then it must wait until it is three since that means
  // there are monkeys going the opposite direction.
  int onRope = 0;

  FILE* fp;
  fp = fopen(argv[1], "r");
  char nextChar;
  // while there is characters to read
  while(fscanf(fp,"%c",&nextChar) != EOF){
    // , are not important
    if(nextChar == ',') continue;
    if(nextChar == 'R'){
      // Loop until there are no monkeys going from left to right.
      while(1){
        sem_getvalue(&left2right, &onRope);
        if(onRope == 3) break;
      }

      // start a monkey going from right to left
      sem_wait(&right2left);
      pthread_create(&tid[0], &attr[0], rightbaboon, argv[2]);
    } else {
      // Loop until there are no monkeys going from right to left.
      while(1){
        sem_getvalue(&right2left, &onRope);
        if(onRope == 3) break;
      }

      // start a monkey going from left to right
      sem_wait(&left2right);
      pthread_create(&tid[0], &attr[0], leftbaboon, argv[2]);
    }
  }

  // Wait for the last baboon to cross.
  pthread_join(tid[0], NULL);
  printf("\n");

  // Detaching the Shared Memory.
  if(shmdt(rope) == -1){
    perror("shmdt");
    exit(-1);
  }
  shmctl(shmid, IPC_RMID, NULL);

  // Destroy the semaphores
  sem_destroy(&left2right);
  sem_destroy(&right2left);
  sem_destroy(&mutex);


  // terminate threads
  pthread_exit(NULL);

	return 0;
}

// function for a baboon going from left to right
void *leftbaboon(void * arg){
  // Put the baboon on the rope.
  sem_wait(&mutex);
  int max = 0;
  int available = 0;
  int val = 0;
  // determine the max value on the rope, and the position of the next 
  // available spot in the shared array to keep track of the baboons.
  for(int i = 0; i < 3; i++){
    val = rope->array[i];
    if(val > max) max = val;
    if(val == 0) available = i;
  }
  // Baboons ID becomes one greater than the last baboon.
  max = max + 1;
  //puts the baboon on the rope with one number bigger than the last baboon that is still on the rope.
  //otherwise it puts 1
  rope->array[available] = max;
  sem_post(&mutex);

  //cross the rope.
  sleep(atoi((char *) arg));

  // values to hold the second and third values of the baboons.
  // if they are 0 there is one less baboon.
  int secondvalue = -1;
  int thirdvalue = -1;

  // Loop to find out if this baboon can exit, FIFO order.
  while(1){
    secondvalue = -1;
    thirdvalue = -1;
    sem_wait(&mutex);

    // Get the first and second value for the other baboons.
    for(int i = 0; i < 3; i++){
      if(i == available) continue;
      if(secondvalue != -1){
        thirdvalue = rope->array[i];
        break;
      }
      secondvalue = rope->array[i];
    }

    // If there are no other baboons, then this baboon can exit
    if(secondvalue == 0 && thirdvalue == 0){
      rope->array[available] = 0;
      printf("L%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
      sem_post(&mutex);
      break;
    }

    if(secondvalue == 0){
      // If this baboon was on before the other baboon, he can exit.
      if(thirdvalue > max){
        rope->array[available] = 0;
        printf("L%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
        sem_post(&mutex);
        break;
      }
      // otherwise he must wait.
      sem_post(&mutex);
      continue;
    }
    if(thirdvalue == 0){
      // If this baboon was on before the other baboon, he can exit.
      if(secondvalue > max){
        rope->array[available] = 0;
        printf("L%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
        sem_post(&mutex);
        break;
      }
      // otherwise he must wait.
      sem_post(&mutex);
      continue;
    }

    // If this baboon was on before all the other baboons, he can now exit.
    if(max < secondvalue && max < thirdvalue){
      rope->array[available] = 0;
      printf("L%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
      sem_post(&mutex);
      break;
    }
    sem_post(&mutex);
  }

  fflush(stdout);
  sem_post(&left2right);
}

// function for a baboon going from right to left
void *rightbaboon(void * arg){
  // Put the baboon on the rope.
  sem_wait(&mutex);
  int max = 0;
  int available = 0;
  int val = 0;

  // determine the max value on the rope, and the position of the next 
  // available spot in the shared array to keep track of the baboons.
  for(int i = 0; i < 3; i++){
    val = rope->array[i];
    if(val > max) max = val;
    if(val == 0) available = i;
  }
  // Baboons ID becomes one greater than the last baboon.
  max = max + 1;
  //puts the baboon on the rope with one number bigger than the last baboon that is still on the rope.
  //otherwise it puts 1
  rope->array[available] = max;
  sem_post(&mutex);

  //cross the rope.
  sleep(atoi((char *) arg));

  // values to hold the second and third values of the baboons.
  // if they are 0 there is one less baboon.
  int secondvalue = -1;
  int thirdvalue = -1;

  // Loop to find out if this baboon can exit, FIFO order.
  while(1){
    secondvalue = -1;
    thirdvalue = -1;
    sem_wait(&mutex);

    // Get the first and second value for the other baboons.
    for(int i = 0; i < 3; i++){
      if(i == available) continue;
      if(secondvalue != -1){
        thirdvalue = rope->array[i];
        break;
      }
      secondvalue = rope->array[i];
    }

    // If there are no other baboons, then this baboon can exit
    if(secondvalue == 0 && thirdvalue == 0){
      rope->array[available] = 0;
      printf("R%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
      sem_post(&mutex);
      break;
    }

    if(secondvalue == 0){
      // If this baboon was on before the other baboon, he can exit.
      if(thirdvalue > max){
        rope->array[available] = 0;
        printf("R%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
        sem_post(&mutex);
        break;
      }
      // otherwise he must wait.
      sem_post(&mutex);
      continue;
    }
    if(thirdvalue == 0){
      // If this baboon was on before the other baboon, he can exit.
      if(secondvalue > max){
        rope->array[available] = 0;
        printf("R%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
        sem_post(&mutex);
        break;
      }
      // otherwise he must wait.
      sem_post(&mutex);
      continue;
    }

    // If this baboon was on before all the other baboons, he can now exit.
    if(max < secondvalue && max < thirdvalue){
      rope->array[available] = 0;
      printf("R%d:(%d %d %d)\n", max, max, secondvalue, thirdvalue);
      sem_post(&mutex);
      break;
    }
    sem_post(&mutex);
  }
  fflush(stdout);
  sem_post(&right2left);
}