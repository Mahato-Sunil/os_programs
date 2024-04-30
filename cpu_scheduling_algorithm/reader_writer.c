#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

sem_t mutex, rw_mutex;
int readers_count = 0;
int running = 1; // Global variable to control termination

void *reader(void *arg) {
    int id = *((int *)arg);
    while (running) {
        sem_wait(&mutex);
        readers_count++;
        if (readers_count == 1) {
            sem_wait(&rw_mutex);
        }
        sem_post(&mutex);

        // Reading
        printf("Reader %d is reading...\n", id);
        sleep(1);

        sem_wait(&mutex);
        readers_count--;
        if (readers_count == 0) {
            sem_post(&rw_mutex);
        }
        sem_post(&mutex);

        // Sleep to simulate reader activity
        sleep(2);
    }
    pthread_exit(NULL);
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (running) {
        sem_wait(&rw_mutex);

        // Writing
        printf("Writer %d is writing...\n", id);
        sleep(2);

        sem_post(&rw_mutex);

        // Sleep to simulate writer activity
        sleep(3);
    }
    pthread_exit(NULL);
}

// Signal handler to handle termination signal (Ctrl+C)
void sigint_handler(int sig) {
    printf("Termination signal received. Exiting...\n");
    running = 0;
}

int main() {
    pthread_t readers[NUM_READERS], writers[NUM_WRITERS];
    int reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];
    
    sem_init(&mutex, 0, 1);
    sem_init(&rw_mutex, 0, 1);

    // Register signal handler for termination signal (Ctrl+C)
    signal(SIGINT, sigint_handler);

    // Create reader threads
    for (int i = 0; i < NUM_READERS; ++i) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    // Create writer threads
    for (int i = 0; i < NUM_WRITERS; ++i) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    // Join threads
    for (int i = 0; i < NUM_READERS; ++i) {
        pthread_join(readers[i], NULL);
    }
    for (int i = 0; i < NUM_WRITERS; ++i) {
        pthread_join(writers[i], NULL);
    }

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&rw_mutex);

    return 0;
}
