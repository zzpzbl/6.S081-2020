#include "../kernel/types.h"
#include "./user.h"

int main(int argc, char * argv[])
{
    int p1[2];
    int p2[2];
    char buf = '\0';
    pipe(p1);
    pipe(p2);
    char msg = '\0';

    int pid = fork();
    if (pid > 0) {
        write(p1[1], &msg, 1);
        read(p2[0], &buf, 1);
        printf("%d: received pong\n", getpid());
        close(p1[0]);
        close(p1[1]);
    } else {
        read(p1[0], &buf, 1);
        printf("%d: received ping\n", getpid());
        write(p2[1], &msg, 1);
        close(p2[0]);
        close(p2[1]);
    }
    exit(0);
}
