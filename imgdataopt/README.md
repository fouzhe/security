#  Program received signal SIGFPE, Arithmetic exception.





I use **Clang 6.0 and AddressSanitizer**  to build **imgdataopt**, this [file](https://github.com/fouzhe/security/blob/master/imgdataopt/crash) can cause crash. Program received signal SIGFPE, Arithmetic exception when executing this command:



```shell
./imgdataopt crash 1.png
```





This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==20944==ERROR: AddressSanitizer: FPE on unknown address 0x00000055c9be (pc 0x00000055c9be bp 0x000000000003 sp 0x7ffe39e5e0d0 T0)
    #0 0x55c9bd  (/home/fouzhe/my_fuzz/imgdataopt_new/imgdataopt/imgdataopt+0x55c9bd)
    #1 0x518312  (/home/fouzhe/my_fuzz/imgdataopt_new/imgdataopt/imgdataopt+0x518312)
    #2 0x7f4bb3a3d82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #3 0x419fd8 in getenv (/home/fouzhe/my_fuzz/imgdataopt_new/imgdataopt/imgdataopt+0x419fd8)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: FPE (/home/fouzhe/my_fuzz/imgdataopt_new/imgdataopt/imgdataopt+0x55c9bd)
==20944==ABORTING
```



This is the gdb information:

```shell
(gdb) set args ./crash 1.png
(gdb) start
Function "main" not defined.
Make breakpoint pending on future shared library load? (y or [n]) y
Temporary breakpoint 1 (main) pending.
Starting program: /home/fouzhe/my_fuzz/imgdataopt_new/imgdataopt/imgdataopt ./crash 1.png
[Thread debugging using libthread_db enabled]
Using host libthread_db library "/lib/x86_64-linux-gnu/libthread_db.so.1".

Program received signal SIGFPE, Arithmetic exception.
0x000000000055c9be in ?? ()
(gdb) bt
#0  0x000000000055c9be in ?? ()
#1  0x0000000000518313 in ?? ()
#2  0x00007ffff6ee5830 in __libc_start_main (main=0x5162d0, argc=3, argv=0x7fffffffe418, init=<optimized out>, fini=<optimized out>, rtld_fini=<optimized out>,
    stack_end=0x7fffffffe408) at ../csu/libc-start.c:291
#3  0x0000000000419fd9 in ?? ()
```

