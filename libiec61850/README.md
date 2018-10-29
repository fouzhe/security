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



