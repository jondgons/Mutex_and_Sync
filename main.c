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

int balance = 0; //global balance for thread accessibility
int buffer = 0; //buffer between withdraw and deposit

//mutex and signaling
pthread_mutex_t mutex;
pthread_cond_t condw, condd;

//thread information
typedef struct{
  int tid;
} parameters;

//FUNCTION DECLARATION
void* withdraw(void* tid);
void* deposit(void* tid);
parameters* threadParameters(int id);

//MAIN
int main(int argc, char* argv[]){
  pthread_t threads[THREAD_COUNT];

  //mutex initialization
  pthread_mutex_init(&mutex, 0);
  pthread_cond_init(&condw, 0);
  pthread_cond_init(&condd, 0);

  //thread initialization
  for (int i = 0; i < THREAD_COUNT; i++){
    if (i % 2 == 1){ //on odds, withdraw
      pthread_create(&threads[i], 0, withdraw, threadParameters(i));
    }
    else { //on evens, deposit
      pthread_create(&threads[i], 0, deposit, threadParameters(i));
    }
  }

  //join threads so they don't stop early
  for (int i = 0; i < THREAD_COUNT; i++){
    pthread_join(threads[i], 0);
  }

  //cleaning up mutex
  pthread_cond_destroy(&condw);
  pthread_cond_destroy(&condd);
  pthread_mutex_destroy(&mutex);
}

//FUNCTION IMPLEMENTATION
void* withdraw(void* tid){
  for (int i = 0; i < 10; i++){
    //entering mutex
    pthread_mutex_lock(&mutex);
    while (buffer == 0) {
      pthread_cond_wait(&condw, &mutex);
    }

    //critical region
    buffer = 0;
    if (balance >= 10){ //if balance is NOT 10 or higher, no withdraw will occur
      int readbalance = balance;

      printf("At time %d, the balance for withdrawal thread %p is %d\n", i, tid, balance);
      readbalance -= 10;
    
      balance = readbalance;
      printf("At time %d, the balance after withdrawal thread %p is %d\n\n", i, tid, balance);
    }
    
    //leaving mutex
    pthread_cond_signal(&condd);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
  return 0;
}

void* deposit(void* tid){
  for (int i = 0; i < 10; i++){
    //entering mutex
    pthread_mutex_lock(&mutex);
    while (buffer != 0) {
      pthread_cond_wait(&condd, &mutex);
    }

    //critical region
    buffer = 1;
    int readbalance = balance;
    
    printf("At time %d, the balance before depositing thread %p is %d\n", i, tid, balance);
    readbalance += 11;
    
    balance = readbalance;
    printf("At time %d, the balance after depositing thread %p is %d\n\n", i, tid, balance);
    
    //leaving mutex
    pthread_cond_signal(&condw);
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(0);
  return 0;
}

parameters* threadParameters(int tid){
  parameters* data = (parameters*) malloc(sizeof(parameters));

  //assign data values to thread
  data->tid = tid;

  return data;
}
