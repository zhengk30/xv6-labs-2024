#include "kernel/types.h"
#include "user/user.h"

#define RD_END 0
#define WRT_END 1

int main() {
////    int p[2];
//    int pid;
//    
//    pid = fork();
//    if (pid == 0) {
//        printf("%d: received ping\n", getpid());
//        exit(0);
//    } else if (pid > 0) {
//        wait(0);
//        printf("%d: received pong\n", getpid());
//        exit(0);
//    } else {
//        exit(1);
//    }
//    exit(0);
    int pcp[2], cpp[2];
    pipe(pcp);
    pipe(cpp);

    int pid = fork();
    if (pid < 0) {
        exit(1);
    } else if (pid > 0) {
        write(pcp[WRT_END], "parent", 6);
        close(pcp[WRT_END]);
        char recv_buf[6];
        read(cpp[RD_END], recv_buf, 5);
        printf("%d: received pong\n", getpid());
        close(cpp[RD_END]);
        exit(0);
    } else {
        char recv_buf[7];
        read(pcp[RD_END], recv_buf, 6);
        close(pcp[RD_END]);
        printf("%d: received ping\n", getpid());
        write(cpp[WRT_END], "child", 5);
        close(cpp[WRT_END]);
        exit(0);
    }
}
