#include <stdio.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();

  if (pid < 0) {
    // Error handling for failed fork
    fprintf(stderr, "Fork failed!\n");
    return 1;
  } else if (pid == 0) {
    // Child process
    printf("I am the child process with PID: %d\n", getpid());
  } else {
    // Parent process
    printf("I am the parent process with PID: %d\n", getpid());
    printf("My child process has PID: %d\n", pid);
  }

  return 0;
}
