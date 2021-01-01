#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/time.h>
#include "thread.h"

static int pipeA[2], pipeB[2];
static int count = 1E6;

void thread1() {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        exit(-1);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < count; i++) {
        read(pipeA[0], NULL, 0);
        write(pipeB[1], NULL, 0);
    }
    gettimeofday(&end, NULL);
    long totalTime = (long)end.tv_sec * 1000000 + (long)end.tv_usec -
                     ((long)start.tv_sec * 1000000 + (long)start.tv_usec);
    printf("\nthread1:\ntotal: %ldus\neach: %lfus\n", totalTime,
           totalTime / ((double)count * 2));
}
void thread2() {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(0, &set);
    if (sched_setaffinity(getpid(), sizeof(cpu_set_t), &set) == -1) {
        exit(-1);
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (size_t i = 0; i < count; i++) {
        write(pipeA[1], NULL, 0);
        read(pipeB[0], NULL, 0);
    }
    gettimeofday(&end, NULL);
    long totalTime = (long)end.tv_sec * 1000000 + (long)end.tv_usec -
                     ((long)start.tv_sec * 1000000 + (long)start.tv_usec);
    printf("\nthread2:\ntotal: %ldus\neach: %lfus\n", totalTime,
           totalTime / ((double)count * 2));
}
int main() {
    // init pipe
    if (pipe(pipeA) == -1 || pipe(pipeB) == -1) {
        exit(1);
    }
    createThread(thread1);
    createThread(thread2);
    wait();
    wait();

    return 0;
}