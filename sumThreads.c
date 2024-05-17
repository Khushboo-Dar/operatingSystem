#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
void *threadFunc1(void *arg);
void *threadFunc2(void *arg);
void *threadFunc3(void *arg);
int result1, result2;

int main() {
    pthread_t thread1, thread2, thread3;
    int arg2 = 7; // Argument for thread 2
    int args3[2]; // Arguments for thread 3 (results of thread 1 and 2)

    // Create thread 1
    if (pthread_create(&thread1, NULL, threadFunc1, NULL) != 0) {
        fprintf(stderr, "Error creating thread 1\n");
        return 1;
    }

    // Wait for thread 1 to complete
    pthread_join(thread1, NULL);

    // Create thread 2
    if (pthread_create(&thread2, NULL, threadFunc2, (void*)&arg2) != 0) {
        fprintf(stderr, "Error creating thread 2\n");
        return 1;
    }

    // Wait for thread 2 to complete
    pthread_join(thread2, NULL);

    // Prepare arguments for thread 3
    args3[0] = result1;
    args3[1] = result2;

    // Create thread 3
    if (pthread_create(&thread3, NULL, threadFunc3, (void*)args3) != 0) {
        fprintf(stderr, "Error creating thread 3\n");
        return 1;
    }

    // Wait for thread 3 to complete
    pthread_join(thread3, NULL);

    return 0;
}

// Function for thread 1
void *threadFunc1(void *arg) {
    result1 = 5; // Assign some value to result1
    printf("Thread 1: Result = %d\n", result1);
    pthread_exit(NULL);
}

// Function for thread 2
void *threadFunc2(void *arg) {
    int num = *(int *)arg;
    result2 = num * 2; // Some operation on the argument
    printf("Thread 2: Argument = %d, Result = %d\n", num, result2);
    pthread_exit(NULL);
}

// Function for thread 3
void *threadFunc3(void *arg) {
    int *results = (int *)arg;
    int sum = results[0] + results[1];
    printf("Thread 3: Result1 = %d, Result2 = %d, Sum = %d\n", results[0], results[1], sum);
    pthread_exit(NULL);
}
