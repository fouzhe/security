#  signal SIGFPE, Arithmetic exception(CVE-2018-12108)







This malformed lepton file can cause crash.

Program received signal SIGFPE, Arithmetic exception. This is the [input file](https://github.com/fouzhe/security/tree/master/lepton/crash_file).


```
Program received signal SIGFPE, Arithmetic exception.
0x00007ffff7bcb269 in raise (sig=8) at ../sysdeps/unix/sysv/linux/pt-raise.c:35
35	in ../sysdeps/unix/sysv/linux/pt-raise.c
```



Here is the gdb information:

```
(gdb) bt
#0  raise (sig=8) at ../sysdeps/unix/sysv/linux/pt-raise.c:31
#1  0x0000000000426e63 in validateAndCompress (reader=<optimized out>,
    writer=<optimized out>, header=..., header_size=<optimized out>,
    start_byte=<optimized out>, end_byte=<optimized out>,
    validation_exit_code=<optimized out>, lepton_data=<optimized out>,
    argc=<optimized out>, argv=<optimized out>, is_permissive=<optimized out>,
    is_socket=<optimized out>, permissive_jpeg_return=<optimized out>)
    at src/lepton/validation.cc:170
#2  0x0000000000410bfa in process_file (reader=<optimized out>,
    writer=<optimized out>, max_file_size=<optimized out>,
    force_zlib0=<optimized out>) at src/lepton/jpgcoder.cc:1607
#3  0x000000000040f7cc in app_main (argc=<optimized out>, argv=<optimized out>)
    at src/lepton/jpgcoder.cc:946
#4  0x00007ffff6f6f830 in __libc_start_main (main=0x4268e0 <main(int, char**)>,
    argc=3, argv=0x7fffffffe428, init=<optimized out>, fini=<optimized out>,
    rtld_fini=<optimized out>, stack_end=0x7fffffffe418) at ../csu/libc-start.c:291
#5  0x0000000000403169 in _start ()
```
