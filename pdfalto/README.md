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

