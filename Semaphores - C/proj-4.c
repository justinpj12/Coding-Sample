/*
	CSE430 Spring 2015
	Programmers: Justin Jackson , Vanessa Averill-Edwards

*/

#include <string.h>
#include "sem.h"



semaphore_t mutex, r_sem, w_sem;
int	wwc = 0,	//write wait counter
	rwc = 0,	//read wait counter
	wc = 2,		//write counter
	rc = 3;		//read counter



void reader(void){
	while(1){
		printf("\nEntering Reader\n");
		P(&mutex);

		if( wwc > 0 || wc > 0 ){
			sleep(2);
			rwc++;
			printf("There is a writer I must wait to read\t	rwc = %d\n", rwc);
			V(&mutex);
			P(&r_sem);
			sleep(2);
			rwc--;
			printf("Reader Im done reading\t	rwc = %d\n", rwc);
		}
		
		rc++;
		if( rwc > 0) V(&r_sem);
		else	V(&mutex);
		printf("This is reader CS:\t rc = %d\n", rc );

		P(&mutex);
		rc--;
		sleep(2);
		if( rc == 0 && wwc > 0 ) V(&w_sem);
		else	V(&mutex);
		printf("Exiting Reader\n\n");
	}			

}


void writer(void){
	while(1){
		printf("\nEntering Writer\n");
		P(&mutex);
		if( rc > 0 || wc > 0 ){
			sleep(2);
			wwc++;
			printf("There are other writers I must wait to write\t wwc = %d\n",wwc);
			V(&mutex);
			P(&w_sem);
			sleep(2);
			wwc--;
			printf("Writer Im done writing\t wwc = %d\n",wwc);
		}
		wc++;
		V(&mutex);
		printf("This is writer CS:\t wc = %d\n", wc );

		P(&mutex);
		wc--;
		sleep(2);
		if( rwc > 0)	V(&r_sem);
		else if( wwc > 0)	V(&w_sem);
		else	V(&mutex);
		printf("Exiting Writer\n\n");
	} 
}

int main(){

	RunQ = (struct queue*) malloc(sizeof (struct queue));
	InitQueue(RunQ);

	InitSem(&mutex, 1);
	InitSem(&r_sem, 0);
	InitSem(&w_sem, 0);

	start_thread(writer);
	start_thread(writer);

	//start_thread(reader);
	start_thread(reader);
	start_thread(reader);
	start_thread(reader);

	run();
	return 0;
}

