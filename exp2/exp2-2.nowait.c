//
// Created by russ on 23-11-26.
//
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main() {
    pid_t pid = fork();
    if (pid == 0) {
        printf("child id is %d\n",getpid());
        printf("chile process goto dead loop\n");
        while (1);
    }else if (pid > 0) {
        printf("parent id is %d\n",getpid());
        sleep(5);
        return 0;
    }else {
        printf("fork error!\n");
    }
    return 0;
}