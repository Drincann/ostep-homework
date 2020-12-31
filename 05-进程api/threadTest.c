#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "thread.h"

void thread() {
    execl("/bin/ls", "ls", "-al", NULL);
    return;
    for (int i = 0; i < 1; ++i) {
        printf("%d  (%d)\n", a++, getpid());
    }
}

int main(int argc, char* argv[]) {
    createThread(thread);
    return 0;
}
