# 6.828 Lab 1
## `sleep`
Create `sleep.c` under the `user/` directory and make a call to `sleep` system call which is bootstrapped by the `sleep()` callable defined in `user/user.h`. The actual jump from userspace into kernel is done by ... defined in `user/usys.S`

## `pingpong`
Two pipes are needed for the bi-directional communication since pipes are for uni-directional data transfer. That `read`/`write` are blocking system calls when the corresponding ends have no data available guarantees the ordering required by this task.

## `primes`
The overall idea is pretty straghitforward by following the diagram given in the linked post. Specifically, an overall "root" process starts by creating a pipe to its child for sending numbers from 2 to 280, and its child recursively sends the sieved numbers down to its child. Be careful with the opened fds. Failing to close any redundant fds would break the sieve pretty quickly.

## `find`
Logic in `ls.c` can be largely reused for implementing `find`. Just be careful with not recursing into `.` and `..`. If the search path refers to a file, then do a file name comparison with the target file name (additional logic for extracting the file name from a absolute path is needed). 
