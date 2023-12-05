#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

int buffer[10];
pthread_mutex_t mutex;
sem_t sem;
int cnt = 0;
int next_to_consume = 0;
int next_to_product = 0;

void *produce(void *data) {
    char ch = *(char*)data;
    // 判断是A还是B生产
    const int offset = ch == 'A' ? 1000 : 2000;
    const int who = offset / 1000;
    while (1) {
        // 休眠0.1-1s
        usleep(rand() % 900 + 100);
        pthread_mutex_lock(&mutex);
        sem_wait(&sem);
        int num = rand() % 1000 + offset;
        // 如果队列满了，则等待
        if (cnt == 10) goto exit;
        printf("productor%d add a value:%d at index:%d\n",who,num,next_to_product);
        // 插入数据到队列
        buffer[next_to_product] = num;
        // 更新索引
        next_to_product++;
        next_to_product %= 10;
        cnt ++;
        exit:
        pthread_mutex_unlock(&mutex);
        sem_post(&sem);
    }
}

void * produce1() {
    while (1) {
        // 休眠0.1-1s
        usleep(rand() % 900 + 100);
        pthread_mutex_lock(&mutex);
//        sem_wait(sem);
        int num = rand() % 1000 + 1000;
        // 如果队列满了，则等待
        if (cnt == 10) goto exit;
        printf("productor1 add a value:%d at index:%d\n",num,next_to_product);
        // 插入数据到队列
        buffer[next_to_product] = num;
        // 更新索引
        next_to_product++;
        next_to_product %= 10;
        cnt ++;
        exit:
        pthread_mutex_unlock(&mutex);
        //        sem_post(sem);
    }
    return NULL;
}

void *  produce2() {
    while (1){
        // 休眠0.1-1s
        usleep(rand() % 900 + 100);
//        sem_wait(sem);
        pthread_mutex_lock(&mutex);
        int num = rand() % 1000 + 2000;
        // 如果队列满了，则等待
        if (cnt == 10) goto exit;
        // 插入数据到队列
        buffer[next_to_product] = num;
        printf("productor2 add a value:%d at index:%d\n",num,next_to_product);
        // 更新索引
        next_to_product ++;
        next_to_product %= 10;
        cnt ++;
        exit:
        pthread_mutex_unlock(&mutex);
//        sem_post(sem);
    }
    return NULL;
}

void * consume() {
    while (1) {
        // 休眠0.1-1s
        usleep(rand() % 900 + 100);
        pthread_mutex_lock(&mutex);
        sem_wait(&sem);
        if (cnt == 0) goto exit;
        while (buffer[next_to_consume] == 0) {
            next_to_consume++;
            next_to_consume %= 10;
        }
        int num = buffer[next_to_consume];
        if (num <= 1999 && num >= 1000){
            printf("From productor 1: index = %d\tvalue = %d\n",next_to_consume,num);
        } else if (num <= 2999 && num >= 2000) {
            printf("From productor 2: index = %d\tvalue = %d\n",next_to_consume,num);
        }else {
            printf("get a wrong value:%d\n",num);
            goto exit;
        }
        buffer[next_to_consume] = 0;
        cnt--;
        exit:
        sem_post(&sem);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main() {
    pthread_t producer1,producer2;
    pthread_t consumer1,consumer2,consumer3;
    sem_init(&sem,0,10);
    pthread_mutex_init(&mutex,NULL);
    pthread_create(&producer1, NULL, produce, "A");
    pthread_create(&producer2, NULL, produce, "B");
    pthread_create(&consumer1,NULL,consume,NULL);
    pthread_create(&consumer2,NULL,consume,NULL);
    pthread_create(&consumer3,NULL,consume,NULL);
    pthread_join(producer1, NULL);
    pthread_join(producer2, NULL);
    pthread_join(consumer1,NULL);
    pthread_join(consumer2,NULL);
    pthread_join(consumer3,NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem);
}
