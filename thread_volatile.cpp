
#include <iostream>
#include <atomic>
#include <vector>
#include <thread>
#include <sstream>
#include <unistd.h>
 

volatile int flag = 1;

pthread_mutex_t lock;

void* my_thread(void *){

    sleep(1);

    printf("run thread1\n");

    

    pthread_mutex_lock(&lock);

    flag = -1;

    pthread_mutex_unlock(&lock);

    

    return NULL;

}

 

int main() {

    pthread_t t;

    int re = pthread_create(&t, NULL, &my_thread, NULL);

    if(re < 0){

        printf("create thread error\n");

        return 0;

    }

    

    pthread_mutex_lock(&lock);

    while(flag > 0){

//        sleep(1);

    }

    pthread_mutex_unlock(&lock);

    

    return 0;

}

