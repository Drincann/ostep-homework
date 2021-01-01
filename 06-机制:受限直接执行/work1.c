#include <fcntl.h>
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int main() {
    // system call
    int countInner = 1E3, countOuter = 1E3;
    int f = open("./workTest.txt", O_CREAT | O_TRUNC | O_RDWR, 0664);
    long int totalTime = 0;
    for (size_t i = 0; i < countOuter; i++) {
        struct timeval start, end;
        gettimeofday(&start, NULL);
        for (size_t j = 0; j < countInner; j++) {
            read(f, NULL, 0);
        }
        gettimeofday(&end, NULL);
        totalTime += (long)end.tv_sec * 1000000 + (long)end.tv_usec -
                     ((long)start.tv_sec * 1000000 + (long)start.tv_usec);
    }

    // clear
    remove("./workTest.txt");
    printf("total: %ldus\neach: %lfus\n", totalTime,
           totalTime / (double)(countInner * countOuter));

    return 0;
}