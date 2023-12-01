//
// Created by russ on 23-11-28.
//
#include <stdio.h>
#include <memory.h>
#include <pthread.h>
#include <unistd.h>
#include <asm-generic/errno-base.h>

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
        if (pthread_mutex_trylock(&chopstick[right]) == EBUSY){ //拿起右手的筷子
            pthread_mutex_unlock(&chopstick[left]); //如果右边筷子被拿走放下左手的筷子
            continue;
        }

        //pthread_mutex_lock(&chopstick[right]); //拿起右手的筷子
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