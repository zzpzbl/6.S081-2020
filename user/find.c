#include "../kernel/types.h"
#include "../kernel/fs.h"
#include "../kernel/stat.h"
#include "user.h"

void find(char * path, char * target)
{
    int fd;
    char buf[512], *p;
    struct dirent de;
    struct stat st;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "cann't open %s!", path);
        return ;
    }

    if (fstat(fd, &st) < 0 || st.type != T_DIR) {
        fprintf(2, "cann't stat %s!", path);
        close(fd);
        return ; 
    }

    /*
    path = "example"
    buf = "example/"
    */
    strcpy(buf, path);
    p = buf + strlen(buf);
    *p++ = '/';
    while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) {
            continue;
        }
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = 0;
        if(stat(buf, &st) < 0){
            printf("cannot stat %s\n", buf);
            continue;
        }
        switch (st.type) {
            case T_FILE:
                if (strcmp(target, de.name) == 0) {
                    printf("%s\n", buf);
                }
                break;
            case T_DIR:
                if (strcmp(de.name, ".") != 0 && strcmp(de.name, "..") != 0) {
                    find(buf, target);
                }
                break;
        }
    }
    close(fd);
    return ;
}

int main(int argc, char * argv[])
{
    if (argc < 3) {
        fprintf(2, "missing arguements");
        exit(1);
    }
    find(argv[1], argv[2]);

    exit(0);
}