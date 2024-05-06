/*A program demonstrating the inter-process communication using pipe()*/
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 256

int main()
{
   int pipefd[2]; //file descriptor for pipe
   pid_t pid;//process id

   char message[]="hello,child process!!";//message to be sent to child process
   char buffer[BUFFER_SIZE];//buffer for receiving message

   //create the pipe
   if(pipe(pipefd)==-1)
   {
    perror("pipe");
    exit(EXIT_FAILURE);
   }

   //FORK the process
   pid=fork();
   if(pid==-1)
   {
    perror("fork");
    exit(EXIT_FAILURE);
   }

   if(pid==0) //child process
   {
    close(pipefd[1]); //close the write end of the pipe

    //read from the pipe
    read(pipefd[0],buffer,BUFFER_SIZE);
    printf("child process received message: %s \n",buffer);

    close(pipefd[0]);//close the read end of the pipe
    exit(EXIT_SUCCESS);

   }
   else{
    //parent process
    close(pipefd[0]); //close the  read end of the pipe

    //write to the pipe
    write(pipefd[1],message,strlen(message)+1);
    close(pipefd[1]);//close the write end of the pipe
    wait(NULL);//wait for child process to finish
    exit(EXIT_SUCCESS);
   }
   return 0;
}