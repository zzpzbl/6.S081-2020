#include "../kernel/types.h"
#include "user.h"

void primes(int * p) 
{
    int in = p[0], out;
    int p2[2];
    int prime, x;
    close(p[1]);
    int len = read(in, &prime, sizeof(int));
    if (len <= 0) {
        exit(0);
    }
    printf("prime %d\n", prime);

    pipe(p2);
    out = p2[1];
    int pid = fork();
    if (pid > 0) {
        while ((len = read(in, &x, sizeof(int))) > 0) {
            if (x % prime != 0) {
                write(out, &x, sizeof(int));
            }
        }
        close(out);
        wait(0);
        exit(0);
    } else {
        primes(p2);
    }
}

int main()
{
    int p[2];
    pipe(p);
    int pid = fork();
    if (pid > 0) {
        for (int i = 2; i <= 35; ++i) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    } else {
        primes(p);
    }
    exit(0);
}