#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int createThread(void (*callback)(void)) {
    fflush(stdout);
    fflush(stdin);
    int rc = fork();
    if (rc < 0) {
        exit(1);
    } else if (rc == 0) {
        callback();
        exit(0);
    }
    return rc;
}