

# Heap buffer overflow in function BerEncoder_encodeOctetString



I used **gcc 5.4 and AddressSanitizer**(`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`)  to build **[libiec61850](https://github.com/mz-automation/libiec61850)**. In the directory `libiec61850/examples/goose_publisher` , the following

 **specific dataSetValue sequence** will cause `heap buffer overflow ` in function `BerEncoder_encodeOctetString` in `ber_encoder.c`:

```c
int j=0;
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<25;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<6;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<6;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));

LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(212));

for(j=0;j<10;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<20;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<10;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<12;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<12;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<19;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
```

However, if the dataSetValue is constructed like following two way, this error will not be triggered. 

```c
int j=0;
for(j=0;j<400;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
```

or

```c
int j=0;
for(j=0;j<5;j++) //modification
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<25;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<6;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<6;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));

LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(212));

for(j=0;j<10;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<20;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<8;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<10;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<12;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<12;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<19;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
```



In detail, the complete version of `goose_publisher_example.c` that triggers `heap buffer overflow` is [here](https://github.com/fouzhe/security/blob/master/libiec61850/goose_publisher_example.c). In order to verify this problem, just replace it with initial `goose_publisher_example.c` in `libiec61850/examples/goose_publisher`, compile it and run it by command `sudo ./goose_publisher_example [interface id]`.



This is the ASAN information:

```shell
==3099==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x61b00001f76e at pc 0x0000004174d3 bp 0x7ffc577e1890 sp 0x7ffc577e1880
WRITE of size 1 at 0x61b00001f76e thread T0
    #0 0x4174d2 in BerEncoder_encodeOctetString src/mms/asn1/ber_encoder.c:122
    #1 0x41be56 in MmsValue_encodeMmsData src/mms/iso_mms/server/mms_access_result.c:384
    #2 0x412dd3 in createGoosePayload src/goose/goose_publisher.c:347
    #3 0x412ea4 in GoosePublisher_publish src/goose/goose_publisher.c:362
    #4 0x40223b in main /home/fouzhe/documents/libiec61850/examples/goose_publisher/goose_publisher_example.c:132
    #5 0x7f58fe16b82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x4017a8 in _start (/home/fouzhe/documents/libiec61850/examples/goose_publisher/goose_publisher_example+0x4017a8)

0x61b00001f76e is located 0 bytes to the right of 1518-byte region [0x61b00001f180,0x61b00001f76e)
allocated by thread T0 here:
    #0 0x7f58fe7ca602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x414612 in Memory_malloc hal/memory/lib_memory.c:47
    #2 0x411ff8 in prepareGooseBuffer src/goose/goose_publisher.c:197
    #3 0x411795 in GoosePublisher_create src/goose/goose_publisher.c:72
    #4 0x4021bf in main /home/fouzhe/documents/libiec61850/examples/goose_publisher/goose_publisher_example.c:121
    #5 0x7f58fe16b82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow src/mms/asn1/ber_encoder.c:122 BerEncoder_encodeOctetString
Shadow bytes around the buggy address:
  0x0c367fffbe90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbea0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbeb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbec0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbed0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c367fffbee0: 00 00 00 00 00 00 00 00 00 00 00 00 00[06]fa fa
  0x0c367fffbef0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==3099==ABORTING
```





# SEGV in function ClientDataSet_getValues

I used **gcc 5.4 and AddressSanitizer**(`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`)  to build **[libiec61850](https://github.com/mz-automation/libiec61850)**. 

First, I run the `server_example_basic_io` in directory `libiec61850/examples/server_example_basic_io` by command `sudo ./server_example_basic_io` so that the server is set up. Then I tested `iec61850_client_example4` in directory `libiec61850/examples/iec61850_client_example4` by command `sudo ./client_example4`. But I got `SEGV` in function  `ClientDataSet_getValues` in `ied_connection.c`.



This is the ASAN information:

```
=================================================================
==13178==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000008 (pc 0x000000412330 bp 0x7ffedff5df40 sp 0x7ffedff5df30 T0)
    #0 0x41232f in ClientDataSet_getValues src/iec61850/client/ied_connection.c:216
    #1 0x402a06 in main /home/fouzhe/libiec61850_pure/libiec61850/examples/iec61850_client_example4/client_example4.c:77
    #2 0x7f8f5eb6682f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #3 0x402658 in _start (/home/fouzhe/libiec61850_pure/libiec61850/examples/iec61850_client_example4/client_example4+0x402658)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV src/iec61850/client/ied_connection.c:216 ClientDataSet_getValues
==13178==ABORTING
```







# SEGV in function ControlObjectClient_setCommandTerminationHandler

I used **gcc 5.4 and AddressSanitizer**(`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`)  to build **[libiec61850](https://github.com/mz-automation/libiec61850)**. 

First, I run the `server_example_basic_io` in directory `libiec61850/examples/server_example_basic_io` by command `sudo ./server_example_basic_io` so that the server is set up. Then I tested `iec61850_client_example_control` in directory `libiec61850/examples/iec61850_client_example_control` by command `sudo ./client_example_control`. But I got `SEGV` in function  `ControlObjectClient_setCommandTerminationHandler` in `client_control.c`.



This is the ASAN information:

```
=================================================================
==16582==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000050 (pc 0x00000044a3d4 bp 0x60800000bfa0 sp 0x7ffd097d60c0 T0)
    #0 0x44a3d3 in ControlObjectClient_setCommandTerminationHandler src/iec61850/client/client_control.c:267
    #1 0x405af2 in main /home/fouzhe/my_fuzz/libiec61850/examples/iec61850_client_example_control/client_example_control.c:191
    #2 0x7f557490f82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #3 0x4093b8 in _start (/home/fouzhe/my_fuzz/libiec61850/examples/iec61850_client_example_control/client_example_control+0x4093b8)
```



# SEGV in function Ethernet_receivePacket

I built **[libiec61850](https://github.com/mz-automation/libiec61850)** in **macOS 10.12.6** with **AddressSanitizer**(`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`).

I ran the `sv_subscriber` in directory `libiec61850/examples/sv_subscriber` by command `sudo ./sv_subscriber`, however, there is a `SEGV` in function `Ethernet_receivePacket` in `ethernet_bsd.c` when the selected interface is unable. 



Here is output with ASAN information:

```
Using interface eth0
Unable to select interface eth0!
Unable to set ethertype filter!
ASAN:DEADLYSIGNAL
=================================================================
==76989==ERROR: AddressSanitizer: SEGV on unknown address 0x00000010 (pc 0x0008b013 bp 0xb078ce68 sp 0xb078cd50 T1)
==76989==The signal is caused by a READ memory access.
==76989==Hint: address points to the zero page.
    #0 0x8b012 in Ethernet_receivePacket ethernet_bsd.c:369
    #1 0x83b2f in SVReceiver_tick sv_subscriber.c:547
    #2 0x8342d in svReceiverLoop sv_subscriber.c:167
    #3 0x8880b in destroyAutomaticThread thread_bsd.c:88
    #4 0x17d185 in __asan::AsanThread::ThreadStart(unsigned long, __sanitizer::atomic_uintptr_t*) (libclang_rt.asan_osx_dynamic.dylib:i386+0x5f185)
    #5 0x16a039 in asan_thread_start(void*) (libclang_rt.asan_osx_dynamic.dylib:i386+0x4c039)
    #6 0xa1754046 in _pthread_body (libsystem_pthread.dylib:i386+0x4046)
    #7 0xa1753f8e in _pthread_start (libsystem_pthread.dylib:i386+0x3f8e)
    #8 0xa1753849 in thread_start (libsystem_pthread.dylib:i386+0x3849)

==76989==Register values:
eax = 0x00000010  ebx = 0x001ff800  ecx = 0x20000002  edx = 0x00000000
edi = 0x018f4000  esi = 0x00000000  ebp = 0xb078ce68  esp = 0xb078cd50
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ethernet_bsd.c:369 in Ethernet_receivePacket
Thread T1 created by T0 here:
    #0 0x169ed3 in wrap_pthread_create (libclang_rt.asan_osx_dynamic.dylib:i386+0x4bed3)
    #1 0x885ea in Thread_start thread_bsd.c:99
    #2 0x8331e in SVReceiver_start sv_subscriber.c:186
    #3 0x7eda9 in main sv_subscriber_example.c:76
    #4 0xa1541394 in start (libdyld.dylib:i386+0x5394)

==76989==ABORTING
Abort trap: 6
```





# SEGV in function Ethernet_sendPacket

I built **[libiec61850](https://github.com/mz-automation/libiec61850)** in **macOS 10.12.6** with **AddressSanitizer**(`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`).

I ran the `sv_publisher` in directory `libiec61850/examples/sv_publisher` by command `sudo ./sv_publisher`, however, there is a `SEGV` in function `Ethernet_sendPacket` in `ethernet_bsd.c` when the selected interface is unable. 



Here is output with ASAN information:

```
Using interface eth0
Could not find the network interface eth0!Unable to select interface eth0!
ASAN:DEADLYSIGNAL
=================================================================
==77056==ERROR: AddressSanitizer: SEGV on unknown address 0x00000000 (pc 0x0004e3bd bp 0xbffe6a18 sp 0xbffe69e0 T0)
==77056==The signal is caused by a READ memory access.
==77056==Hint: address points to the zero page.
    #0 0x4e3bc in Ethernet_sendPacket ethernet_bsd.c:416
    #1 0x4500c in SVPublisher_publish sv_publisher.c:488
    #2 0x1acc7 in main sv_publisher_example.c:70
    #3 0xa1541394 in start (libdyld.dylib:i386+0x5394)

==77056==Register values:
eax = 0x00000000  ebx = 0x00000000  ecx = 0x20000000  edx = 0x00000000
edi = 0x00000000  esi = 0x02f03880  ebp = 0xbffe6a18  esp = 0xbffe69e0
AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV ethernet_bsd.c:416 in Ethernet_sendPacket
==77056==ABORTING
Abort trap: 6
```





#Another heap buffer overflow in function BerEncoder_encodeOctetString

This issue seems to be similiar to [this issue](https://github.com/fouzhe/security/tree/master/libiec61850#heap-buffer-overflow-in-function-berencoder_encodeoctetstring) which is reported several days ago. Although this bug has been fixed, there is  **another specific dataSetValue sequence** which can cause heap buffer overflow in another trace. 

The following is the special sequence and the complete version of `goose_publisher_example.c` that triggers `heap buffer overflow` is [here](https://github.com/fouzhe/security/blob/master/libiec61850/goose_publisher_example_2.c).

```C
int j=0;
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<28;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(1));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(0));
for(j=0;j<5;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<7;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(1));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
LinkedList_add(dataSetValues, MmsValue_newIntegerFromInt32(0));
for(j=0;j<4;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<3;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
for(j=0;j<1;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(false));
for(j=0;j<2;j++)
LinkedList_add(dataSetValues, MmsValue_newBinaryTime(true));
```



Here is the ASAN information:

```shell
=================================================================
==13400==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x61b00001f76e at pc 0x00000045624c bp 0x7fff45a10840 sp 0x7fff45a10830
WRITE of size 1 at 0x61b00001f76e thread T0
    #0 0x45624b in BerEncoder_encodeOctetString src/mms/asn1/ber_encoder.c:122
    #1 0x4477f3 in createGoosePayload src/goose/goose_publisher.c:347
    #2 0x4477f3 in GoosePublisher_publish src/goose/goose_publisher.c:362
    #3 0x402baf in main /home/fouzhe/my_fuzz/libiec61850/examples/goose_publisher/goose_publisher_example.c:253
    #4 0x7fc57f71782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #5 0x4032c8 in _start (/home/fouzhe/my_fuzz/libiec61850/examples/goose_publisher/goose_publisher_example+0x4032c8)

0x61b00001f76e is located 0 bytes to the right of 1518-byte region [0x61b00001f180,0x61b00001f76e)
allocated by thread T0 here:
    #0 0x7fc57fd76602 in malloc (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x98602)
    #1 0x44b610 in Memory_malloc hal/memory/lib_memory.c:47

SUMMARY: AddressSanitizer: heap-buffer-overflow src/mms/asn1/ber_encoder.c:122 BerEncoder_encodeOctetString
Shadow bytes around the buggy address:
  0x0c367fffbe90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbea0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbeb0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbec0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c367fffbed0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c367fffbee0: 00 00 00 00 00 00 00 00 00 00 00 00 00[06]fa fa
  0x0c367fffbef0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf10: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf20: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c367fffbf30: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07
  Heap left redzone:       fa
  Heap right redzone:      fb
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack partial redzone:   f4
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
==13400==ABORTING
```

