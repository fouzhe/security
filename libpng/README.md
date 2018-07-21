#  SEGV in function png_free_data(CVE-2018-14048)



There is a bug in **libpng 1.6.34** when using [pngwriter](https://github.com/pngwriter/pngwriter),which take libpng as dependence. 

There is more information by inferring [this](https://github.com/pngwriter/pngwriter/issues/129)!





# Memory Leak in png2pnm

There is an issue in **png2pnm** in **libpng 1.6** .

Those command can be used to compile png2pnm with **Clang 6.0**:

```
export CFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address" CC=clang-6.0
./autogen.sh
./configure
make
cd contrib/pngminus/

make -f makefile.std
```



The `makefile.std` in folder `contrib/pngminus` should also be modified before the command `make -f makefile.std` as mention in [this comment](https://github.com/glennrp/libpng/issues/238#issuecomment-404487829):



```diff
index 14e25cd64..553bbe354 100644
--- a/contrib/pngminus/makefile.std
+++ b/contrib/pngminus/makefile.std
@@ -2,7 +2,7 @@
 # Linux / Unix
 
 #CC=cc
-CC=gcc
+CC=clang-6.0
 LD=$(CC)
 
 RM=rm -f
@@ -13,18 +13,19 @@ RM=rm -f
 #PNGLIBS = $(PNGPATH)/lib/libpng16.a
 PNGINC = -I../..
 PNGLIB = -L../.. -lpng
-PNGLIBS = ../../libpng.a
+PNGLIBS = ../../.libs/libpng16.a
 
-#ZPATH = /usr/local
-#ZINC = -I$(ZPATH)/include
-#ZLIB = -L$(ZPATH)/lib -lz
+ZPATH = /usr/local
+ZINC = -I$(ZPATH)/include
+ZLIB = -L$(ZPATH)/lib -lz
 #ZLIBS = $(ZPATH)/lib/libz.a
-ZINC = -I../../../zlib
-ZLIB = -L../../../zlib -lz
-ZLIBS = ../../../zlib/libz.a
+#ZINC = -I../../../zlib
+#ZLIB = -L../../../zlib -lz
+#ZLIBS = ../../../zlib/libz.a
 
 CPPFLAGS=$(PNGINC) $(ZINC)
-CFLAGS=
+CFLAGS=-g -fsanitize=address
+LDFLAGS=-fsanitize=address
 LDLIBS=$(PNGLIB) $(ZLIB)
 LDLIBSS=$(PNGLIBS) $(ZLIBS)
 C=.c
@@ -41,19 +42,19 @@ png2pnm$(O): png2pnm$(C)
        $(CC) -c $(CPPFLAGS) $(CFLAGS) png2pnm$(C)
 
 png2pnm$(E): png2pnm$(O)
-       $(LD) $(LDFLAGS) -o png2pnm$(E) png2pnm$(O) $(LDLIBS) -lm
+       $(LD) $(LDFLAGS) -o png2pnm$(E) png2pnm$(O) $(LDLIBS) -lm -lz
 
 png2pnm-static$(E): png2pnm$(O)
-       $(LD) $(LDFLAGS) -o png2pnm-static$(E) png2pnm$(O) $(LDLIBSS) -lm
+       $(LD) $(LDFLAGS) -o png2pnm-static$(E) png2pnm$(O) $(LDLIBSS) -lm -lz
 
 pnm2png$(O): pnm2png$(C)
        $(CC) -c $(CPPFLAGS) $(CFLAGS) pnm2png$(C)
 
 pnm2png$(E): pnm2png$(O)
-       $(LD) $(LDFLAGS) -o pnm2png$(E) pnm2png$(O) $(LDLIBS) -lm
+       $(LD) $(LDFLAGS) -o pnm2png$(E) pnm2png$(O) $(LDLIBS) -lm -lz
 
 pnm2png-static$(E): pnm2png$(O)
-       $(LD) $(LDFLAGS) -o pnm2png-static$(E) pnm2png$(O) $(LDLIBSS) -lm
+       $(LD) $(LDFLAGS) -o pnm2png-static$(E) pnm2png$(O) $(LDLIBSS) -lm -lz
 
 clean:
        $(RM) png2pnm$(O)
```





This [file](https://github.com/fouzhe/security/tree/master/libpng/crash_png2pnm_memory_leak) can cause memory leak when using this command:

```
./png2pnm ./crash_png2pnm_memory_leak crash.pnm
```



This is the ASAN information:

```
libpng error: Read Error
PNG2PNM
Error:  unsuccessful conversion of PNG-image

=================================================================
==15420==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 160 byte(s) in 1 object(s) allocated from:
    #0 0x4de728 in malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x516a2e in png2pnm (/home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/png2pnm+0x516a2e)
    #2 0x516493 in main (/home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/png2pnm+0x516493)
    #3 0x7f48e2cc082f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 2400 byte(s) in 1 object(s) allocated from:
    #0 0x4de728 in malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x5169f0 in png2pnm (/home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/png2pnm+0x5169f0)
    #2 0x516493 in main (/home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/png2pnm+0x516493)
    #3 0x7f48e2cc082f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: 2560 byte(s) leaked in 2 allocation(s).
```





# stack-buffer-overflow in png2pnm in function get_token

There is an issue in **png2pnm** in **libpng 1.6** . It's a stack-buffer-overflow in png2pnm in function get_token.

To compile png2pnm,those command can be used with **Clang 6.0**:

```
export CFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address" CC=clang-6.0
./autogen.sh
./configure
make
cd contrib/pngminus/

make -f makefile.std
```



The `makefile.std` in folder `contrib/pngminus` should also be modified before the command `make -f makefile.std` as mention in [this comment](https://github.com/glennrp/libpng/issues/238#issuecomment-404487829):



```diff
index 14e25cd64..553bbe354 100644
--- a/contrib/pngminus/makefile.std
+++ b/contrib/pngminus/makefile.std
@@ -2,7 +2,7 @@
 # Linux / Unix
 
 #CC=cc
-CC=gcc
+CC=clang-6.0
 LD=$(CC)
 
 RM=rm -f
@@ -13,18 +13,19 @@ RM=rm -f
 #PNGLIBS = $(PNGPATH)/lib/libpng16.a
 PNGINC = -I../..
 PNGLIB = -L../.. -lpng
-PNGLIBS = ../../libpng.a
+PNGLIBS = ../../.libs/libpng16.a
 
-#ZPATH = /usr/local
-#ZINC = -I$(ZPATH)/include
-#ZLIB = -L$(ZPATH)/lib -lz
+ZPATH = /usr/local
+ZINC = -I$(ZPATH)/include
+ZLIB = -L$(ZPATH)/lib -lz
 #ZLIBS = $(ZPATH)/lib/libz.a
-ZINC = -I../../../zlib
-ZLIB = -L../../../zlib -lz
-ZLIBS = ../../../zlib/libz.a
+#ZINC = -I../../../zlib
+#ZLIB = -L../../../zlib -lz
+#ZLIBS = ../../../zlib/libz.a
 
 CPPFLAGS=$(PNGINC) $(ZINC)
-CFLAGS=
+CFLAGS=-g -fsanitize=address
+LDFLAGS=-fsanitize=address
 LDLIBS=$(PNGLIB) $(ZLIB)
 LDLIBSS=$(PNGLIBS) $(ZLIBS)
 C=.c
@@ -41,19 +42,19 @@ png2pnm$(O): png2pnm$(C)
        $(CC) -c $(CPPFLAGS) $(CFLAGS) png2pnm$(C)
 
 png2pnm$(E): png2pnm$(O)
-       $(LD) $(LDFLAGS) -o png2pnm$(E) png2pnm$(O) $(LDLIBS) -lm
+       $(LD) $(LDFLAGS) -o png2pnm$(E) png2pnm$(O) $(LDLIBS) -lm -lz
 
 png2pnm-static$(E): png2pnm$(O)
-       $(LD) $(LDFLAGS) -o png2pnm-static$(E) png2pnm$(O) $(LDLIBSS) -lm
+       $(LD) $(LDFLAGS) -o png2pnm-static$(E) png2pnm$(O) $(LDLIBSS) -lm -lz
 
 pnm2png$(O): pnm2png$(C)
        $(CC) -c $(CPPFLAGS) $(CFLAGS) pnm2png$(C)
 
 pnm2png$(E): pnm2png$(O)
-       $(LD) $(LDFLAGS) -o pnm2png$(E) pnm2png$(O) $(LDLIBS) -lm
+       $(LD) $(LDFLAGS) -o pnm2png$(E) pnm2png$(O) $(LDLIBS) -lm -lz
 
 pnm2png-static$(E): pnm2png$(O)
-       $(LD) $(LDFLAGS) -o pnm2png-static$(E) pnm2png$(O) $(LDLIBSS) -lm
+       $(LD) $(LDFLAGS) -o pnm2png-static$(E) pnm2png$(O) $(LDLIBSS) -lm -lz
 
 clean:
        $(RM) png2pnm$(O)
```



This [file](https://github.com/fouzhe/security/tree/master/libpng/crash_pnm2png_stack_buffer_overflow_get_token) can cause stack-buffer-overflow when using this command:

```shell
./pnm2png crash_pnm2png_stack_buffer_overflow_get_token 1.png
```



This is the ASAN information:

```
=================================================================
==4664==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7ffc0475bdc0 at pc 0x00000051740a bp 0x7ffc0475bcb0 sp 0x7ffc0475bca8
WRITE of size 1 at 0x7ffc0475bdc0 thread T0
    #0 0x517409 in get_token /home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png.c:564:14
    #1 0x517409 in pnm2png /home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png.c:238
    #2 0x5164e5 in main /home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png.c:159:7
    #3 0x7f94071de82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41a3e8 in _start (/home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png+0x41a3e8)

Address 0x7ffc0475bdc0 is located in stack of thread T0 at offset 128 in frame
    #0 0x516c0f in pnm2png /home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png.c:205

  This frame has 18 object(s):
    [32, 40) 'png_ptr' (line 206)
    [64, 72) 'info_ptr' (line 207)
    [96, 100) 'row_bytes' (line 211)
    [112, 128) 'type_token' (line 213) <== Memory access at offset 128 overflows this variable
    [144, 160) 'width_token' (line 214)
    [176, 192) 'height_token' (line 215)
    [208, 224) 'maxval_token' (line 216)
    [240, 244) 'color_type' (line 217)
    [256, 264) 'ul_width' (line 218)
    [288, 296) 'ul_alpha_width' (line 218)
    [320, 328) 'ul_height' (line 219)
    [352, 360) 'ul_alpha_height' (line 219)
    [384, 392) 'ul_maxval' (line 220)
    [416, 420) 'width' (line 221)
    [432, 436) 'height' (line 221)
    [448, 452) 'alpha_width' (line 222)
    [464, 468) 'alpha_height' (line 222)
    [480, 484) 'bit_depth' (line 224)
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
SUMMARY: AddressSanitizer: stack-buffer-overflow /home/fouzhe/my_fuzz/libpng_test/libpng/contrib/pngminus/pnm2png.c:564:14 in get_token
Shadow bytes around the buggy address:
  0x1000008e3760: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000008e3770: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000008e3780: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000008e3790: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000008e37a0: 00 00 00 00 00 00 00 00 f1 f1 f1 f1 00 f2 f2 f2
=>0x1000008e37b0: 00 f2 f2 f2 04 f2 00 00[f2]f2 00 00 f2 f2 00 00
  0x1000008e37c0: f2 f2 00 00 f2 f2 04 f2 00 f2 f2 f2 00 f2 f2 f2
  0x1000008e37d0: 00 f2 f2 f2 00 f2 f2 f2 00 f2 f2 f2 04 f2 04 f2
  0x1000008e37e0: 04 f2 04 f2 04 f3 f3 f3 00 00 00 00 00 00 00 00
  0x1000008e37f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x1000008e3800: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==4664==ABORTING
```

