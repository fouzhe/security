#    Alloc_dealloc_mismatch in function ~HtmlString(CVE-2018-14946)

I use **Clang 6.0 and AddressSanitizer**  to build **pdf2json v0.69**, this [file](https://github.com/fouzhe/security/blob/master/pdf2json/alloc_dealloc_mismatch_~HtmlString.pdf) can cause alloc-dealloc-mismatch with the following command:



```shell
./pdf2json alloc_dealloc_mismatch_~HtmlString.pdf 1.json
```



This is the ASAN information:

```shell
=================================================================
==22708==ERROR: AddressSanitizer: alloc-dealloc-mismatch (malloc vs operator delete) on 0x606000004580
    #0 0x517bd0 in operator delete(void*) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:149
    #1 0x51c1ec in HtmlString::~HtmlString() /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:118:3
    #2 0x52282c in HtmlPage::coalesce() /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:558:10
    #3 0x52a41c in ImgOutputDev::endPage() /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:978:10
    #4 0x78c975 in Gfx::~Gfx() /home/fouzhe/my_fuzz/pdf2json/xpdf/Gfx.cc:530:10
    #5 0x60aa91 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, Links*, int, Catalog*, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/Page.cc:359:3
    #6 0x609810 in Page::display(OutputDev*, double, double, int, int, int, Links*, int, Catalog*, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/Page.cc:265:3
    #7 0x60feb5 in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:319:27
    #8 0x60feb5 in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:332
    #9 0x53c946 in main /home/fouzhe/my_fuzz/pdf2json/src/pdf2json.cc:275:10
    #10 0x7f1f071e482f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #11 0x41b198 in _start (/home/fouzhe/my_fuzz/pdf2json/src/pdf2json+0x41b198)

0x606000004580 is located 0 bytes inside of 64-byte region [0x606000004580,0x6060000045c0)
allocated by thread T0 here:
    #0 0x4df3c8 in __interceptor_malloc /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_malloc_linux.cc:88
    #1 0x8dcbc3 in grealloc /home/fouzhe/my_fuzz/pdf2json/goo/gmem.cc:143:9

SUMMARY: AddressSanitizer: alloc-dealloc-mismatch /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:149 in operator delete(void*)
==22708==HINT: if you don't care about these errors you may set ASAN_OPTIONS=alloc_dealloc_mismatch=0
==22708==ABORTING
```





# Alloc_dealloc_mismatch in function CSStyle(CVE-2018-14947)

I use **Clang 6.0 and AddressSanitizer**  to build **pdf2json v0.69**, this [file](https://github.com/fouzhe/security/blob/master/pdf2json/alloc_dealloc_mismatch_CSStyle.pdf) can cause alloc-dealloc-mismatch with the following command:



```shell
./pdf2json alloc_dealloc_mismatch_CSStyle.pdf 1.json
```



This is the ASAN information:

```shell
=================================================================
==28963==ERROR: AddressSanitizer: alloc-dealloc-mismatch (operator new [] vs operator delete) on 0x603000017230
    #0 0x517bd0 in operator delete(void*) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:149
    #1 0x537741 in XmlFontAccu::CSStyle(int, int) /home/fouzhe/my_fuzz/pdf2json/src/XmlFonts.cc:392:4
    #2 0x523af4 in HtmlPage::dumpAsXML(_IO_FILE*, int, int, int) /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:618:35
    #3 0x52a724 in HtmlPage::dump(_IO_FILE*, int, int, int) /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:712:14
    #4 0x52a724 in ImgOutputDev::endPage() /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:1036
    #5 0x78c975 in Gfx::~Gfx() /home/fouzhe/my_fuzz/pdf2json/xpdf/Gfx.cc:530:10
    #6 0x60aa91 in Page::displaySlice(OutputDev*, double, double, int, int, int, int, int, int, int, Links*, int, Catalog*, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/Page.cc:359:3
    #7 0x609810 in Page::display(OutputDev*, double, double, int, int, int, Links*, int, Catalog*, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/Page.cc:265:3
    #8 0x60feb5 in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:319:27
    #9 0x60feb5 in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:332
    #10 0x53c946 in main /home/fouzhe/my_fuzz/pdf2json/src/pdf2json.cc:275:10
    #11 0x7f619da1082f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #12 0x41b198 in _start (/home/fouzhe/my_fuzz/pdf2json/src/pdf2json+0x41b198)

0x603000017230 is located 0 bytes inside of 20-byte region [0x603000017230,0x603000017244)
allocated by thread T0 here:
    #0 0x517008 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0x53749b in XmlFontAccu::CSStyle(int, int) /home/fouzhe/my_fuzz/pdf2json/src/XmlFonts.cc:363:19
    #2 0x523af4 in HtmlPage::dumpAsXML(_IO_FILE*, int, int, int) /home/fouzhe/my_fuzz/pdf2json/src/ImgOutputDev.cc:618:35

SUMMARY: AddressSanitizer: alloc-dealloc-mismatch /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:149 in operator delete(void*)
==28963==HINT: if you don't care about these errors you may set ASAN_OPTIONS=alloc_dealloc_mismatch=0
==28963==ABORTING
```



# Detected memory leaks

I use **Clang 6.0 and AddressSanitizer**  to build **pdf2json v0.69**, this [file](https://github.com/fouzhe/security/blob/master/pdf2json/detected_memory_leaks.pdf) can cause memory leaks with the following command:



```shell
./pdf2json detected_memory_leaks.pdf 1.json
```



This is the ASAN information:

```shell
=================================================================
==15578==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x516e58 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5e9bcf in GString::copy() /home/fouzhe/my_fuzz/pdf2json/xpdf/./../goo/GString.h:41:28
    #2 0x5e9bcf in GlobalParams::getTextEncodingName() /home/fouzhe/my_fuzz/pdf2json/xpdf/GlobalParams.cc:2256

Direct leak of 16 byte(s) in 1 object(s) allocated from:
    #0 0x516e58 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x6094f1 in Page::getLinks(Catalog*) /home/fouzhe/my_fuzz/pdf2json/xpdf/Page.cc:254:11
    #2 0x60fe2e in PDFDoc::getLinks(int) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:351:34
    #3 0x60fe2e in PDFDoc::displayPage(OutputDev*, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:320
    #4 0x60fe2e in PDFDoc::displayPages(OutputDev*, int, int, double, double, int, int, int, int, int (*)(void*), void*) /home/fouzhe/my_fuzz/pdf2json/xpdf/PDFDoc.cc:332

Indirect leak of 8 byte(s) in 1 object(s) allocated from:
    #0 0x517008 in operator new[](unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:95
    #1 0x8cc5ce in GString::resize(int) /home/fouzhe/my_fuzz/pdf2json/goo/GString.cc:87:9
    #2 0x8cc5ce in GString::GString(GString*) /home/fouzhe/my_fuzz/pdf2json/goo/GString.cc:131

SUMMARY: AddressSanitizer: 40 byte(s) leaked in 3 allocation(s).
```

