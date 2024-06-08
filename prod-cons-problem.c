#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE]; // Buffer array
int in = 0; // Next free position in the buffer for the producer
int out = 0; // Next filled position in the buffer for the consumer

sem_t empty; // Semaphore to count empty slots in the buffer
sem_t full; // Semaphore to count full slots in the buffer
pthread_mutex_t mutex; // Mutex for critical section

// Producer function
void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100; // Produce a random item
        sem_wait(&empty); // Wait if buffer is full
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        // Add the item to the buffer
        buffer[in] = item;
        printf("Producer produced item %d at position %d\n", item, in);
        in = (in + 1) % BUFFER_SIZE; // Circular increment
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&full); // Signal that the buffer is not empty
        
        sleep(1); // Simulate time taken to produce an item
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full); // Wait if buffer is empty
        pthread_mutex_lock(&mutex); // Lock the buffer
        
        // Remove the item from the buffer
        item = buffer[out];
        printf("Consumer consumed item %d from position %d\n", item, out);
        out = (out + 1) % BUFFER_SIZE; // Circular increment
        
        pthread_mutex_unlock(&mutex); // Unlock the buffer
        sem_post(&empty); // Signal that the buffer is not full
        
        sleep(1); // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t prod, cons; // Thread identifiers
    
    // Initialize the semaphores
    sem_init(&empty, 0, BUFFER_SIZE); // Buffer is initially empty
    sem_init(&full, 0, 0); // Buffer is initially full
    
    // Initialize the mutex
    pthread_mutex_init(&mutex, NULL);
    
    // Create the producer and consumer threads
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    
    // Join the threads (in this simple example, they will run forever)
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    
    // Destroy the semaphores and mutex
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
