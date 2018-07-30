# SEGV in function TextPage::restoreState

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/SEGV_restoreState) can cause SEGV in function TextPage::restoreState when executing this command:

```shell
./pdfalto SEGV_restoreState 1.xml
```

This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==13300==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x0000005addf7 bp 0x0c2c000001c7 sp 0x7fff8c9133e0 T0)
==13300==The signal is caused by a READ memory access.
==13300==Hint: address points to the zero page.
    #0 0x5addf6 in TextPage::restoreState(GfxState*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:5763:21
    #1 0x5addf6 in XmlAltoOutputDev::restoreState(GfxState*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7414
    #2 0x9a6668 in Gfx::execOp(Object*, Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:826:3
    #3 0x9a42b1 in Gfx::go(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:719:12
    #4 0x9a1d1b in Gfx::display(Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:641:3
    #5 0x77c466 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:373:10
    #6 0x77babc in Page::display(OutputDev*, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:321:3
    #7 0x78268e in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:386:27
    #8 0x78268e in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:399
    #9 0x526f9d in PDFDocXrce::displayPages(OutputDev*, _xmlNode*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/src/PDFDocXrce.cc:22:10
    #10 0x529565 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:415:18
    #11 0x7f5e9a57182f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #12 0x41c678 in _start (/home/fouzhe/my_fuzz/pdfalto/pdfalto+0x41c678)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:5763:21 in TextPage::restoreState(GfxState*)
==13300==ABORTING
```



# FPE in function ImageStream::ImageStream

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/FPE_ImageStream) can cause FPE in function ImageStream::ImageStream when executing this command:

```shell
./pdfalto FPE_ImageStream 1.xml
```

This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==4985==ERROR: AddressSanitizer: FPE on unknown address 0x00000079252d (pc 0x00000079252d bp 0x0c0c000006ae sp 0x7ffde533a9d0 T0)
    #0 0x79252c in ImageStream::ImageStream(Stream*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Stream.cc:359:23
    #1 0x5969bc in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6427:43
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28
    #3 0x5ae52f in XmlAltoOutputDev::drawSoftMaskedImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, Stream*, int, int, GfxImageColorMap*, double*, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7460:5
    #4 0x9d94cd in Gfx::doImage(Object*, Stream*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:4447:7
    #5 0x9709a5 in Gfx::opXObject(Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:3980:2
    #6 0x9a6668 in Gfx::execOp(Object*, Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:826:3
    #7 0x9a42b1 in Gfx::go(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:719:12
    #8 0x9a1d1b in Gfx::display(Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:641:3
    #9 0x77c466 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:373:10
    #10 0x77babc in Page::display(OutputDev*, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:321:3
    #11 0x78268e in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:386:27
    #12 0x78268e in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:399
    #13 0x526f9d in PDFDocXrce::displayPages(OutputDev*, _xmlNode*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/src/PDFDocXrce.cc:22:10
    #14 0x529565 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:415:18
    #15 0x7f7dc0f1382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #16 0x41c678 in _start (/home/fouzhe/my_fuzz/pdfalto/pdfalto+0x41c678)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: FPE /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Stream.cc:359:23 in ImageStream::ImageStream(Stream*, int, int, int)
==4985==ABORTING
```



# SEGV in function GfxImageColorMap::getRGB

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/SEGV_getRGB) can cause SEGV in function GfxImageColorMap::getRGB when executing this command:

```shell
./pdfalto SEGV_getRGB 1.xml
```

This is the ASAN information:

```shell
AddressSanitizer:DEADLYSIGNAL
=================================================================
==20699==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000000 (pc 0x000000710e0c bp 0x7ffd9f911d30 sp 0x7ffd9f911be0 T0)
==20699==The signal is caused by a READ memory access.
==20699==Hint: address points to the zero page.
    #0 0x710e0b in GfxImageColorMap::getRGB(unsigned char*, GfxRGB*, GfxRenderingIntent) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/GfxState.cc:3659:30
    #1 0x596afe in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6477:35
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28
    #3 0x5ae4a4 in XmlAltoOutputDev::drawSoftMaskedImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, Stream*, int, int, GfxImageColorMap*, double*, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7458:5
    #4 0x9d94cd in Gfx::doImage(Object*, Stream*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:4447:7
    #5 0x9709a5 in Gfx::opXObject(Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:3980:2
    #6 0x9a6668 in Gfx::execOp(Object*, Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:826:3
    #7 0x9a42b1 in Gfx::go(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:719:12
    #8 0x9a1d1b in Gfx::display(Object*, int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:641:3
    #9 0x77c466 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:373:10
    #10 0x77babc in Page::display(OutputDev*, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:321:3
    #11 0x78268e in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:386:27
    #12 0x78268e in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:399
    #13 0x526f9d in PDFDocXrce::displayPages(OutputDev*, _xmlNode*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/src/PDFDocXrce.cc:22:10
    #14 0x529565 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:415:18
    #15 0x7fc4172c282f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #16 0x41c678 in _start (/home/fouzhe/my_fuzz/pdfalto/pdfalto+0x41c678)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/GfxState.cc:3659:30 in GfxImageColorMap::getRGB(unsigned char*, GfxRGB*, GfxRenderingIntent)
==20699==ABORTING
```





# Infinite loop

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/infinite_loop) can infinite loop when executing this command:

```shell
./pdfalto infinite_loop 1.xml
```





# Heap buffer overflow in function TextPage::dump

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/heap-buffer-overflow_dump) can cause heap buffer overflow in function TextPage::dump when executing this command:

```shell
./pdfalto heap-buffer-overflow_dump 1.xml
```

This is the ASAN information:

```shell
=================================================================
==1865==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x60200047ff5a at pc 0x00000049397b bp 0x7ffd280d7300 sp 0x7ffd280d6ab0
WRITE of size 13 at 0x60200047ff5a thread T0
    #0 0x49397a in vsprintf /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1572
    #1 0x493ad2 in __interceptor_sprintf /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1615
    #2 0x587186 in TextPage::dump(int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:5307:13
    #3 0x5a9de7 in XmlAltoOutputDev::endPage() /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7216:19
    #4 0x9a06eb in Gfx::~Gfx() /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Gfx.cc:590:10
    #5 0x77cd47 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:406:3
    #6 0x77babc in Page::display(OutputDev*, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:321:3
    #7 0x78268e in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:386:27
    #8 0x78268e in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/PDFDoc.cc:399
    #9 0x526f9d in PDFDocXrce::displayPages(OutputDev*, _xmlNode*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdfalto/src/PDFDocXrce.cc:22:10
    #10 0x529565 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:415:18
    #11 0x7f4ca2c9982f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #12 0x41c678 in _start (/home/fouzhe/my_fuzz/pdfalto/pdfalto+0x41c678)

0x60200047ff5a is located 0 bytes to the right of 10-byte region [0x60200047ff50,0x60200047ff5a)
allocated by thread T0 here:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x5821d5 in TextPage::dump(int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:4706:20
    #2 0x5a9de7 in XmlAltoOutputDev::endPage() /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7216:19

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:1572 in vsprintf
Shadow bytes around the buggy address:
  0x0c0480087f90: fa fa fd fa fa fa fd fd fa fa fd fa fa fa 05 fa
  0x0c0480087fa0: fa fa 06 fa fa fa 05 fa fa fa 07 fa fa fa 05 fa
  0x0c0480087fb0: fa fa 06 fa fa fa 06 fa fa fa 07 fa fa fa 07 fa
  0x0c0480087fc0: fa fa 07 fa fa fa 00 02 fa fa 06 fa fa fa 03 fa
  0x0c0480087fd0: fa fa 06 fa fa fa 00 fa fa fa 05 fa fa fa 07 fa
=>0x0c0480087fe0: fa fa 05 fa fa fa 00 fa fa fa 00[02]fa fa 07 fa
  0x0c0480087ff0: fa fa fd fd fa fa fd fd fa fa fd fa fa fa fd fd
  0x0c0480088000: fa fa fd fd fa fa 04 fa fa fa 00 01 fa fa fd fd
  0x0c0480088010: fa fa fd fa fa fa fd fd fa fa 03 fa fa fa 00 fa
  0x0c0480088020: fa fa fd fd fa fa fd fa fa fa 00 00 fa fa 00 fa
  0x0c0480088030: fa fa fd fa fa fa 00 fa fa fa 02 fa fa fa 00 00
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
==1865==ABORTING
```



#Memory Leaks

I used **Clang 6.0 and AddressSanitizer**  to build **[pdfalto](https://github.com/kermitt2/pdfalto)**, this [file](https://github.com/fouzhe/security/pdfalto/detected_memory_leaks) can cause memory leaks when executing this command:

```shell
./pdfalto detected_memory_leaks 1.xml
```

This is the ASAN information:

```
=================================================================
==12842==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 104340 byte(s) in 1 object(s) allocated from:
    #0 0x5184e8 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0x596941 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6423:35
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 104340 byte(s) in 1 object(s) allocated from:
    #0 0x5184e8 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0x596941 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6423:35
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 14000 byte(s) in 14 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff25d7f6 in xmlEncodeEntitiesInternal /home/fouzhe/my_fuzz/libxml2/entities.c:576

Direct leak of 120 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff282dc0 in xmlNewNode__internal_alias /home/fouzhe/my_fuzz/libxml2/tree.c:2239

Direct leak of 84 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0xb378a8 in gmalloc /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/gmem.cc:140:13
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 48 byte(s) in 3 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x52a5e1 in removeAlreadyExistingData(GString*) /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:464:20
    #2 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 48 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff281d6b in xmlNewNs__internal_alias /home/fouzhe/my_fuzz/libxml2/tree.c:757

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59e8d1 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6721:26
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x54021f in TextPage::TextPage(int, Catalog*, _xmlNode*, GString*, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1508:17
    #2 0x59fbc1 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6852:16
    #3 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x544254 in TextPage::startPage(int, GfxState*, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1567:13
    #2 0x5a992b in XmlAltoOutputDev::startPage(int, GfxState*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7200:15

Direct leak of 24 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59b645 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6663:19
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59e7e4 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6708:24
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x77b765 in Page::getLinks() /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/xpdf/Page.cc:311:11
    #2 0x544f81 in TextPage::startPage(int, GfxState*, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1732:30
    #3 0x5a992b in XmlAltoOutputDev::startPage(int, GfxState*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7200:15

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a49a8 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6938:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59e681 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6692:18
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a4c24 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6954:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x540b34 in TextPage::TextPage(int, Catalog*, _xmlNode*, GString*, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1552:23
    #2 0x59fbc1 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6852:16
    #3 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a490c in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6934:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a4b85 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6950:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x540abe in TextPage::TextPage(int, Catalog*, _xmlNode*, GString*, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1551:23
    #2 0x59fbc1 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6852:16
    #3 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a4b85 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6950:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a4c24 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6954:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x595d0d in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6259:24
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a63db in XmlAltoOutputDev::getInfoDate(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7122:19
    #2 0x5a4c8a in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6958:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a63db in XmlAltoOutputDev::getInfoDate(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7122:19
    #2 0x5a4cf0 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6962:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59e5cd in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6687:18
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x529331 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:395:23
    #2 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a4ae5 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6946:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x52902e in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:328:29
    #2 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x595cac in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6255:24
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a4ae5 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6946:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597f8f in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:48
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a4a44 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6942:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a31e6 in XmlAltoOutputDev::toUnicode(GString*, UnicodeMap*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7188:12

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597f75 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:23
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597faa in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:78
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x595cac in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6255:24
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x595cf3 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6257:21
    #3 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x595d4b in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6261:21
    #3 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x595d4b in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6261:21
    #3 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597f75 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:23
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597f8f in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:48
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x597faa in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6497:78
    #2 0x5af0b2 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7547:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x547aff in TextPage::endPage(GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1785:25

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x547bff in TextPage::endPage(GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:1790:25

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a4a44 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6942:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x595d0d in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6259:24
    #2 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0xb23b8c in GString::fromInt(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:186:10
    #2 0x595cf3 in TextPage::drawImageOrMask(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6257:21
    #3 0x5aedb4 in XmlAltoOutputDev::drawImage(GfxState*, Object*, Stream*, int, int, GfxImageColorMap*, int*, int, int) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7535:28

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a55b1 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7080:19
    #2 0x5a49a8 in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6938:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59f1bd in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6783:13
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x59e604 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6689:15
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a5597 in XmlAltoOutputDev::getInfoString(Dict*, char const*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7079:18
    #2 0x5a490c in XmlAltoOutputDev::addMetadataInfo(PDFDocXrce*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6934:19
    #3 0x5292dc in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:388:17
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x518338 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5a750f in XmlAltoOutputDev::closeMetadataInfoDoc(GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6970:33
    #2 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 424 byte(s) in 33 object(s) allocated from:
    #0 0x5184e8 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0xb34fb9 in GString::resize(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:119:9

Indirect leak of 336 byte(s) in 11 object(s) allocated from:
    #0 0x5184e8 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0xb34eba in GString::resize(int) /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/GString.cc:121:10

Indirect leak of 176 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff282754 in xmlNewDoc__internal_alias /home/fouzhe/my_fuzz/libxml2/tree.c:1171

Indirect leak of 120 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff283006 in xmlNewText__internal_alias /home/fouzhe/my_fuzz/libxml2/tree.c:2445

Indirect leak of 120 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff282dc0 in xmlNewNode__internal_alias /home/fouzhe/my_fuzz/libxml2/tree.c:2239

Indirect leak of 120 byte(s) in 2 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0xb378a8 in gmalloc /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/gmem.cc:140:13
    #2 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #3 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

Indirect leak of 96 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff283146 in xmlNewPropInternal /home/fouzhe/my_fuzz/libxml2/tree.c:1855

Indirect leak of 87 byte(s) in 8 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x7fdeff2d8518 in xmlStrndup__internal_alias /home/fouzhe/my_fuzz/libxml2/xmlstring.c:45

Indirect leak of 64 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0xb378a8 in gmalloc /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/gmem.cc:140:13
    #2 0x5a992b in XmlAltoOutputDev::startPage(int, GfxState*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:7200:15

Indirect leak of 64 byte(s) in 1 object(s) allocated from:
    #0 0x4e08a8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0xb378a8 in gmalloc /home/fouzhe/my_fuzz/pdfalto/xpdf-4.00/goo/gmem.cc:140:13
    #2 0x59fbc1 in XmlAltoOutputDev::XmlAltoOutputDev(GString*, GString*, Catalog*, int, int, GString*, GString*) /home/fouzhe/my_fuzz/pdfalto/src/XmlAltoOutputDev.cc:6852:16
    #3 0x5292c5 in main /home/fouzhe/my_fuzz/pdfalto/src/pdfalto.cc:385:22
    #4 0x7fdefdfba82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: 225355 byte(s) leaked in 128 allocation(s).
```

