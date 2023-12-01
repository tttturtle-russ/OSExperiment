////
//// Created by russ on 23-11-27.
////
//#include <unistd.h>
//#include <stdlib.h>
//#include <pthread.h>
//#include <stdio.h>
//
//static char* names[5] = {
//        "a",
//        "b",
//        "c",
//        "d",
//        "d"
//};
//
//typedef struct {
//    char *name;
//    pthread_mutex_t *left,*right;
//}philosopher;
//
//philosopher philosophers[5];
//pthread_mutex_t chops[5];
//pthread_t threads[5];
//
//int pick_up_left(philosopher *p) {
//    if (p == NULL || p->left == NULL) return -1;
////    printf("%s pick up left chopstick\n",p->name);
//    return pthread_mutex_lock(p->left);
//}
//
//int pick_up_right(philosopher *p) {
//    if (p == NULL || p->right == NULL) return -1;
////    printf("%s pick up right chopstick\n",p->name);
//    return pthread_mutex_lock(p->right);
//}
//
//int put_down_left(philosopher *p) {
//    if (p == NULL || p->left == NULL) return -1;
////    printf("%s put down left chopstick\n",p->name);
//    return pthread_mutex_unlock(p->left);
//}
//
//int put_down_right(philosopher *p) {
//    if (p == NULL || p->right == NULL) return -1;
////    printf("%s put down right chopstick\n",p->name);
//    return pthread_mutex_unlock(p->right);
//}
//
//int eat(philosopher *p) {
//    if (p == NULL || p->left == NULL || p->right == NULL) return 1;
//    printf("%s wants to eat...\n",p->name);
//    pick_up_left(p);
//    pick_up_right(p);
//    printf("%s eat successfully! :)\n",p->name);
//    put_down_left(p);
//    put_down_right(p);
//    exit(0);
//}
//
//void think(philosopher *p) {
//    printf("%s thinks about the world :) \n",p->name);
//}
//
//void * action(void * data) {
//    philosopher *p = (philosopher*)data;
//    for(;;) {
//        // 100 - 500ms的随机延迟
//        usleep(rand() % 400 + 100);
//        think(p);
//        usleep(rand() % 400 + 100);
//        eat(p);
//    }
//    return NULL;
//}
//
//int main() {
//    for (int i = 0; i < 5; ++i) {
//        pthread_mutex_init(&chops[i],NULL);
//        philosophers[i].name = names[i];
//        philosophers[i].left = &chops[i];
//        philosophers[i].right = &chops[(i + 1) % 5];
//    }
//    pthread_create(&threads[0],NULL,action,(void*)&philosophers[0]);
//    pthread_create(&threads[1],NULL,action,(void*)&philosophers[1]);
//    pthread_create(&threads[2],NULL,action,(void*)&philosophers[2]);
//    pthread_create(&threads[3],NULL,action,(void*)&philosophers[3]);
//    pthread_create(&threads[4],NULL,action,(void*)&philosophers[4]);
//    pthread_join(threads[0],NULL);
//    pthread_join(threads[1],NULL);
//    pthread_join(threads[2],NULL);
//    pthread_join(threads[3],NULL);
//    pthread_join(threads[4],NULL);
//    如下代码运行到98行就退出了
////    for (int i = 0; i < 5; ++i) {
////        pthread_create(&threads[i],NULL, action,(void *)&philosophers[i]);
////    }
////    for (int i = 0; i < 5; ++i) {
////        if (pthread_join(threads[i],NULL) != 0)
////            printf("error join thread!\n");
////        printf("join thread!\n");
////    }
//}

#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <unistd.h>

static char* names[5] = {
        "Confucius",
        "Plato",
        "Socrates",
        "Aristotle",
        "Dante"
};

pthread_mutex_t chopstick[5] ;
typedef struct {
    char * name;
    int left,right;
}philosopher ;

void think(philosopher p) {
    printf("%s thinks about the world and truth :)\n",p.name);
    usleep(3);
}

void *dine (void *arg){
    philosopher p = *(philosopher*)arg;
    int left = p.left,right = p.right; //左右筷子的编号
    while (1){
        think(p);
        pthread_mutex_lock(&chopstick[left]); //拿起左手的筷子
        printf("%s pick up chopstick %d\n", p.name,left);
//        if (pthread_mutex_trylock(&chopstick[right]) == EBUSY){ //拿起右手的筷子
//            pthread_mutex_unlock(&chopstick[left]); //如果右边筷子被拿走放下左手的筷子
//            continue;
//        }

        pthread_mutex_lock(&chopstick[right]); //拿起右手的筷子
        printf("%s pick up chopstick %d\n", p.name, right);
        printf("%s eat successfully! :)\n",p.name);
        usleep(3); //吃饭
        pthread_mutex_unlock(&chopstick[left]); //放下左手的筷子
        printf("%s put down chopstick %d\n", p.name, left);
        pthread_mutex_unlock(&chopstick[right]); //放下右手的筷子
        printf("%s put down chopstick %d\n", p.name, right);
    }
}
int main(){
    pthread_t Confucius,Plato,Socrates,Aristotle,Dante; //5个哲学家
    philosopher philosophers[5];
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_init(&chopstick[i],NULL);
        philosophers[i].name = names[i];
        philosophers[i].left = i;
        philosophers[i].right = (i + 1) % 5;
    }
    pthread_create(&Confucius, NULL, dine, &philosophers[0]);
    pthread_create(&Plato, NULL, dine, &philosophers[1]);
    pthread_create(&Socrates, NULL, dine, &philosophers[2]);
    pthread_create(&Aristotle, NULL, dine, &philosophers[3]);
    pthread_create(&Dante, NULL, dine, &philosophers[4]);
    pthread_join(Confucius, NULL);
    pthread_join(Plato, NULL);
    pthread_join(Socrates,NULL);
    pthread_join(Aristotle, NULL);
    pthread_join(Dante, NULL);
    return 0;
}