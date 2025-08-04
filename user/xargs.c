#include "kernel/param.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv) {
    char* args[MAXARG];
    for (int i = 1; i < argc; i++) {
        args[i-1] = argv[i];
    }
    char buf[512];
    int done = 0;
    while (!done) {
        char c;
        int p = argc - 1;
        int i = 0;
        while (1) {
            int nbytes = read(0, &c, sizeof(char));
            if (nbytes == 0) {
                done = 1;
                break;
            }
            if (c != ' ' && c != '\n') {
                buf[i++] = c;
            } else {
                buf[i] = 0;
                args[p] = (char*)malloc(strlen(buf)+1);
                strcpy(args[p], buf);
                memset(buf, 0, 512);
                i = 0;
                p++;
                if (c == '\n')
                    break;
            }
        }
        if (!done) {
            args[p] = 0;
            if (fork() == 0) {
                exec(args[0], args);
            } else {
                wait(0);
            }
        }
    }
    exit(0);
}
