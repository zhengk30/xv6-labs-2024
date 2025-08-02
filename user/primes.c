#include "kernel/types.h"
#include "user/user.h"

#define RD_END 0
#define WRT_END 1

void sieve(int prev[2]) {
    close(prev[WRT_END]);
    int p, n;
    if (read(prev[RD_END], &p, sizeof(int)) == 0) {
        exit(0);
    }
    printf("prime %d\n", p);

    int next[2];
    if (pipe(next) < 0) {
//        printf("%d failed to call pipe\n", getpid());
        exit(1);
    }
//    printf("prev %d %d, next %d %d\n", prev[0], prev[1], next[0], next[1]);
    int pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid > 0) {
        close(next[RD_END]);
        while (read(prev[RD_END], &n, sizeof(int))) { 
            if (n % p) {
                write(next[WRT_END], &n, sizeof(int));
            }
        }
        close(next[WRT_END]);
        close(prev[RD_END]);
        wait(0);
    } else {
        close(prev[RD_END]);
        sieve(next);
    }
}

int main() {
    int p[2];
    if (pipe(p) < 0) {
//        printf("[%d] pipe failed\n", getpid());
        exit(1);
    }
    int pid = fork();
    if (pid < 0) {
        close(p[RD_END]);
        close(p[WRT_END]);
        exit(1);
    } else if (pid > 0) {
        close(p[RD_END]);
        for (int i = 2; i <= 280; i++) {
            int n = i;
            write(p[WRT_END], &n, sizeof(int));
        }
        close(p[WRT_END]);
        wait(0);        
    } else {
        sieve(p);
    }
    exit(9);
}
