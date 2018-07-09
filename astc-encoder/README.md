###  Memory leak



I use **g++ 5.4.0 and AddressSanitizer**  to build **astc-encoder v1.4**, this [file](https://github.com/fouzhe/security/blob/master/astc-encoder/pngtest.png) can cause memory leak when executing this command:



```shell
./astcenc -c pngtest.png 1.astc 6x6 -medium
```



This is the ASAN information:

```shell
Encoding settings:

2D Block size: 6x6 (3.56 bpp)
3D Block size: 6x6x1 (3.56 bpp)
Radius for mean-and-stdev calculations: 0 texels
RGB power: 1
RGB base-weight: 1
RGB local-mean weight: 0
RGB local-stdev weight: 0
RGB mean-and-stdev mixing across color channels: 0
Alpha power: 1
Alpha base-weight: 1
Alpha local-mean weight: 0
Alpha local-stdev weight: 0
RGB weights scale with alpha: disabled
Color channel relative weighting: R=1 G=1 B=1 A=1
Block-artifact suppression parameter : 0
Number of distinct partitionings to test: 25 (preset)
PSNR decibel limit: 2D: 40.529411 3D: 40.529411 (preset)
1->2 partition limit: 1.200000
Dual-plane color-correlation cutoff: 0.750000 (preset)
Block Mode Percentile Cutoff: 75.000000 (preset)
Max refinement iterations: 2 (preset)
Thread count : 8 (autodetected)

pngtest.png: 2D LDR image, 91 x 69 x 1, 4 components

192 blocks to process ..
183
=================================================================
==7141==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 8 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b546b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x4c24d6 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2321
    #2 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 4 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b546b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x4c24a3 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2320
    #2 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 25116 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b546b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x4773fb in allocate_image(int, int, int, int, int) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:63
    #2 0x4a34bc in load_image_with_stb(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_stb_tga.cpp:72
    #3 0x482334 in astc_codec_load_image(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:1328
    #4 0x4c2550 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2329
    #5 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 552 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b546b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x477372 in allocate_image(int, int, int, int, int) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:62
    #2 0x4a34bc in load_image_with_stb(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_stb_tga.cpp:72
    #3 0x482334 in astc_codec_load_image(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:1328
    #4 0x4c2550 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2329
    #5 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 32 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b54532 in operator new(unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x99532)
    #1 0x4771a1 in allocate_image(int, int, int, int, int) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:49
    #2 0x4a34bc in load_image_with_stb(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_stb_tga.cpp:72
    #3 0x482334 in astc_codec_load_image(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:1328
    #4 0x4c2550 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2329
    #5 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 8 byte(s) in 1 object(s) allocated from:
    #0 0x7f6a08b546b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x477313 in allocate_image(int, int, int, int, int) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:61
    #2 0x4a34bc in load_image_with_stb(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_stb_tga.cpp:72
    #3 0x482334 in astc_codec_load_image(char const*, int, int*) /home/fouzhe/my_fuzz/astc-encoder/Source/astc_image_load_store.cpp:1328
    #4 0x4c2550 in main /home/fouzhe/my_fuzz/astc-encoder/Source/astc_toplevel.cpp:2329
    #5 0x7f6a07c5382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: 25720 byte(s) leaked in 6 allocation(s).

```

