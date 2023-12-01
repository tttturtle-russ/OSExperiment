//
// Created by russ on 23-11-26.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        sleep(5);
        exit(28);
    }else if (pid > 0) {
        printf("parent id is %d\n",getpid());
        int code = 0;
        printf("child id is %d\n",wait(&code));
        printf("child process return %d\n",WEXITSTATUS(code));
    }else {
        printf("fork error!\n");
    }
    return 0;
}