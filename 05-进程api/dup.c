#include <fcntl.h>
#include <stdio.h>
#include "thread.h"

// 子进程
void child() {
    printf("child pro");
}

int main() {
    // 相当于将 STDOUT_FILENO 变成 target
    // 以后对 STDOUT_FILENO 的操作全部变成对 target 的操作
    int target = open("./dup_out.txt", O_CREAT | O_TRUNC | O_RDWR, 0664);
    dup2(target, STDOUT_FILENO);
    createThread(child);

    return 0;
}