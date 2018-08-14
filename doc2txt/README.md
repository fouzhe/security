# Heap Buffer Overflow in Function Storage::init

I used **g++ 5.4 and AddressSanitizer**  to build **[doc2txt](https://github.com/tsfn/doc2txt)**, this [file](https://github.com/fouzhe/security/blob/master/doc2txt/heap-buffer-overflow_init.doc) can cause heap buffer overflow in function Storage::init in Storage.cpp when executing this command(pic is just a folder which is used to store the picture in doc file):

```shell
./doc2txt ./heap-buffer-overflow_init.doc 1.txt ./pic/
```

This is the ASAN information:

```shell
=================================================================
==5702==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x62100001ca1c at pc 0x7f723d545bec bp 0x7fff6a6378f0 sp 0x7fff6a637098
WRITE of size 8760 at 0x62100001ca1c thread T0
    #0 0x7f723d545beb in __asan_memset (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x8cbeb)
    #1 0x404eb2 in memset /usr/include/x86_64-linux-gnu/bits/string3.h:90
    #2 0x404eb2 in Storage::init(_IO_FILE*) src/Storage.cpp:160
    #3 0x406a3e in parse_doc(char const*, char const*, char const*) src/parse_doc.cpp:20
    #4 0x4018b2 in main src/main.cpp:10
    #5 0x7f723cb7782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x401c78 in _start (/home/fouzhe/my_fuzz/doc2txt/doc2txt+0x401c78)

0x62100001ca1c is located 0 bytes to the right of 4380-byte region [0x62100001b900,0x62100001ca1c)
allocated by thread T0 here:
    #0 0x7f723d551602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x404e46 in Storage::init(_IO_FILE*) src/Storage.cpp:156
    #2 0x7fff6a637b9f  (<unknown module>)

SUMMARY: AddressSanitizer: heap-buffer-overflow ??:0 __asan_memset
Shadow bytes around the buggy address:
  0x0c427fffb8f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c427fffb900: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c427fffb910: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c427fffb920: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c427fffb930: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c427fffb940: 00 00 00[04]fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c427fffb950: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c427fffb960: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c427fffb970: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c427fffb980: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c427fffb990: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==5702==ABORTING
```



# Heap Buffer Overflow in Function read_stream

I used **g++ 5.4 and AddressSanitizer**  to build **[doc2txt](https://github.com/tsfn/doc2txt)**, this [file](https://github.com/fouzhe/security/blob/master/doc2txt/heap-buffer-overflow_read_stream.doc) can cause heap buffer overflow in function read_stream in Storage.cpp when executing this command(pic is just a folder which is used to store the picture in doc file):

```shell
./doc2txt heap-buffer-overflow_read_stream.doc 1.txt ./pic/
```

This is the ASAN information:

```shell
=================================================================
==26339==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200000eff4 at pc 0x000000403999 bp 0x7ffe3892a860 sp 0x7ffe3892a850
READ of size 4 at 0x60200000eff4 thread T0
    #0 0x403998 in read_stream src/Storage.cpp:106
    #1 0x404bc3 in Storage::init(_IO_FILE*) src/Storage.cpp:134
    #2 0x406a3e in parse_doc(char const*, char const*, char const*) src/parse_doc.cpp:20
    #3 0x4018b2 in main src/main.cpp:10
    #4 0x7fc57eba682f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #5 0x401c78 in _start (/home/fouzhe/my_fuzz/doc2txt/doc2txt+0x401c78)

0x60200000eff4 is located 3 bytes to the right of 1-byte region [0x60200000eff0,0x60200000eff1)
allocated by thread T0 here:
    #0 0x7fc57f580602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x405209 in read_sat src/Storage.cpp:91
    #2 0x405209 in Storage::init(_IO_FILE*) src/Storage.cpp:130
    #3 0x7ffe3892ac5f  (<unknown module>)

SUMMARY: AddressSanitizer: heap-buffer-overflow src/Storage.cpp:106 read_stream
Shadow bytes around the buggy address:
  0x0c047fff9da0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9db0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dc0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9dd0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9de0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c047fff9df0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa[01]fa
  0x0c047fff9e00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c047fff9e40: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==26339==ABORTING
```



