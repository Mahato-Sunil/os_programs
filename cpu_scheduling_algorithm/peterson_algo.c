#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>

#define NUM_THREADS 2

bool flag[NUM_THREADS]; // Flags for each thread
int turn = 0;           // Turn variable

void* thread_func(void* thread_id) {
    int id = *(int*)thread_id;
    int other = 1 - id; // ID of the other thread

    flag[id] = true;    // Marking entry to the critical section
    turn = other;       // Giving the other thread the turn
    // Wait until the other thread releases its flag or it's your turn
    while (flag[other] && turn == other) {}

    // Critical Section
    printf("Thread %d is in critical section.\n", id);
    for(int i = 0; i<3; i++)

    printf("Thread %d is being Executed.\n", id);
    
    // Exiting the critical section
    flag[id] = false;

    printf("Thread %d exited the critical section.\n", id);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS] = {0, 1}; // IDs for the threads

    // Creating threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_create(&threads[i], NULL, thread_func, (void*)&thread_ids[i]);
    }

    // Joining threads
    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
