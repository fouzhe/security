# Stack-buffer-overflow in Function mxml_write_node

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



