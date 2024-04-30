#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

sem_t room;           // counting semaphore
sem_t chopstick[5];   // binary semaphore

void * philosopher(void *);
void eat(int);

void eat(int phil)
{
	printf("\nPhilosopher %d is eating",phil);
}

int main()
{
	int i,a[5];
	pthread_t tid[5];       // creation of threads refering to 5 philosophers
	
	sem_init(&room,0,4);   // initializations of semaphore  varring from 0 to 4.
	
	for(i=0;i<5;i++)        
		sem_init(&chopstick[i],0,1);  //initializations of binary semaphore .   
		
	for(i=0;i<5;i++){
		a[i]=i;
		pthread_create(&tid[i],NULL,philosopher,(void *)&a[i]);  // creation of philosopher and assigning it a number.
	}
	for(i=0;i<5;i++)
		pthread_join(tid[i],NULL);  // waits until a thread gets terminated
}

void * philosopher(void * num)
{
	int phil=*(int *)num;

	sem_wait(&room);                         // semaphore function to checks if resources are available.
	printf("\nPhilosopher %d has entered room",phil);
	sem_wait(&chopstick[phil]);              // semaphore function to checks if chopstick is available.
	sem_wait(&chopstick[(phil+1)%5]);

	eat(phil);
	sleep(2);
	printf("\nPhilosopher %d has finished eating",phil);

	sem_post(&chopstick[(phil+1)%5]);   // gives confirmation if semophore is released successfully 
	sem_post(&chopstick[phil]);
	sem_post(&room);
}

