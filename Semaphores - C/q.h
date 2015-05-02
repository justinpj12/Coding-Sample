#include <stdlib.h>
#include "tcb.h"

typedef struct queue{
	struct TCB_t *head;
}queue;

queue *RunQ;

//default constructor
TCB_t* NewItem(void)
{
    TCB_t* item = malloc(sizeof(struct TCB_t));
    item->next = NULL;
    item->prev = NULL;
    return item; // returns the new q TCB_t
}

void InitQueue(queue *q)
{
    q->head = NULL;
}

void AddQueue(queue *q, TCB_t *e)
{
    //empty queue
if( q == NULL){
	printf("Queue not found");
	return;
}
 else if(q->head == NULL)
    {
        q->head = e;
        e->next = e;
        e->prev = e;
        return;
    }
    else //more than one item
    {
        TCB_t *temp = q->head->prev;
        //insert e
        temp->next = e;
        e->prev = temp;
        e->next = q->head;
        q->head->prev = e;
        return;
    }

}

TCB_t* DelQueue(queue *q)
{
    TCB_t *temp;
    //empty list
    if(q->head == NULL)
    {
        return q->head;
    }
    //list items equal 1
    else if(q->head->next == q->head)
    {
        temp = q->head;
        q->head = NULL;
        return temp;
    }
    //list items more than 1
    else
    {
        temp = q->head;
        TCB_t *headPrev = q->head->prev;
        q->head = temp->next;
        q->head->prev = headPrev;
        headPrev->next = q->head;
        return temp;
    }
}

void RotateQ(queue *q)
{
	if( q->head == NULL) printf("Queue is Full");
	else    q->head = q->head->next;
}
