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
