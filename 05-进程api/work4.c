#include <unistd.h>
#include "thread.h"

void execvThread() {
    char* args[] = {"ls", "-al", NULL};

    execv("/bin/ls", args);
}
void execvpThread() {
    char* args[] = {"ls", "-al", NULL};

    execvp("ls", args);
}
void execvpeThread() {
    char* args[] = {"ls", "-al", NULL};
    char* env[] = {"AA=aa", "BB=bb", NULL};

    execvpe("ls", args, env);
}
void execlThread() {
    execl("/bin/ls", "ls", "-al", NULL);
}
void execlpThread() {
    execlp("ls", "ls", "-al", NULL);
}
void execleThread() {
    char* env[] = {"AA=aa", "BB=bb", NULL};

    execle("/bin/ls", "ls", "-al", NULL, env);
}
int main() {
    createThread(execvThread);
    createThread(execvpThread);
    createThread(execvpeThread);
    createThread(execlThread);
    createThread(execlpThread);
    createThread(execleThread);
    // 还有 execve，但是不知道为什么没有 execlpe
    return 0;
}