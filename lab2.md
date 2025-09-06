# 6.828 Lab 2
## Chapter 2 reading
### OS responsibilities
Multiplexing, isolation, interaction
### Why is OS not a library
Some RTOS's do implement their OS's as a library, and applications directly manipulate the underlying hardware. But misbehaving applications would interfere with the execution of others. Strong isolation is therefore required. Also, designing such a hardware/software interface saves applications from worrying about particulars of time-sharing.
### Strong isolation -- how?
Modes with different levels of privilege are introduced. Applications are run in userspace with user mode, and system calls are invoked to request certain services provided by the kernel (running in the kernel space). On RISC-V, `ecall` instruction switches the CPU from user mode to kernel mode.
### What should be running in kernel mode?
Two mainstream design philosophies compete: monolithic kernel (entire OS in kernel mode) and microkernel (OS as minimal as possible, applications communicating with each other via kernel to request services).
### How is xv6 started?
```
    kernel loaded by BIOS into memory (@0x80000000)
--> instructions in _entry set up a stack for kernel
--> _entry calls into C code at `start` (kernel/start.c)
--> mret instruction to switch to kernel mode
--> first process created by calling `userinit`
```

## `trace` system call
The overall process of making a system call is as follows: The corresponding function (i.e., a wrapper function defined in `user/user.h`) is invoked from the userspace. Then the userspace stub for that system call is located (in `user/usys.pl`, a Perl script that is used to generate the assembly code into `user/usys.S`), and the system call number of the desired system call is placed into register `a7`, from which the kernel fetches the number to check which system call to execute. The `ecall` instruction (RISC-V's trap-into-kernel instruction) is executed, and the OS enters the kernel space. In `kernel/syscall.c`, the function `syscall()` serves as the entry point for locating the right system call handler and running it for the calling process. Finally, the corresponding system call handler finishes and populates the return value in the calling process's `a0` register.

Based on the workflow described above, the corresponding stub and handler should at least be registered, which involves modifying `user/usys.pl`, `kernel/syscall.c`, and `kernel/sysproc.c`. Then, according to the specification, `trace` should enable tracing for the desired system calls in both the calling process and the child processes it forks, which requires `fork()` to be able to copy the `trace_mask` from parent to child (make this modification in `fork()` and `struct proc`). Finally, in `syscall()`, print the desired line after the specified system call is made if it's specified in `trace_mask`. The job of `sys_trace` would be simply fetching the argument `trace_mask` from register `a0`.
