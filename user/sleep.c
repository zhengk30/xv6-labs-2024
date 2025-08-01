#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char** argv) {
    int nticks = atoi(argv[1]);
    sleep(nticks);
    exit(0);
}
