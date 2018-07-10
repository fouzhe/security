#  Assert Failure





I use **clang 6.0 and AddressSanitizer**  to build **wav2json**, this [file](https://github.com/fouzhe/security/blob/master/wav2json/crash.wav) can cause assert failure when executing this command:



```shell
./wav2json crash.wav -p 3 --channels left right mid side min max -o song.json
```



This is the gdb information:

```shell
(gdb) bt
#0  0x00007ffff6691428 in __GI_raise (sig=sig@entry=6) at ../sysdeps/unix/sysv/linux/raise.c:54
#1  0x00007ffff669302a in __GI_abort () at abort.c:89
#2  0x00007ffff6689bd7 in __assert_fail_base (fmt=<optimized out>, assertion=assertion@entry=0x5b46c0 <.str.24> "n_channels == 2",
    file=file@entry=0x5b41e0 <.str.8> "../src/wav2json.cpp", line=line@entry=70,
    function=function@entry=0x5b4700 <__PRETTY_FUNCTION__._Z14compute_sampleIsET_RKSt6vectorIS0_SaIS0_EEiiN7Options7ChannelE> "T compute_sample(const std::vector<T> &, int, int, Options::Channel) [T = short]") at assert.c:92
#3  0x00007ffff6689c82 in __GI___assert_fail (assertion=0x5b46c0 <.str.24> "n_channels == 2", file=0x5b41e0 <.str.8> "../src/wav2json.cpp", line=70,
    function=0x5b4700 <__PRETTY_FUNCTION__._Z14compute_sampleIsET_RKSt6vectorIS0_SaIS0_EEiiN7Options7ChannelE> "T compute_sample(const std::vector<T> &, int, int, Options::Channel) [T = short]") at assert.c:101
#4  0x00000000005973f2 in compute_sample<short> (block=..., i=<optimized out>, n_channels=<optimized out>, channel=<optimized out>) at ../src/wav2json.cpp:70
#5  0x0000000000594021 in compute_waveform (wav=..., output_stream=..., samples=<optimized out>, channels=std::vector of length -30786325576016, capacity -30786325576016 = {...},
    use_db_scale=false, db_min=-48, db_max=48, progress_callback=0x522ec0 <progress_callback(unsigned long)>) at ../src/wav2json.cpp:186
#6  0x0000000000524340 in main (argc=-982, argv=0x7fffffffe000) at ../src/main.cpp:74
```

