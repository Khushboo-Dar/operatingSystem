/*IMPLEMENT MATRIX MULTIPLICATION USING MULTIPLE THREADS.*/
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define SIZE 3
int A[SIZE][SIZE];
int B[SIZE][SIZE];
int C[SIZE][SIZE];
typedef struct {
    int row;
    int col;
}
thread_data;

void *multiply(void *arg)
{
    thread_data *data=(thread_data*)arg;
    int row=data->row;
    int col=data->col;
    int sum=0;
    for(int i=0;i<SIZE;i++)
    {
        sum+=A[row][i]*B[i][col];
    }
    C[row][col]=sum;
    pthread_exit(NULL);
}
int main()
{
    printf("MATRIX A : \n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++){
            A[i][j]=rand()%10;
            printf("%d\t",A[i][j]);

        }
        printf("\n");
    }
    printf("\n MATRIX B : \n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++){
            B[i][j]=rand()%10;
            printf("%d\t",B[i][j]);

        }
        printf("\n");
    }
    pthread_t threads[SIZE][SIZE];
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            thread_data *data=(thread_data*)malloc(sizeof(thread_data));
            data->row=i;
            data->col=j;
            pthread_create(&threads[i][j],NULL,multiply,(void *)data);
        }
    }
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            pthread_join(threads[i][j],NULL);
        }
    }
    printf("\n matrix C: \n");
    for(int i=0;i<SIZE;i++)
    {
        for(int j=0;j<SIZE;j++)
        {
            printf("%d\t",C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
