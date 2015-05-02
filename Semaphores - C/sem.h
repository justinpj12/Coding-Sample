#include "threads.h"
typedef struct semaphore_t{
	struct queue *SemQ;
	int count;
}semaphore_t;

void InitSem( semaphore_t* semaphore, int value)
{
	semaphore->SemQ = malloc(sizeof(semaphore->SemQ));	
	semaphore->count = value;
}

void P( semaphore_t* semaphore)
{
	TCB_t *blockedProcess;	
	semaphore->count--;
	if(semaphore->count < 0){
		blockedProcess = DelQueue(RunQ);
		AddQueue(semaphore->SemQ, blockedProcess);
		swapcontext(&blockedProcess->context, &RunQ->head->context);
	}
}

void V( semaphore_t* semaphore)
{
	TCB_t *readyProcess;	
	semaphore->count++;
	if(semaphore->count <= 0){
		readyProcess = DelQueue(semaphore->SemQ);		
		AddQueue(RunQ, readyProcess);
		yield();
	}
}
