#include<stdio.h>
#include<string.h>
#include<pthread.h>
//global variable
int i=2;
void* foo(void* p)
{
    //print the value received as argument
    printf("value received as argument in starting routine: ");
    printf("%i\n", *(int*)p);

    //return reference  to global variable
    pthread_exit(&i);
    
}
int main(void){
    //declare a variable for thread's id
    pthread_t id;
    int j=1;
    pthread_create(&id,NULL,foo,&j);
    int *ptr;

    //wait for foo and retrive value in ptr
    pthread_join(id,(void**)&ptr);
    printf("value received by parent from child: ");
    printf("%i\n",*ptr);
}