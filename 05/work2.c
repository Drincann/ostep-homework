#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    int fd = open("./work2.txt", O_RDWR | O_CREAT, S_IRWXU);

    if (!fork()) {
        for (int i = 0; i < 10000; ++i) {
            write(fd, "1", 2);
        }
    } else {
        for (int i = 0; i < 10000; ++i) {
            write(fd, "-", 2);
        }
    }
    return 0;
}