#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_RESOURCES 3 // Total number of resources
#define NUM_THREADS 5   // Number of threads trying to use the resource

sem_t semaphore; // Define the semaphore

// Function for threads to run
void* use_resource(void* thread_id) {
    long tid = (long)thread_id;

    printf("Thread %ld: Waiting to use resource...\n", tid);
    sem_wait(&semaphore); // Wait to use the resource

    printf("Thread %ld: Using the resource...\n", tid);
    sleep(1); // Simulate resource usage

    printf("Thread %ld: Finished using resource.\n", tid);
    sem_post(&semaphore); // Release the resource

    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    sem_init(&semaphore, 0, NUM_RESOURCES); // Initialize semaphore with NUM_RESOURCES

    // Create threads
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, use_resource, (void*)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&semaphore); // Destroy the semaphore
    return 0;
}

/*The purpose of this program is to illustrate how semaphores can be used to control access to a limited number of resources in a multithreaded environment. It shows how to:

Initialize a semaphore.
Use sem_wait and sem_post to manage resource access.
Create and join threads in C.
Here , five threads try to access three available resources concurrently*/