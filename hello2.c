#include<stdio.h>
#include<unistd.h>

int main()
{
    printf("I am in hello2.c.\n");
    printf("PID of hello2.c is %d.\n", getpid());
    return 0;
   
}
