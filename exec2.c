#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<unistd.h>

int main()
{
    // Using execl()
    if(execl("/sbin/ifconfig", "/sbin/ifconfig", NULL) == -1) {
        // Using execlp() if execl() fails
        if(execlp("ipconfig", "ipconfig", NULL) == -1) {
            // Using execle() if execlp() fails
            if(execle("/sbin/ifconfig", "/sbin/ifconfig", NULL, NULL) == -1) {
                // Using execv() if execle() fails
                if(execv("/sbin/ifconfig", (char *[]){"ifconfig", NULL}) == -1) {
                    // Using execvp() if execv() fails
                    if(execvp("ipconfig", (char *[]){"ipconfig", NULL}) == -1) {
                        // Using execvpe() if execvp() fails
                        if(execvpe("ipconfig", (char *[]){"ipconfig", NULL}, NULL) == -1) {
                            fprintf(stderr, "Cannot run ipconfig: %s\n", strerror(errno));
                            return 1;
                        }
                    }
                }
            }
        }
    }
    return 0;
}
