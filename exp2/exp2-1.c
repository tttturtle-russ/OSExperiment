//
// Created by russ on 23-11-26.
//
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * A(void *pVoid) {
    for (int i = 0; i < 1000; ++i) {
        usleep(200);
        printf("A:%04d\n",i+1);
    }
    return NULL;
}

void * B(void *pVoid) {
    for (int i = 1000; i > 0; --i) {
        usleep(200);
        printf("B:%04d\n",i);
    }
    return NULL;
}

int main() {
    pthread_t thread_a,thread_b;
    pthread_create(&thread_a,NULL,A,NULL);
    pthread_create(&thread_b,NULL,B,NULL);
    pthread_join(thread_a,NULL);
    pthread_join(thread_b, NULL);
}