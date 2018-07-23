# Allocate Failure



I used **Clang 6.0 and AddressSanitizer**  to build **jpeg-encoder**, this [file](https://github.com/fouzhe/security/blob/master/jpeg_encoder/allocate_failure_readFromBMP) can cause allocate failure when executing this command:

```shell
./a.out allocate_failure_readFromBMP
```

This is the ASAN information:

```shell
==7094==WARNING: AddressSanitizer failed to allocate 0xffffffffffa00000 bytes
==7094==AddressSanitizer's allocator is terminating the process instead of returning 0
==7094==If you don't like this behavior set allocator_may_return_null=1
==7094==AddressSanitizer CHECK failed: /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/sanitizer_common/sanitizer_allocator.cc:225 "((0)) != (0)" (0x0, 0x0)
    #0 0x4e7d5f in __asan::AsanCheckFailed(char const*, int, char const*, unsigned long long, unsigned long long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_rtl.cc:69
    #1 0x504ce5 in __sanitizer::CheckFailed(char const*, int, char const*, unsigned long long, unsigned long long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/sanitizer_common/sanitizer_termination.cc:79
    #2 0x4edb86 in __sanitizer::ReportAllocatorCannotReturnNull() /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/sanitizer_common/sanitizer_allocator.cc:225
    #3 0x4edbc3 in __sanitizer::ReturnNullOrDieOnFailure::OnBadRequest() /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/sanitizer_common/sanitizer_allocator.cc:241
    #4 0x4248c7 in __asan::asan_memalign(unsigned long, unsigned long, __sanitizer::BufferedStackTrace*, __asan::AllocType) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_allocator.cc:900
    #5 0x516478 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #6 0x51c396 in JpegEncoder::readFromBMP(char const*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:193:27
    #7 0x51a88b in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:16:14
    #8 0x7f3acf0b082f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #9 0x41a638 in _start (/home/fouzhe/my_fuzz/jpeg_encoder/a.out+0x41a638)
```



# SEGV in function readFromBMP

I used **Clang 6.0 and AddressSanitizer**  to build **jpeg-encoder**, this [file](https://github.com/fouzhe/security/blob/master/jpeg_encoder/SEGV_readFromBMP) can cause SEGV in function readFromBMP when executing this command:

```shell
./a.out SEGV_readFromBMP
```

This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==26187==ERROR: AddressSanitizer: SEGV on unknown address 0x602003000010 (pc 0x7f6485b4a3f2 bp 0x000000000018 sp 0x7ffe77d368f8 T0)
==26187==The signal is caused by a WRITE memory access.
    #0 0x7f6485b4a3f1  (/lib/x86_64-linux-gnu/libc.so.6+0x8f3f1)
    #1 0x7f6485b3403d  (/lib/x86_64-linux-gnu/libc.so.6+0x7903d)
    #2 0x7f6485b29235 in fread (/lib/x86_64-linux-gnu/libc.so.6+0x6e235)
    #3 0x49e7e6 in fread /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:977
    #4 0x51c515 in JpegEncoder::readFromBMP(char const*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:202:17
    #5 0x51a88b in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:16:14
    #6 0x7f6485adb82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #7 0x41a638 in _start (/home/fouzhe/my_fuzz/jpeg_encoder/a.out+0x41a638)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV (/lib/x86_64-linux-gnu/libc.so.6+0x8f3f1)
==26187==ABORTING
```



# SEGV in function _convertColorSpace

I used **Clang 6.0 and AddressSanitizer**  to build **jpeg-encoder**, this [file](https://github.com/fouzhe/security/blob/master/jpeg_encoder/SEGV__convertColorSpace) can cause SEGV in function _convertColorSpace when executing this command:

```shell
./a.out SEGV__convertColorSpace
```

This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==1347==ERROR: AddressSanitizer: SEGV on unknown address 0x60ffc0000058 (pc 0x0000005201c0 bp 0x000000000000 sp 0x7fffa96a3330 T0)
==1347==The signal is caused by a READ memory access.
    #0 0x5201bf in JpegEncoder::_convertColorSpace(int, int, char*, char*, char*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:471:22
    #1 0x51d671 in JpegEncoder::encodeToJPG(char const*, int) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:256:4
    #2 0x51a8e1 in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:21:14
    #3 0x7f60ad83082f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41a638 in _start (/home/fouzhe/my_fuzz/jpeg_encoder/a.out+0x41a638)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:471:22 in JpegEncoder::_convertColorSpace(int, int, char*, char*, char*)
==1347==ABORTING
```





# heap-buffer-overflow in function readFromBMP

I used **Clang 6.0 and AddressSanitizer**  to build **jpeg-encoder**, this [file](https://github.com/fouzhe/security/blob/master/jpeg_encoder/heap_buffer_overflow_readFromBMP) can cause heap-buffer-overflow in function readFromBMP when executing this command:

```shell
./a.out heap_buffer_overflow_readFromBMP
```

This is the ASAN information:

```shell
=================================================================
==328==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x616000000368 at pc 0x00000049ea5c bp 0x7fff6b99bdb0 sp 0x7fff6b99b560
WRITE of size 24 at 0x616000000368 thread T0
    #0 0x49ea5b in fread /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:978
    #1 0x51c515 in JpegEncoder::readFromBMP(char const*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:202:17
    #2 0x51a88b in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:16:14
    #3 0x7f7a716a882f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41a638 in _start (/home/fouzhe/my_fuzz/jpeg_encoder/a.out+0x41a638)

0x616000000368 is located 192 bytes to the right of 552-byte region [0x616000000080,0x6160000002a8)
allocated by thread T0 here:
    #0 0x4de868 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7f7a716f5cdc  (/lib/x86_64-linux-gnu/libc.so.6+0x6dcdc)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:978 in fread
Shadow bytes around the buggy address:
  0x0c2c7fff8010: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8050: 00 00 00 00 00 fa fa fa fa fa fa fa fa fa fa fa
=>0x0c2c7fff8060: fa fa fa fa fa fa fa fa fa fa fa fa fa[fa]fa fa
  0x0c2c7fff8070: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8080: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff8090: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff80a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c2c7fff80b0: 00 00 00 00 00 00 00 00 fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==328==ABORTING
```





# heap-buffer-overflow in function _convertColorSpace

I used **Clang 6.0 and AddressSanitizer**  to build **jpeg-encoder**, this [file](https://github.com/fouzhe/security/blob/master/jpeg_encoder/heap_buffer_overflow__convertColorSpace) can cause heap-buffer-overflow in function _convertColorSpace when executing this command:

```shell
./a.out heap_buffer_overflow__convertColorSpace
```

This is the ASAN information:

```shell
=================================================================
==3638==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000000011 at pc 0x000000522018 bp 0x7ffe3bab8540 sp 0x7ffe3bab8538
READ of size 1 at 0x602000000011 thread T0
    #0 0x522017 in JpegEncoder::_convertColorSpace(int, int, char*, char*, char*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:472:22
    #1 0x51d671 in JpegEncoder::encodeToJPG(char const*, int) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:256:4
    #2 0x51a8e1 in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:21:14
    #3 0x7f7f579b782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41a638 in _start (/home/fouzhe/my_fuzz/jpeg_encoder/a.out+0x41a638)

0x602000000011 is located 0 bytes to the right of 1-byte region [0x602000000010,0x602000000011)
allocated by thread T0 here:
    #0 0x5164a8 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0x51c396 in JpegEncoder::readFromBMP(char const*) /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:193:27
    #2 0x51a88b in main /home/fouzhe/my_fuzz/jpeg_encoder/test.cpp:16:14
    #3 0x7f7f579b782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/my_fuzz/jpeg_encoder/jpeg_encoder.cpp:472:22 in JpegEncoder::_convertColorSpace(int, int, char*, char*, char*)
Shadow bytes around the buggy address:
  0x0c047fff7fb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c047fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c047fff8000: fa fa[01]fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8020: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8030: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8040: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff8050: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==3638==ABORTING
```











