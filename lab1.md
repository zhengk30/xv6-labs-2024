# 6.828 Lab 1
## `sleep`
Create `sleep.c` under the `user/` directory and make a call to `sleep` system call which is bootstrapped by the `sleep()` callable defined in `user/user.h`. The actual jump from userspace into kernel is done by ... defined in `user/usys.S`

## `pingpong`
Two pipes are needed for the bi-directional communication since pipes are for uni-directional data transfer. That `read`/`write` are blocking system calls when the corresponding ends have no data available guarantees the ordering required by this task. 
