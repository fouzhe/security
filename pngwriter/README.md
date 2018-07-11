#  SEGV in function pngwriter::readfromfile





I use **Clang 6.0 and AddressSanitizer**  to build **pngwriter v0.7.0**, this [file](https://github.com/fouzhe/security/blob/master/pngwriter/crash_SEGV_readfromfile) can cause SEGV signal when running the **test** `blackwhite` in folder `pngwriter-build` with the following command:



```shell
./blackwhite crash_SEGV_readfromfile
```



This is the ASAN information:

```shell
libpng error: Read Error
 PNGwriter::read_png_info - ERROR **: This file may be a corrupted PNG file. (setjmp(*png_ptr)->jmpbf) failed).
 PNGwriter::readfromfile - ERROR **: Error opening file AddressSanitizer:DEADLYSIGNAL
=================================================================
==20801==ERROR: AddressSanitizer: SEGV on unknown address 0x0200856caffc (pc 0x00000047ec5e bp 0x7ffd5b4ffef0 sp 0x7ffd5b4ff680 T0)
==20801==The signal is caused by a READ memory access.
    #0 0x47ec5d in AddressIsPoisoned /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_mapping.h:344
    #1 0x47ec5d in QuickCheckForUnpoisonedRegion /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_interceptors_memintrinsics.h:32
    #2 0x47ec5d in __interceptor_strlen.part.32 /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/../sanitizer_common/sanitizer_common_interceptors.inc:343
    #3 0x5404e3 in std::char_traits<char>::length(char const*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/char_traits.h:267:16
    #4 0x5404e3 in std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ostream:562
    #5 0x5404e3 in pngwriter::readfromfile(char*) /home/fouzhe/my_fuzz/tests/pngwriter/src/pngwriter.cc:1313
    #6 0x51ee9a in main /home/fouzhe/my_fuzz/tests/pngwriter/tests/blackwhite.cc:23:11
    #7 0x7f23bea4382f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #8 0x41e498 in _start (/home/fouzhe/my_fuzz/tests/pngwriter/pngwriter-build/blackwhite+0x41e498)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_mapping.h:344 in AddressIsPoisoned
==20801==ABORTING
```


