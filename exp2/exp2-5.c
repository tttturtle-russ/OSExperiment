//
// Created by russ on 23-11-27.
//
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

void terminate_handler() {
    printf("Bye,World!\n");
    exit(0);
}

int main() {
    pid_t pid = fork();
    if (pid == 0) {
        if (signal(SIGTERM,terminate_handler) == SIG_ERR)
        {
            printf("failed to set SIGTERM handler!\n");
            printf("chile process exit!\n");
            exit(1);
        }
        while (1){
            sleep(2);
            printf("i am Child process, alive!\n");
        }
    }else if (pid > 0) {
        char buf[16] = {'N'};
        int code;
        while (buf[0] != 'Y') {
            printf("To terminate Child Process. Yes or No?\n");
            scanf("%s",buf);
            sleep(2);
        }
        kill(pid,SIGTERM);
        wait(&code);
        printf("child process exit %d\n",code / 256);
        return 0;
    }else {
        printf("failed to fork!\n");
        return 1;
    }
}