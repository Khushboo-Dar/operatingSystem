#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>

#define NUM_LOOPS 10 // Number of times each process will enter the critical section

bool flag[2] = { false, false }; // Shared flag array
int turn; // Shared turn variable

void* process0(void* arg) {
    for (int i = 0; i < NUM_LOOPS; i++) {
        flag[0] = true; // Indicate that process 0 wants to enter the critical section
        turn = 1; // Give priority to process 1

        // Wait until process 1 either does not want to enter or it is not process 1's turn
        while (flag[1] && turn == 1) {
            // Busy wait (spin wait)
        }

        // Critical Section
        printf("Process 0 is in the critical section (iteration %d)\n", i);
        usleep(1000); // Simulate work in the critical section

        // Exit Section
        flag[0] = false; // Indicate that process 0 is leaving the critical section
    }
    return NULL;
}

void* process1(void* arg) {
    for (int i = 0; i < NUM_LOOPS; i++) {
        flag[1] = true; // Indicate that process 1 wants to enter the critical section
        turn = 0; // Give priority to process 0

        // Wait until process 0 either does not want to enter or it is not process 0's turn
        while (flag[0] && turn == 0) {
            // Busy wait (spin wait)
        }

        // Critical Section
        printf("Process 1 is in the critical section (iteration %d)\n", i);
        usleep(1000); // Simulate work in the critical section

        // Exit Section
        flag[1] = false; // Indicate that process 1 is leaving the critical section
    }
    return NULL;
}

int main() {
    pthread_t thread0, thread1;

    // Create two threads representing the two processes
    pthread_create(&thread0, NULL, process0, NULL);
    pthread_create(&thread1, NULL, process1, NULL);

    // Wait for both threads to finish
    pthread_join(thread0, NULL);
    pthread_join(thread1, NULL);

    return 0;
}
