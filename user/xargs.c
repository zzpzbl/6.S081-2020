#include "../kernel/types.h"
#include "../kernel/fs.h"
#include "../kernel/param.h"
#include "../kernel/stat.h"
#include "user.h"

int main(int argc, char * argv[])
{
    char args[MAXARG][MAXARG];
    char * p[MAXARG];
    char buf;
    if (argc < 2) {
        fprintf(2, "missing argv");
        exit(1);
    }
    while (1) {
        int pos = 0;
        memset(args, 0, MAXARG * MAXARG);
        for (int j = 1; j < argc; ++j) {
            strcpy(args[pos++], argv[j]);
        }
        int j = 0;
        while (pos < MAXARG - 1) {
            while (read(0, &buf, 1) <= 0) {
            exit(0);
            }
            if (buf == '\n') {
                break;
            } else if (buf == ' ') {
                pos++;
                j = 0;
            } else {
                args[pos][j++] = buf;
            }
        }
        int i = 0;
        for (i = 0; i <= pos; ++i) p[i] = args[i];
        p[i] = 0;
        if (fork() == 0) {
            exec(argv[1], p);
            exit(0);
        } else {
            wait(0);
        }
    }
    exit(0);
}