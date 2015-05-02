#include <stdlib.h>
#include "q.h"



void start_thread(void (*function)(void))
{ // begin pseudo code
  //   allocate a stack (via malloc) of a certain size (choose 8192)
    void *pStack = malloc(8192);
  //   allocate a TCB (via malloc)
    TCB_t *tcb = (TCB_t*)malloc(sizeof(TCB_t));
  //   call init_TCB with appropriate arguments
    init_TCB(tcb,function,pStack,8192);
  //   call addQ to add this TCB into the “RunQ” which is a global header pointer
    AddQueue(RunQ,tcb);
  //end pseudo code
}

void run()
{
    ucontext_t parent;     // get a place to store the main context, for faking
    getcontext(&parent);   // magic sauce
    swapcontext(&parent, &(RunQ->head->context));  // start the first thread
}


void yield() // similar to run
{
	ucontext_t parent;
	getcontext(&parent); //Save to parent
	RunQ->head->context = parent; // Save current state before context switch to the next thread */
	RotateQ(RunQ);//rotate the run Q;
	swapcontext(&parent, &(RunQ->head->context));    
   	//swap the context, from previous thread to the thread pointed to by RunQ
}
