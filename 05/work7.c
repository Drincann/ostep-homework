#include <stdio.h>
#include <unistd.h>

int main() {
    if (!fork()) {
        close(STDOUT_FILENO);
    } else {
        wait();
        printf("parent pro\n");
    }
    return 0;
}