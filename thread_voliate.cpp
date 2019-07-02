
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
 

//volatile int flag = 1;
int flag = 1;

pthread_mutex_t lock;

void* my_thread(void *){

    sleep(1);

    printf("run thread1\n");

    

    pthread_mutex_lock(&lock);
    
    printf("after lock in thread, flag=%d\n",flag);

    flag = -1;
    printf("in thread, flag=%d\n",flag);

    pthread_mutex_unlock(&lock);

    

    return NULL;

}

 

int main() {

    if (pthread_mutex_init(&lock) != 0)
    {
       return 0;
    }

    pthread_t t;

    int re = pthread_create(&t, NULL, &my_thread, NULL);

    if(re < 0){

        printf("create thread error\n");

        return 0;

    }

    printf("before lock in main, flag=%d\n",flag);

    pthread_mutex_lock(&lock);
    
    printf("after lock in main, flag=%d\n",flag);

    while(flag > 0){

        printf("in while, flag=%d\n",flag);
        sleep(1);

    }

    pthread_mutex_unlock(&lock);

    

    return 0;

}

