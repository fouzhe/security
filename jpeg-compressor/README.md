# global_buffer_overflow

I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_global_buffer_overflow) can cause global-buffer-overflow when executing this command:

```
./encoder ./crash_global_buffer_overflow 1.jpeg 50
```



This is the ASAN information:

```
==31440==ERROR: AddressSanitizer: global-buffer-overflow on address 0x000000734f4c at pc 0x00000068bcd5 bp 0x7ffd7d4e8a00 sp 0x7ffd7d4e89f8
READ of size 4 at 0x000000734f4c thread T0
    #0 0x68bcd4 in extend_receive(jpeg*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1120:26
    #1 0x68bcd4 in decode_block(jpeg*, short*, huffman*, huffman*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1164
    #2 0x5e3631 in parse_entropy_coded_data(jpeg*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1399:27
    #3 0x5e3631 in decode_jpeg_image(jpeg*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1626
    #4 0x5e3631 in load_jpeg_image(jpeg*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1812
    #5 0x5e3631 in stbi_jpeg_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1908
    #6 0x5e3631 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:532
    #7 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #8 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #9 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #10 0x7f3d5c57582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #11 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

0x000000734f4c is located 20 bytes to the left of global variable '<string literal>' defined in './stb_image.c:1102:4' (0x734f60) of size 76
  '<string literal>' is ascii string '(((j->code_buffer) >> (32 - h->size[c])) & bmask[h->size[c]]) == h->code[c]'
0x000000734f4c is located 40 bytes to the right of global variable 'bmask' defined in './stb_image.c:1058:15' (0x734ee0) of size 68
SUMMARY: AddressSanitizer: global-buffer-overflow /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1120:26 in extend_receive(jpeg*, int)
Shadow bytes around the buggy address:
  0x0000800de990: f9 f9 f9 f9 00 02 f9 f9 f9 f9 f9 f9 00 01 f9 f9
  0x0000800de9a0: f9 f9 f9 f9 00 05 f9 f9 f9 f9 f9 f9 00 00 00 f9
  0x0000800de9b0: f9 f9 f9 f9 00 04 f9 f9 f9 f9 f9 f9 00 04 f9 f9
  0x0000800de9c0: f9 f9 f9 f9 00 04 f9 f9 f9 f9 f9 f9 00 f9 f9 f9
  0x0000800de9d0: f9 f9 f9 f9 00 00 01 f9 f9 f9 f9 f9 00 00 00 00
=>0x0000800de9e0: 00 00 00 00 04 f9 f9 f9 f9[f9]f9 f9 00 00 00 00
  0x0000800de9f0: 00 00 00 00 00 04 f9 f9 f9 f9 f9 f9 00 06 f9 f9
  0x0000800dea00: f9 f9 f9 f9 00 00 00 06 f9 f9 f9 f9 00 04 f9 f9
  0x0000800dea10: f9 f9 f9 f9 00 06 f9 f9 f9 f9 f9 f9 00 05 f9 f9
  0x0000800dea20: f9 f9 f9 f9 00 02 f9 f9 f9 f9 f9 f9 00 02 f9 f9
  0x0000800dea30: f9 f9 f9 f9 00 00 f9 f9 f9 f9 f9 f9 00 00 02 f9
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
==31440==ABORTING
```



# stack-buffer-overflow in function build_huffman

I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_stack_buffer_overflow) can cause stack-buffer-overflow in function "build_huffman" when executing this command:

```
./encoder ./crash_stack_buffer_overflow 1.jpeg 50
```



This is the ASAN information:

```
==26257==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffc7bb25690 at pc 0x00000068231d bp 0x7ffc7bb1d130 sp 0x7ffc7bb1d128
WRITE of size 1 at 0x7ffc7bb25690 thread T0
    #0 0x68231c in build_huffman(huffman*, int*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1005:23
    #1 0x67c315 in process_marker(jpeg*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1474:21
    #2 0x5ded36 in decode_jpeg_image(jpeg*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1641:15
    #3 0x5ded36 in load_jpeg_image(jpeg*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1812
    #4 0x5ded36 in stbi_jpeg_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1908
    #5 0x5ded36 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:532
    #6 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #7 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #8 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #9 0x7fd19a50a82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #10 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

Address 0x7ffc7bb25690 is located in stack of thread T0 at offset 33680 in frame
    #0 0x5d90bf in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:531

  This frame has 11 object(s):
    [32, 62) 'packets.i.i.i' (line 3695)
    [96, 100) 'value.i.i.i' (line 3240)
    [112, 116) 'value75.i.i.i' (line 3769)
    [128, 18648) 'g.i' (line 4172)
    [18912, 18944) 'p.i' (line 2851)
    [18976, 19104) 'data.i.i.i.i' (line 1359)
    [19136, 19264) 'data54.i.i.i.i' (line 1387)
    [19296, 19328) 'coutput.i.i' (line 1827)
    [19360, 19552) 'res_comp.i.i' (line 1829)
    [19616, 33680) 'j.i71' (line 1906) <== Memory access at offset 33680 overflows this variable
    [33936, 48000) 'j.i' (line 1914)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1005:23 in build_huffman(huffman*, int*)
Shadow bytes around the buggy address:
  0x10000f75ca80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10000f75ca90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10000f75caa0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10000f75cab0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x10000f75cac0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x10000f75cad0: 00 00[f2]f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2
  0x10000f75cae0: f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2
  0x10000f75caf0: f2 f2 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x10000f75cb00: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x10000f75cb10: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x10000f75cb20: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
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
==26257==ABORTING
```





# heap-buffer-overflow in function bmp_load

I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_heap_buffer_overflow_in_bmp_load) can cause heap_buffer_overflow when executing this command:

```
./encoder crash_heap_buffer_overflow_in_bmp_load 1.jpeg 50
```



This is the ASAN information:

```
==4982==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x61f000000c80 at pc 0x000000703602 bp 0x7ffd1c738dd0 sp 0x7ffd1c738dc8
WRITE of size 1 at 0x61f000000c80 thread T0
    #0 0x703601 in bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3059:22
    #1 0x5dc310 in stbi_bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3144:11
    #2 0x5dc310 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:534
    #3 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #4 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #5 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #6 0x7fe2be26882f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #7 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

0x61f000000c80 is located 0 bytes to the right of 3072-byte region [0x61f000000080,0x61f000000c80)
allocated by thread T0 here:
    #0 0x4dec48 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x6e7d99 in bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3035:22
    #2 0x5dc310 in stbi_bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3144:11
    #3 0x5dc310 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:534
    #4 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #5 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #6 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #7 0x7fe2be26882f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3059:22 in bmp_load(stbi*, int*, int*, int*, int)
Shadow bytes around the buggy address:
  0x0c3e7fff8140: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c3e7fff8150: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c3e7fff8160: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c3e7fff8170: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c3e7fff8180: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c3e7fff8190:[fa]fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c3e7fff81a0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c3e7fff81b0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c3e7fff81c0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c3e7fff81d0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c3e7fff81e0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==4982==ABORTING
```





# negative-size-param in function getn



I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_negative_size_param_in_getn) can cause negative_size_param when executing this command:

```
./encoder crash_negative_size_param_in_getn 1.jpeg 50
```



This is the ASAN information:

```
==481==ERROR: AddressSanitizer: negative-size-param: (size=-2147483551)
    #0 0x4dd9b3 in __asan_memcpy /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_interceptors_memintrinsics.cc:23
    #1 0x6977a4 in getn(stbi*, unsigned char*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:783:7
    #2 0x6977a4 in parse_png_file(png*, int, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2770
    #3 0x5dd857 in do_png(png*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2830:8
    #4 0x5dd857 in stbi_png_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2853
    #5 0x5dd857 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:533
    #6 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #7 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #8 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #9 0x7fec3fc1b82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #10 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

Address 0x7fff6fce2c91 is located in stack of thread T0 at offset 465 in frame
    #0 0x668dbf in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:263

  This frame has 22 object(s):
    [32, 240) 's.i.i172'
    [304, 512) 's.i.i164' <== Memory access at offset 465 is inside this variable
    [576, 784) 's.i.i'
    [848, 1056) 's.i.i.i'
    [1120, 1124) 'width.i' (line 169)
    [1136, 1140) 'height.i' (line 169)
    [1152, 1156) 'actual_comps.i' (line 169)
    [1168, 1180) 'params.i' (line 196)
    [1200, 1204) 'comp_size.i' (line 200)
    [1216, 1220) 'uncomp_width.i' (line 206)
    [1232, 1236) 'uncomp_height.i' (line 206)
    [1248, 1252) 'uncomp_actual_comps.i' (line 206)
    [1264, 1304) 'results.i' (line 222)
    [1344, 1348) 'width' (line 344)
    [1360, 1364) 'height' (line 344)
    [1376, 1380) 'actual_comps' (line 344)
    [1392, 1404) 'params' (line 354)
    [1424, 1428) 'buf_size' (line 360)
    [1440, 1444) 'uncomp_width' (line 399)
    [1456, 1460) 'uncomp_height' (line 399)
    [1472, 1476) 'uncomp_actual_comps' (line 399)
    [1488, 1528) 'results' (line 419)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: negative-size-param /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_interceptors_memintrinsics.cc:23 in __asan_memcpy
==481==ABORTING
```





# SEGV in function bmp_load



I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_SEGV_in_bmp_load) can cause SEGV signal when executing this command:

```
./encoder ./crash_SEGV_in_bmp_load 1.jpeg 50
```



This is the ASAN information:

```
==23080==ERROR: AddressSanitizer: SEGV on unknown address 0x61f0c0000c20 (pc 0x0000006efc77 bp 0x7ffca587f770 sp 0x7ffca587f100 T0)
==23080==The signal is caused by a READ memory access.
    #0 0x6efc76 in bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3126:32
    #1 0x5dc310 in stbi_bmp_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3144:11
    #2 0x5dc310 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:534
    #3 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #4 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #5 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #6 0x7fc049a9f82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #7 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:3126:32 in bmp_load(stbi*, int*, int*, int*, int)
==23080==ABORTING
```





# SEGV in function parse_png_file

I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_SEGV_in_parse_png_file) can cause SEGV signal when executing this command:

```
./encoder ./crash_SEGV_in_parse_png_file 1.jpeg 50
```



This is the ASAN information:

```
==3565==ERROR: AddressSanitizer: SEGV on unknown address 0x7ffc58f560ee (pc 0x0000006938e4 bp 0x7ffcd8f4a050 sp 0x7ffcd8f48940 T0)
==3565==The signal is caused by a READ memory access.
    #0 0x6938e3 in parse_png_file(png*, int, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:731:28
    #1 0x5dd857 in do_png(png*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2830:8
    #2 0x5dd857 in stbi_png_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2853
    #3 0x5dd857 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:533
    #4 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #5 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #6 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #7 0x7f64ea27e82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #8 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:731:28 in parse_png_file(png*, int, int)
==3565==ABORTING
```







# stack_buffer_overflow in function do_zlib

I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash_stack_buffer_overflow_in_do_zlib) can cause stack-buffer-overflow when executing this command:

```
./encoder crash_stack_buffer_overflow_in_do_zlib 1.jpeg 50
```



This is the ASAN information:



```
==27287==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffc9a45e30f at pc 0x00000064ac90 bp 0x7ffc9a45da70 sp 0x7ffc9a45da68
READ of size 1 at 0x7ffc9a45e30f thread T0
    #0 0x64ac8f in do_zlib(zbuf*, char*, int, int, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2183:29
    #1 0x69eb5d in stbi_zlib_decode_malloc_guesssize_headerflag(char const*, int, int, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2327:8
    #2 0x69eb5d in parse_png_file(png*, int, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2780
    #3 0x5dd857 in do_png(png*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2830:8
    #4 0x5dd857 in stbi_png_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2853
    #5 0x5dd857 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:533
    #6 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #7 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #8 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #9 0x7fafb5fb282f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #10 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

Address 0x7ffc9a45e30f is located in stack of thread T0 at offset 2191 in frame
    #0 0x64213f in do_zlib(zbuf*, char*, int, int, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2290

  This frame has 4 object(s):
    [32, 2052) 'z_codelength.i.i' (line 2159)
    [2192, 2647) 'lencodes.i.i' (line 2160) <== Memory access at offset 2191 underflows this variable
    [2720, 2739) 'codelength_sizes.i.i' (line 2161)
    [2784, 2788) 'header.i.i' (line 2204)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:2183:29 in do_zlib(zbuf*, char*, int, int, int)
Shadow bytes around the buggy address:
  0x100013483c10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c20: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c30: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c40: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c50: 04 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2
=>0x100013483c60: f2[f2]00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c70: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100013483c90: 00 00 00 00 00 00 00 00 00 00 07 f2 f2 f2 f2 f2
  0x100013483ca0: f2 f2 f2 f2 00 00 03 f2 f2 f2 f2 f2 f8 f3 f3 f3
  0x100013483cb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==27287==ABORTING
```





