/*
	CSE430 Spring 2015
	Programmers: Justin Jackson , Vanessa Averill-Edwards

*/

#include <string.h>
#include "sem.h"

//Method 1 variables
semaphore_t *mutex;
int global_var1 = 0;

//Method 2 - producer consumer variables
#define SHELF_MAX 5

int addIndex = 0;
int subIndex = 0;

int shelf[SHELF_MAX];

semaphore_t *empty;
semaphore_t *full;

void displayShelf(char* str);

//Method 1 functions
void function_One()
{
	int local1_fOne = 0;
	while(1){
		P(mutex);
		
		printf("Function One entered -\tGlobal 1: %d Local 1: %d \n",global_var1,local1_fOne);
		global_var1++;
		local1_fOne++;		
		sleep(2);
		V(mutex);
		printf("End Function One\n");
	}
}

void function_Two()
{
	int local1_fTwo = 0;
	while(1){
		printf("Function Two entered -\tGlobal 1: %d Local 1: %d\n",global_var1,local1_fTwo);
		global_var1++;
		local1_fTwo++;
		sleep(2);
		V(mutex);
		printf("End Function Two\n");
	}
}

//Method 2 functions
void producer_One(){
	while(1){
		P(empty);
		shelf[addIndex] = 1; //adding a can
		addIndex = (addIndex + 1) % SHELF_MAX;
		displayShelf("Producer1");
		sleep(2);
		V(full);
	} 
}

void producer_Two(){
	while(1){
		P(empty);
		shelf[addIndex] = 1; //adding a can
		addIndex = (addIndex + 1) % SHELF_MAX;
		displayShelf("Producer2");
		sleep(2);
		V(full);
	} 
}

void consumer_One(){
	while(1){
		P(full);
		shelf[subIndex] = 0; //remove a can
		subIndex = (subIndex + 1) % SHELF_MAX;
		displayShelf("Consumer1");
		sleep(2);
		V(empty);
	} 
}

void consumer_Two(){
	while(1){
		P(full);
		shelf[subIndex] = 0; //remove a can
		subIndex = (subIndex + 1) % SHELF_MAX;
		displayShelf("Consumer2");
		sleep(2);
		V(empty);
	} 
}

void displayShelf(char* str){
	printf("%s - \t", str);
	int i;
	for (i = 0; i < SHELF_MAX; i++){	printf("%d: %d\t", i, shelf[i]);}
	printf("\n");
	sleep(1);
}

int main(){
	// Method 1: 
	/*mutex = (struct semaphore_t*) malloc(sizeof(struct semaphore_t));
	
	InitSem(mutex, 1);
	start_thread(function_One);
	start_thread(function_Two);*/

	// Method 2:
	empty = (struct semaphore_t*) malloc(sizeof(struct semaphore_t));
	full = (struct semaphore_t*) malloc(sizeof(struct semaphore_t));

	//Initialize semaphores
	InitSem(empty, SHELF_MAX);
	InitSem(full, 0);
	
	start_thread(consumer_One);
	start_thread(consumer_Two);
	start_thread(producer_One);
	start_thread(producer_Two);

	run();
	return 0;
}

