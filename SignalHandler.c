/*A program to implement the new signal handlers for standard signals*/
#include<stdio.h>
#include<signal.h>
#include<stdlib.h>

//custom signal handler for SIGINT
void handle_sigint(int sig)
{
    printf("caught SIGINT signal\n");
    signal(SIGINT,SIG_DFL);//Restore the default behavior for SIGINT
}
int main()
{
    //set custom signal handler for SIGINT
    if(signal(SIGINT,handle_sigint)==SIG_ERR)
    {
        perror("signal");
        exit(EXIT_FAILURE);
    }
    //Infinite loop to keep the program running
    while(1)
    {
        //do some work here
    }
    return 0;
}
/*When i press ctrl+c , the message "caught SIGINT signal should be printed"*/

/*In the main() function, we set up the custom signal handler for SIGINT using the signal() function.
 If setting the signal handler fails, an error message is printed, and the program exits.
The program then enters an infinite loop to keep running until it's terminated. During this time,
 it can respond to SIGINT signals.*/