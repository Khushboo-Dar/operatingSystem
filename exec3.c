#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("I am in exec3.c.\n");
    printf("PID of exec3.c is %d.\n", getpid());
    char *args[] = {"./hello2", NULL};
    execv(args[0], args);
    printf("Coming back to exec_demo.c");
    return 0;
}
