#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "thread.h"

// 管道句柄
static int fd[2], readPipe, writePipe;

// 子进程 1
void child1() {
    char buf[1024] = {0};
    printf("child1 in:");
    fflush(stdout);

    while (scanf("%s", buf) != -1) {
        // 从 stdin 读，写入 pipe
        write(writePipe, buf, sizeof(buf));
        memset(buf, 0, sizeof(buf));

        // 让出 cpu，让子进程 2 输出
        // (这种做法并不稳定，应该通过进程共享内存实现进程同步锁，这里不展开)
        sleep(0);
        printf("child1 in: ");
        fflush(stdout);
    }
}

// 子进程 2
void child2() {
    char buf[1024];
    while (read(readPipe, buf, sizeof(buf))) {
        printf("child2 out: ");
        printf(buf);
        printf("\n");
        fflush(stdout);
    }
}

int main() {
    // 创建管道
    if (pipe(fd) != -1) {
        readPipe = fd[0];
        writePipe = fd[1];
    } else {
        printf("error");
        exit(1);
    }

    // 创建进程
    createThread(child1);
    createThread(child2);

    // 主进程守护进程 1
    wait();

    return 0;
}