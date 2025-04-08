#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>





void *thread_function(void *arg)
{
    int *num=arg;
    pthread_exit(&num);
}

int main()
{
pthread_t p;
void *value;
int num=10;
pthread_create(&p,NULL,thread_function,(void *)&num);

pthread_join(p,&value);

printf("Entered value is %d",atoi(value));





    return 0;


}
