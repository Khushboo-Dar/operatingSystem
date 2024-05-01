#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h> //required for open system call
#include<unistd.h> // reqd for clode sys call
int main()
{
    char *file_path = "example.txt";
    int file_descriptor;

    //opening a file in read only mode
   file_descriptor = open(file_path, O_RDONLY);
   if(file_descriptor==-1)
   {
    perror("error opening the file");
    exit(EXIT_FAILURE);

   }
   printf("file  opened successfully \n");

   //reading and printing the contents of a file
   char buffer[1024];
   ssize_t bytes_read;
   printf("file content:\n");
   while((bytes_read=read(file_descriptor,buffer,sizeof(buffer)))>0)
   {
    write(STDOUT_FILENO,buffer,bytes_read);
   }
   if(bytes_read==-1)
   {
    perror("erroe reading file");
    exit(EXIT_FAILURE);
   }
    
    //CLOSING THE FILE
    if(close(file_descriptor)==-1)
    {
        perror("error closing the file");
        exit(EXIT_FAILURE);
    }
    printf("\n file closed successfully\n");
    return 0;
}
