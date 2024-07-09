#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Shared resource
int counter = 0;

// Mutex declaration
pthread_mutex_t mutex;

// Thread function to increment the counter
void *increment_counter(void *arg)
{
    for (int i = 0; i < 100000; ++i) // Each iteration represents an attempt to enter the critical section and increment the counter.
    {
        // Lock the mutex before entering the critical section
        pthread_mutex_lock(&mutex);

        // Critical section
        counter++;

        // Unlock the mutex after exiting the critical section
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    // Number of threads
    const int num_threads = 5;

    // Array of thread identifiers
    pthread_t threads[num_threads];

    // Initialize the mutex
    if (pthread_mutex_init(&mutex, NULL) != 0)
    {
        printf("Failed to initialize mutex\n");
        return 1;
    }

    // Create threads
    for (int i = 0; i < num_threads; ++i)
    {
        if (pthread_create(&threads[i], NULL, increment_counter, NULL) != 0)
        {
            printf("Failed to create thread %d\n", i);
            return 1;
        }
    }

    // Wait for all threads to finish
    for (int i = 0; i < num_threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Destroy the mutex
    pthread_mutex_destroy(&mutex);

    // Print the final value of the counter
    printf("Final counter value: %d\n", counter);

    return 0;
}
/*
Thread Creation: Using pthread_create to create multiple threads.
Mutex Usage: Using a mutex to ensure that only one thread accesses the critical section at a time.
Thread Synchronization: Using pthread_join to wait for all threads to complete.
Resource Management: Proper initialization and destruction of the mutex to avoid resource leaks.*/