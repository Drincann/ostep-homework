#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        exit(1);
    }
    if (!fork()) {  // 子进程
        printf("hello");
        fflush(stdout);
        write(fd[1], " goodbye", strlen(" goodbye"));
    } else {  // 父进程
        char buf[1024];
        // 若父进程抢到 cpu，则会在此等待，
        // 直到子进程输出hello、写入管道，并让出 cpu
        // 然后父进程从此处返回
        read(fd[0], buf, 1024);
        printf(buf);
    }
    return 0;
}