#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int staticVar = 0;
int main() {
    int localVar = 0;
    int* heapVar = (int*)malloc(sizeof(int));
    // 进程之间甚至无法共享堆区数据
    if (!fork()) {
        printf("child pro %d %d %d\n", ++localVar, ++staticVar, ++(*heapVar));
    } else {
        printf("main pro %d %d %d\n", ++localVar, ++staticVar, ++(*heapVar));
        wait();
    }
    return 0;
}