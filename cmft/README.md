#Stack buffer overflow in function rwReadFile







I use **Clang 6.0 and AddressSanitizer**  to build **cmft**, this [file](https://github.com/fouzhe/security/blob/master/cmft/down-reference.ktx) can cause stack buffer overflow when executing this command:



```shell
./cmftRelease --input ./down-reference.ktx --output0 1
```



This is the ASAN information:

```shell
==22471==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffdd8490e18 at pc 0x00000049eccc bp 0x7ffdd8490b60 sp 0x7ffdd8490310
WRITE of size 49152 at 0x7ffdd8490e18 thread T0
AddressSanitizer:DEADLYSIGNAL
AddressSanitizer: nested bug in the same thread, aborting.
```



This is the debug information:

```
#0  __interceptor_fread (ptr=0x7ffffffe4c50, size=1, nmemb=49152, 
    file=0x616000000080)
    at /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:973
#1  0x000000000054b0a6 in cmft::rwReadFile (_src=0x7ffffffe4f80, 
    _data=0x7ffffffe4c50, _size=49152) at ../../src/cmft/image.cpp:238
#2  0x00000000005b24b7 in cmft::imageLoadKtx (_image=..., _rw=<optimized out>, 
    _allocator=0x96bb80 <cmft::g_crtAllocator>) at ../../src/cmft/image.cpp:4587
#3  0x00000000005bcb08 in cmft::imageLoad (_image=..., _rw=<optimized out>, 
    _convertTo=cmft::TextureFormat::RGBA32F, 
    _allocator=0x96bb80 <cmft::g_crtAllocator>) at ../../src/cmft/image.cpp:5030
#4  0x00000000005bd53c in cmft::imageLoad (_image=..., _filePath=<optimized out>, 
    _convertTo=<optimized out>, _allocator=<optimized out>)
    at ../../src/cmft/image.cpp:5057
#5  0x0000000000716df0 in cmftMain (_argc=<optimized out>, _argv=<optimized out>)
    at ../../src/cmft_cli/cmft_cli.h:895
#6  0x00007ffff6b63830 in __libc_start_main (
    main=0x71b6f0 <main(int, char const* const*)>, argc=5, argv=0x7fffffffdd88, 
    init=<optimized out>, fini=<optimized out>, rtld_fini=<optimized out>, 
    stack_end=0x7fffffffdd78) at ../csu/libc-start.c:291
#7  0x000000000041bb29 in _start ()
```

