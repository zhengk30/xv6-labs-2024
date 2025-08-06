# 6.828 Lab 2
## Chapter 2 reading
### OS responsibilities
Mutiplexing, isolation, interaction
### Why OS is not a library
Some RTOS's do implement their OS's as a library, and applications directly manipulate the underlying hardware. But misbehaving applications would interfere the execution of others. Strong isolation is therefore required. Also, designing such a hardware/software interface saves applications from worrying about particulars of time-sharing.
### Strong isolation -- how?
Modes with different levels of privilege are introduced. Applications are run in userspace with user mode, and system calls are invoked to request certain services provided by the kernel (running in the kernel space). On RISC-V, `ecall` instruction switches the CPU from user mode to kernel mode.
### What should be running in kernel mode?
Two mainstream design philosophies compete: monolithic kernel (entire OS running in kernel mode) and microkernel (OS as minimal as possible, applications communicating with each other via kernel to request services).
### How xv6 is started?
```
    kernel loaded by BIOS into memory (@0x80000000)
--> instructions in _entry set up a stack for kernel
--> _entry calls into C code at `start` (kernel/start.c)
--> mret instruction to switch to kernel mode
--> first process created by calling `userinit`
```


