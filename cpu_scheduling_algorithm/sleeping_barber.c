#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define MAX_CUSTOMERS 10
#define MAX_WAITING_CHAIRS 10

sem_t waiting_chairs;      // Semaphore for waiting chairs
sem_t barber_chair;        // Semaphore for the barber chair
sem_t customer_ready;      // Semaphore to signal customer readiness
int num_customers = 0;     // Number of waiting customers

void *barber(void *arg)
{
    while (1)
    {
        sem_wait(&customer_ready); // Wait for a customer to be ready
        sem_wait(&waiting_chairs); // Wait for the waiting chairs semaphore

        printf("Barber is cutting customer hair.\n");
        sleep(1); // Simulate hair cutting

        sem_post(&waiting_chairs); // Release the waiting chairs semaphore
    }
}

void *customer(void *arg)
{
    int id = *(int *)arg;

    if (num_customers < MAX_CUSTOMERS)
    {
        printf("Customer %d enters the waiting room.\n", id);
        num_customers++;

        sem_post(&customer_ready); // Signal to the barber that customer is ready

        if (num_customers <= MAX_WAITING_CHAIRS) {
            sem_wait(&barber_chair);   // Wait for the barber chair
            printf("Customer %d is getting a haircut.\n", id);
            sleep(1); // Simulate hair cutting
            sem_post(&barber_chair); // Release the barber chair
            printf("Customer %d leaves after getting a haircut.\n", id);
        } else {
            printf("Customer %d leaves because no chairs are available.\n", id);
            num_customers--; // Decrement the number of customers since this customer is leaving
        }
    }
    else
    {
        printf("Chair Full So Customer %d leaves. \n", id);
    }
}

int main()
{
    sem_init(&waiting_chairs, 0, MAX_WAITING_CHAIRS); // Initialize the waiting chairs semaphore with 5 chairs
    sem_init(&barber_chair, 0, 10);   // Initialize the barber chair semaphore with 1 chair
    sem_init(&customer_ready, 0, 10); // Initialize the customer ready semaphore with 0

    pthread_t barber_thread;
    pthread_create(&barber_thread, NULL, barber, NULL);

    pthread_t customer_threads[MAX_CUSTOMERS];
    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        pthread_create(&customer_threads[i], NULL, customer, id);
    }

    for (int i = 0; i < MAX_CUSTOMERS; i++)
    {
        pthread_join(customer_threads[i], NULL);
    }

    printf("All customers have been served.\n");

    sem_destroy(&waiting_chairs);
    sem_destroy(&barber_chair);
    sem_destroy(&customer_ready);

    return 0;
}
