#    SEGV in function apply_gain in wav_gain.c





I use **Clang 6.0 and AddressSanitizer**  to build **libwav**, this [file](https://github.com/fouzhe/security/blob/master/libwav/wav_gain__crash__SEGV_apply_gain) can cause SEGV signal in function `apply_gain`  when running the  `wav_gain` in folder `tools/wav_gain` with the following command:



```shell
./wav_gain wav_gain__crash__SEGV_apply_gain 1.wav
```



This is the ASAN information:

```shell
LibWAV v. 0.0.1 A (c) 2016 - 2017 Marc Volker Dickmann

AddressSanitizer:DEADLYSIGNAL
=================================================================
==22143==ERROR: AddressSanitizer: SEGV on unknown address 0x00005d5dd1d4 (pc 0x000000518934 bp 0x7ffd5b957f40 sp 0x7ffd5b957e40 T0)
==22143==The signal is caused by a WRITE memory access.
    #0 0x518933 in apply_gain /home/fouzhe/my_fuzz/libwav/tools/wav_gain/wav_gain.c:11:20
    #1 0x518933 in gain_file /home/fouzhe/my_fuzz/libwav/tools/wav_gain/wav_gain.c:26
    #2 0x518933 in main /home/fouzhe/my_fuzz/libwav/tools/wav_gain/wav_gain.c:43
    #3 0x7f3b4c60582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x419f08 in _start (/home/fouzhe/my_fuzz/libwav/tools/wav_gain/wav_gain+0x419f08)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/libwav/tools/wav_gain/wav_gain.c:11:20 in apply_gain
==22143==ABORTING
```





#   SEGV in function wrap_free in libwav.c



I use **Clang 6.0 and AddressSanitizer**  to build **libwav**, this [file](https://github.com/fouzhe/security/blob/master/libwav/wav_gain__crash__SEGV_gain_file) can cause SEGV signal in function `wrap_free`  when running the  `wav_gain` in folder `tools/wav_gain` with the following command:



```shell
./wav_gain wav_gain__crash__SEGV_gain_file 1.wav
```





This is the ASAN information:

```
LibWAV v. 0.0.1 A (c) 2016 - 2017 Marc Volker Dickmann

ASAN:DEADLYSIGNAL
=================================================================
==89112==ERROR: AddressSanitizer: SEGV on unknown address 0x0000ff564147 (pc 0x0001060e8809 bp 0x7fff59b24ee0 sp 0x7fff59b24eb0 T0)
==89112==The signal is caused by a WRITE memory access.
    #0 0x1060e8808 in __asan::Allocator::Deallocate(void*, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x3808)
    #1 0x10613e130 in wrap_free (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x59130)
    #2 0x1060db8fc in wav_free libwav.c:196
    #3 0x1060dc54f in gain_file wav_gain.c:33
    #4 0x1060dc3b2 in main wav_gain.c:43
    #5 0x7fff8bb96234 in start (libdyld.dylib:x86_64+0x5234)

==89112==Register values:
rax = 0x0000000000000002  rbx = 0x00000000ff564157  rcx = 0x00007fff59b24f03  rdx = 0x0000000000000000
rdi = 0x00000000ff564157  rsi = 0x00000000ff564157  rbp = 0x00007fff59b24ee0  rsp = 0x00007fff59b24eb0
 r8 = 0x0000000000000001   r9 = 0x000000000000001e  r10 = 0x000000000000002e  r11 = 0x000000010613dfa0
r12 = 0x00000000ff564147  r13 = 0x0000000000000000  r14 = 0x00007fff59b24f08  r15 = 0x0000000000000001
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (libclang_rt.asan_osx_dynamic.dylib:x86_64h+0x3808) in __asan::Allocator::Deallocate(void*, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType)
==89112==ABORTING
Abort trap: 6
```





#   Infinite loop in wav_read in libwav.c 

I use **Clang 6.0 and AddressSanitizer**  to build **libwav**, this [file](https://github.com/fouzhe/security/blob/master/libwav/wav_gain__crash__infinite_loop) can cause infinite loop in function `wav_read`  when running the  `wav_gain` in folder `tools/wav_gain` with the following command:

```shell
./wav_gain wav_gain__crash__infinite_loop 1.wav
```



Here is the gdb information:

```
(gdb) bt
#0  0x00007ffff6ba7447 in lseek64 () at ../sysdeps/unix/syscall-template.S:84
#1  0x00007ffff6b18571 in _IO_new_file_seekoff (fp=0x61600000fc80, offset=<optimized out>, dir=1, mode=<optimized out>) at fileops.c:1118
#2  0x00007ffff6b15f79 in __GI_fseek (fp=0x61600000fc80, offset=<optimized out>, whence=<optimized out>) at fseek.c:36
#3  0x0000000000401e12 in wav_read (wavfile=0x7fffffffe2c0, filename=0x7fffffffe6f1 "wav_gain__crash__infinite_loop") at ../../libwav.c:268
#4  0x0000000000402121 in gain_file (filename=0x7fffffffe6f1 "wav_gain__crash__infinite_loop", filename_out=0x7fffffffe710 "1.wav") at wav_gain.c:20
#5  0x0000000000402275 in main (argc=3, argv=0x7fffffffe448) at wav_gain.c:43
```







#   SEGV in function print_info in wav_info.c





I use **Clang 6.0 and AddressSanitizer**  to build **libwav**, this [file](https://github.com/fouzhe/security/blob/master/libwav/wav_info__crash__print_info) can cause SEGV signal in function `print_info`  when running the  `wav_info` in folder `tools/wav_info` with the following command:



```shell
./wav_info ./wav_info__crash__print_info
```



This is the ASAN information:

```shell
LibWAV v. 0.0.1 A (c) 2016 - 2017 Marc Volker Dickmann

Riff Type:	�
Format:		0
Channels:	0
Samplerate:	5344226
Bytespersec:	0
Blockalign:	640
Bitwidth:	47712
AddressSanitizer:DEADLYSIGNAL
=================================================================
==32370==ERROR: AddressSanitizer: SEGV on unknown address 0x000026007fef (pc 0x000000424c5f bp 0x7ffcba5ff820 sp 0x7ffcba5ff7c0 T0)
==32370==The signal is caused by a WRITE memory access.
    #0 0x424c5e in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_atomic_clang.h:81
    #1 0x424c5e in __asan::Allocator::AtomicallySetQuarantineFlagIfAllocated(__asan::AsanChunk*, void*, __sanitizer::BufferedStackTrace*) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_allocator.cc:540
    #2 0x424c5e in __asan::Allocator::Deallocate(void*, unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_allocator.cc:617
    #3 0x424c5e in __asan::asan_free(void*, __sanitizer::BufferedStackTrace*, __asan::AllocType) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_allocator.cc:847
    #4 0x4ddf53 in __interceptor_cfree.localalias.0 /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:79
    #5 0x518a82 in print_info /home/fouzhe/my_fuzz/libwav/tools/wav_info/wav_info.c:18:2
    #6 0x518a82 in main /home/fouzhe/my_fuzz/libwav/tools/wav_info/wav_info.c:28
    #7 0x7fb30338e82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #8 0x419f08 in _start (/home/fouzhe/my_fuzz/libwav/tools/wav_info/wav_info+0x419f08)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_atomic_clang.h:81 in bool __sanitizer::atomic_compare_exchange_strong<__sanitizer::atomic_uint8_t>(__sanitizer::atomic_uint8_t volatile*, __sanitizer::atomic_uint8_t::Type*, __sanitizer::atomic_uint8_t::Type, __sanitizer::memory_order)
==32370==ABORTING
```

