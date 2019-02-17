# Stack-buffer-overflow in Function mxml_write_node(CVE-2018-20004)

I used **clang 6.0 and AddressSanitizer**  to build **[mxml 2.12](https://github.com/michaelrsweet/mxml)**, this [file](https://github.com/fouzhe/security/blob/master/mxml/Stack-buffer-overflow-mxml_write_node) can cause stack buffer overflow in function mxml_write_node in mxml-file.c when executing this command:

```shell
./testmxml $crash 1.xml
```

This is the ASAN information:

```shell
==6890==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffe99d748ff at pc 0x00000049147b bp 0x7ffe99d746e0 sp 0x7ffe99d73e90
WRITE of size 269 at 0x7ffe99d748ff thread T0
    #0 0x49147a in __interceptor_vsprintf /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1572
    #1 0x4915d2 in __interceptor_sprintf /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1615
    #2 0x53c97c in mxml_write_node /home/fouzhe/my_fuzz/mxml/mxml-file.c:2914:4
    #3 0x53c97c in mxmlSaveFile /home/fouzhe/my_fuzz/mxml/mxml-file.c:339
    #4 0x518e98 in main /home/fouzhe/my_fuzz/mxml/testmxml.c:568:3
    #5 0x7f4e00bb282f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x41a178 in _start (/home/fouzhe/my_fuzz/mxml/testmxml+0x41a178)

Address 0x7ffe99d748ff is located in stack of thread T0 at offset 287 in frame
    #0 0x53b88f in mxmlSaveFile /home/fouzhe/my_fuzz/mxml/mxml-file.c:329

  This frame has 1 object(s):
    [32, 287) 's.i' (line 2727) <== Memory access at offset 287 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1572 in __interceptor_vsprintf
Shadow bytes around the buggy address:
  0x1000533a68c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000533a68d0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000533a68e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000533a68f0: 00 00 00 00 00 00 00 00 00 00 00 00 f1 f1 f1 f1
  0x1000533a6900: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x1000533a6910: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00[07]
  0x1000533a6920: f3 f3 f3 f3 f3 f3 f3 f3 00 00 00 00 00 00 00 00
  0x1000533a6930: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000533a6940: 00 00 00 00 00 00 00 00 f1 f1 f1 f1 00 00 00 00
  0x1000533a6950: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000533a6960: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==6890==ABORTING
```



# SEGV in Function write_element

I used **clang 6.0 and AddressSanitizer**  to build **[mxml 2.12](https://github.com/michaelrsweet/mxml)**, this [file](https://github.com/fouzhe/security/blob/master/mxml/SEGV_write_element) can cause SEGV in function write_element in mxmldoc.c when executing this command:

```shell
./testmxml $crash 1.xml
```

This is the ASAN information:

```shell
==29979==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000038 (pc 0x0000004095a0 bp 0x60800000bf20 sp 0x7ffcc2981e20 T0)
    #0 0x40959f in write_element /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3796
    #1 0x40cf4e in write_html_body /home/fouzhe/my_fuzz/mxml/mxmldoc.c:4790
    #2 0x40e9cb in write_html /home/fouzhe/my_fuzz/mxml/mxmldoc.c:4551
    #3 0x402e35 in main /home/fouzhe/my_fuzz/mxml/mxmldoc.c:602
    #4 0x7f361bffe82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #5 0x402ff8 in _start (/home/fouzhe/my_fuzz/mxml/mxmldoc+0x402ff8)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3796 write_element
```



# Another SEGV in Function write_element

I used **clang 6.0 and AddressSanitizer**  to build **[mxml 2.12](https://github.com/michaelrsweet/mxml)**, this [file](https://github.com/fouzhe/security/blob/master/mxml/SEGV_write_element_2) can cause SEGV in function write_element in mxmldoc.c when executing this command:

```shell
./testmxml $crash 1.xml
```

This is the ASAN information:

```shell
==30934==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000038 (pc 0x0000004095a0 bp 0x60800000bf20 sp 0x7fff5b96eca0 T0)
    #0 0x40959f in write_element /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3796
    #1 0x40c47d in write_scu /home/fouzhe/my_fuzz/mxml/mxmldoc.c:5786
    #2 0x40cdeb in write_html_body /home/fouzhe/my_fuzz/mxml/mxmldoc.c:4748
    #3 0x40e9cb in write_html /home/fouzhe/my_fuzz/mxml/mxmldoc.c:4551
    #4 0x402e35 in main /home/fouzhe/my_fuzz/mxml/mxmldoc.c:602
    #5 0x7f1be4e8c82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x402ff8 in _start (/home/fouzhe/my_fuzz/mxml/mxmldoc+0x402ff8)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3796 write_element
```





# heap-use-after-free in Function mxmlWalkNext(CVE-2018-20005)

I used **clang 6.0 and AddressSanitizer**  to build **[mxml 2.12](https://github.com/michaelrsweet/mxml)**, this [file](https://github.com/fouzhe/security/blob/master/mxml/heap-use-after-free_mxmlWalkNext) can cause heap-use-after-free in mxmlWalkNext in mxml-search.c when executing this command:

```shell
./mxmldoc $crash
```

This is the ASAN information:

```shell
==2544==ERROR: AddressSanitizer: heap-use-after-free on address 0x608000008ec0 at pc 0x7fedf0751729 bp 0x7fff65264ee0 sp 0x7fff65264ed0
READ of size 8 at 0x608000008ec0 thread T0
    #0 0x7fedf0751728 in mxmlWalkNext /home/fouzhe/my_fuzz/mxml/mxml-search.c:212
    #1 0x7fedf075180c in mxmlFindElement /home/fouzhe/my_fuzz/mxml/mxml-search.c:101
    #2 0x405074 in sort_node /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3372
    #3 0x405b5d in scan_file /home/fouzhe/my_fuzz/mxml/mxmldoc.c:1981
    #4 0x402b1d in main /home/fouzhe/my_fuzz/mxml/mxmldoc.c:503
    #5 0x7fedeff5d82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x402ff8 in _start (/home/fouzhe/my_fuzz/mxml/mxmldoc+0x402ff8)

0x608000008ec0 is located 32 bytes inside of 88-byte region [0x608000008ea0,0x608000008ef8)
freed by thread T0 here:
    #0 0x7fedf09f92ca in __interceptor_free (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x982ca)
    #1 0x4050c1 in sort_node /home/fouzhe/my_fuzz/mxml/mxmldoc.c:3389

previously allocated by thread T0 here:
    #0 0x7fedf09f979a in __interceptor_calloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x9879a)
    #1 0x7fedf0750e50 in mxml_new /home/fouzhe/my_fuzz/mxml/mxml-node.c:844

SUMMARY: AddressSanitizer: heap-use-after-free /home/fouzhe/my_fuzz/mxml/mxml-search.c:212 mxmlWalkNext
Shadow bytes around the buggy address:
  0x0c107fff9180: fa fa fa fa 00 00 00 00 00 00 00 00 00 00 00 fa
  0x0c107fff9190: fa fa fa fa 00 00 00 00 00 00 00 00 00 00 00 fa
  0x0c107fff91a0: fa fa fa fa 00 00 00 00 00 00 00 00 00 00 00 fa
  0x0c107fff91b0: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
  0x0c107fff91c0: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
=>0x0c107fff91d0: fa fa fa fa fd fd fd fd[fd]fd fd fd fd fd fd fa
  0x0c107fff91e0: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
  0x0c107fff91f0: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
  0x0c107fff9200: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
  0x0c107fff9210: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
  0x0c107fff9220: fa fa fa fa fd fd fd fd fd fd fd fd fd fd fd fa
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
==2544==ABORTING
```



