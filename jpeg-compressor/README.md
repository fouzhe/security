I use **Clang 6.0 and AddressSanitizer**  to build **jpeg-compressor v0.1**, this [file](https://github.com/fouzhe/security/blob/master/jpeg-compressor/crash) can cause global-buffer-overflow when executing this command:

```
./encoder crash 1.jpeg 50
```



This is the ASAN information:

```
==15244==ERROR: AddressSanitizer: global-buffer-overflow on address 0x000000734f4c at pc 0x00000068bcd5 bp 0x7ffe7fccbac0 sp 0x7ffe7fccbab8
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
    #10 0x7fb352a3582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
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
==15244==ABORTING
```







```
=================================================================
==23160==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffda4c5beb0 at pc 0x00000068231d bp 0x7ffda4c53950 sp 0x7ffda4c53948
WRITE of size 1 at 0x7ffda4c5beb0 thread T0
    #0 0x68231c in build_huffman(huffman*, int*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1005:23
    #1 0x67c315 in process_marker(jpeg*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1474:21
    #2 0x5ded36 in decode_jpeg_image(jpeg*) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1641:15
    #3 0x5ded36 in load_jpeg_image(jpeg*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1812
    #4 0x5ded36 in stbi_jpeg_load(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:1908
    #5 0x5ded36 in stbi_load_main(stbi*, int*, int*, int*, int) /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:532
    #6 0x66a0ab in stbi_load_from_file /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:567:11
    #7 0x66a0ab in stbi_load /home/fouzhe/my_fuzz/jpeg-compressor/./stb_image.c:558
    #8 0x66a0ab in main /home/fouzhe/my_fuzz/jpeg-compressor/encoder.cpp:345
    #9 0x7fc447b4d82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #10 0x41aa18 in _start (/home/fouzhe/my_fuzz/jpeg-compressor/encoder+0x41aa18)

Address 0x7ffda4c5beb0 is located in stack of thread T0 at offset 33680 in frame
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
  0x100034983780: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x100034983790: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000349837a0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000349837b0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000349837c0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x1000349837d0: 00 00 00 00 00 00[f2]f2 f2 f2 f2 f2 f2 f2 f2 f2
  0x1000349837e0: f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2 f2
  0x1000349837f0: f2 f2 f2 f2 f2 f2 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x100034983800: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x100034983810: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
  0x100034983820: f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8 f8
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
==23160==ABORTING
```

