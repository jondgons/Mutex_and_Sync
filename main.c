/*Name: Cody Gonsowski
 *Date: 02/18/2020
 *File: main.c
 *Desc: Main driver of the multithreaded mutex & synchronization bank demo program.
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

//GLOBAL DECLARATION
#define THREAD_COUNT 4 //number of threads to be run
#define STARTING_BALANCE 100 //initial balance

int balance = STARTING_BALANCE; //global balance for thread accessibility

//thread information
typedef struct{
  int id;
} parameters;

//FUNCTION DECLARATION
void* withdraw(void* tid);
void* deposit(void* tid);
parameters* threadParameters(int id);

//MAIN
int main(int argc, char* argv[]){
  //thread initialization
  pthread_t threads[THREAD_COUNT];
  for (int i = 0; i < THREAD_COUNT; i++){
    if (i % 2 == 1){ //on odds, withdraw
      pthread_create(&threads[i], NULL, withdraw, threadParameters(i));
    }
    else { //on evens, deposit
      pthread_create(&threads[i], NULL, deposit, threadParameters(i));
    }
  }

  //join threads so they don't stop early
  for (int i = 0; i < THREAD_COUNT; i++){
    pthread_join(threads[i], NULL);
  }

  printf("Original balance: %d", STARTING_BALANCE);
  printf("New balance: %d", balance);
}

//FUNCTION IMPLEMENTATION
//UNFINISHED - mutex & sync
void* withdraw(void* tid){
  for (int i = 0; i < 10; i++){
    int readbalance = balance;
    
    printf("At time %d, the balance for withdrawal thread %p is %d", i, tid, balance);
    readbalance -= 10;
    usleep(1);
    
    balance = readbalance;
    printf("At time %d, the balance after withdrawal thread %p is %d", i, tid, balance);
    usleep(1);
  }

  return 0;
}
//UNFINISHED - mutex & sync
void* deposit(void* tid){
  for (int i = 0; i < 10; i++){
    int readbalance = balance;
    
    printf("At time %d, the balance before depositing thread %p is %d", i, tid, balance);
    readbalance += 11;
    usleep(10);
    
    balance = readbalance;
    printf("At time %d, the balance after depositing thread %p is %d", i, tid, balance);
    usleep(10);
  }

  return 0;
}

parameters* threadParameters(int tid){
  parameters* data = (parameters*) malloc(sizeof(parameters));

  //assign data values to thread
  data->id = tid;

  return data;
}
