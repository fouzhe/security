#  SEGV in function png_free_data



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

