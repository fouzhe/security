# Allocate Failure in function openWavFile



I used **gcc 5.4 and AddressSanitizer**  to build **[sound](https://github.com/dilawar/sound/commit/357c2c57e2127dbd996b7e7dce90148f08cf7cbf)**, this [file](https://github.com/fouzhe/security/blob/master/sound/allocate_failure_openWavFile) can cause allocate failure when executing this command:

```shell
./parseSpeech -f allocate_failure_openWavFile
```

This is the ASAN information:

```shell
Input file : allocate_failure_openWavFileSize of chunk8
Size of chunk8
wBufferLength : 4293066752maxInSamples 4293066752
==29066==WARNING: AddressSanitizer failed to allocate 0xffffffffffe30000 bytes
==29066==AddressSanitizer's allocator is terminating the process instead of returning 0
==29066==If you don't like this behavior set allocator_may_return_null=1
==29066==AddressSanitizer CHECK failed: ../../../../src/libsanitizer/sanitizer_common/sanitizer_allocator.cc:147 "((0)) != (0)" (0x0, 0x0)
    #0 0x7f5578ebd631  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0xa0631)
    #1 0x7f5578ec25e3 in __sanitizer::CheckFailed(char const*, int, char const*, unsigned long long, unsigned long long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0xa55e3)
    #2 0x7f5578e3a425  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x1d425)
    #3 0x7f5578ec0865  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0xa3865)
    #4 0x7f5578e3fb4d  (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x22b4d)
    #5 0x7f5578eb667e in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x9967e)
    #6 0x4070d9 in WavFile::openWavFile(char*) /home/fouzhe/my_fuzz/sound/src/wav-file.cc:345
    #7 0x4025c2 in main /home/fouzhe/my_fuzz/sound/main.cc:148
    #8 0x7f55781d282f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #9 0x402a38 in _start (/home/fouzhe/my_fuzz/sound/parseSpeech+0x402a38)
```



# Alloc-dealloc-mismatch in function openWavFile

I used **gcc 5.4 and AddressSanitizer**  to build **[sound](https://github.com/dilawar/sound/commit/357c2c57e2127dbd996b7e7dce90148f08cf7cbf)**, this [file](https://github.com/fouzhe/security/blob/master/sound/alloc_dealloc_mismatch_openWavFile) can cause alloc-dealloc-mismatch when executing this command:

```shell
./parseSpeech -f alloc_dealloc_mismatch_openWavFile
```

This is the ASAN information:

```shell
Input file : alloc_dealloc_mismatch_openWavFileSize of chunk8
wBufferLength : 1080764maxInSamples 1080764
=================================================================
==8789==ERROR: AddressSanitizer: alloc-dealloc-mismatch (operator new [] vs operator delete) on 0x7fcd33711800
    #0 0x7fcd3277cb2a in operator delete(void*) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x99b2a)
    #1 0x407655 in WavFile::openWavFile(char*) /home/fouzhe/my_fuzz/sound/src/wav-file.cc:402
    #2 0x4025c2 in main /home/fouzhe/my_fuzz/sound/main.cc:148
    #3 0x7fcd31a9882f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x402a38 in _start (/home/fouzhe/my_fuzz/sound/parseSpeech+0x402a38)

0x7fcd33711800 is located 0 bytes inside of 1080764-byte region [0x7fcd33711800,0x7fcd338195bc)
allocated by thread T0 here:
    #0 0x7fcd3277c6b2 in operator new[](unsigned long) (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x996b2)
    #1 0x4070d9 in WavFile::openWavFile(char*) /home/fouzhe/my_fuzz/sound/src/wav-file.cc:345

SUMMARY: AddressSanitizer: alloc-dealloc-mismatch ??:0 operator delete(void*)
==8789==HINT: if you don't care about these warnings you may set ASAN_OPTIONS=alloc_dealloc_mismatch=0
==8789==ABORTING
```







