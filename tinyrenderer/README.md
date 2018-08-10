# Heap buffer overflow in function Model::uv



I used **Clang 6.0 and AddressSanitizer**  to build **[tinyrenderer](https://github.com/ssloy/tinyrenderer)**, this [obj file](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::uv.obj) with those tga file [tga1](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::uv_diffuse.tga),[tga2](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::uv_nm_tangent.tga),[tga3](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::uv_spec.tga) can cause heap buffer overflow in function Model::uv in model.cpp when executing this command:



```shell
./main $POC(obj file only)
```

This is the ASAN information:

```shell
=================================================================
==26495==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x602000004140 at pc 0x000000530bb9 bp 0x7ffc8eedd770 sp 0x7ffc8eedd768
READ of size 4 at 0x602000004140 thread T0
    #0 0x530bb8 in Model::uv(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:96:16
    #1 0x542798 in Shader::vertex(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:26:44
    #2 0x54146b in main /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:82:24
    #3 0x7f1ec386e82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41c098 in _start (/home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main+0x41c098)

0x602000004140 is located 4 bytes to the right of 12-byte region [0x602000004130,0x60200000413c)
allocated by thread T0 here:
    #0 0x517d58 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x5387e5 in __gnu_cxx::new_allocator<vec<3ul, int> >::allocate(unsigned long, void const*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/new_allocator.h:104:27
    #2 0x53878b in __gnu_cxx::__alloc_traits<std::allocator<vec<3ul, int> > >::allocate(std::allocator<vec<3ul, int> >&, unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/alloc_traits.h:182:18
    #3 0x538452 in std::_Vector_base<vec<3ul, int>, std::allocator<vec<3ul, int> > >::_M_allocate(unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:170:20
    #4 0x53a36e in std::_Vector_base<vec<3ul, int>, std::allocator<vec<3ul, int> > >::_M_create_storage(unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:185:33
    #5 0x539bb4 in std::_Vector_base<vec<3ul, int>, std::allocator<vec<3ul, int> > >::_Vector_base(unsigned long, std::allocator<vec<3ul, int> > const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:136:9
    #6 0x5398df in std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >::vector(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:319:9
    #7 0x53e337 in void std::_Construct<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > >(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_construct.h:83:38
    #8 0x53e268 in std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >* std::__uninitialized_copy<false>::__uninit_copy<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*>(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_uninitialized.h:75:3
    #9 0x53e218 in std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >* std::uninitialized_copy<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*>(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_uninitialized.h:123:14
    #10 0x53e1e8 in std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >* std::__uninitialized_copy_a<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > >(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > >&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_uninitialized.h:281:14
    #11 0x53bdcc in std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >* std::__uninitialized_move_if_noexcept_a<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > > >(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > >&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_uninitialized.h:302:14
    #12 0x53906b in std::vector<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > > >::_M_insert_aux(__gnu_cxx::__normal_iterator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >*, std::vector<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > > > >, std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/vector.tcc:371:5
    #13 0x5322b8 in std::vector<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > >, std::allocator<std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > > >::push_back(std::vector<vec<3ul, int>, std::allocator<vec<3ul, int> > > const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:925:4
    #14 0x52e590 in Model::Model(char const*) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:38:20
    #15 0x54133c in main /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:78:21
    #16 0x7f1ec386e82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:96:16 in Model::uv(int, int)
Shadow bytes around the buggy address:
  0x0c047fff87d0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff87e0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff87f0: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8800: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8810: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
=>0x0c047fff8820: fa fa fd fd fa fa 00 04[fa]fa fd fd fa fa fd fd
  0x0c047fff8830: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8840: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8850: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8860: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
  0x0c047fff8870: fa fa fd fd fa fa fd fd fa fa fd fd fa fa fd fd
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
==26495==ABORTING
```



# Heap buffer overflow in function Model::vert

I used **Clang 6.0 and AddressSanitizer**  to build **[tinyrenderer](https://github.com/ssloy/tinyrenderer)**, this [obj file](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::vert.obj) with those tga file [tga1](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::vert_diffuse.tga),[tga2](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::vert_nm_tangent.tga),[tga3](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_Model::vert_spec.tga) can cause heap buffer overflow in function Model::vert  in model.cpp when executing this command:

```shell
./main $POC(obj file only)
```

This is the ASAN information:

```shell
=================================================================
==31108==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x6230000000f4 at pc 0x0000004df14d bp 0x7ffceaa92750 sp 0x7ffceaa91f00
READ of size 12 at 0x6230000000f4 thread T0
    #0 0x4df14c in __asan_memcpy /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_interceptors_memintrinsics.cc:23
    #1 0x52faed in Model::vert(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:68:12
    #2 0x543047 in Shader::vertex(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:28:64
    #3 0x54146b in main /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:82:24
    #4 0x7f0574f4582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #5 0x41c098 in _start (/home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main+0x41c098)

0x6230000000f4 is located 12 bytes to the left of 6144-byte region [0x623000000100,0x623000001900)
allocated by thread T0 here:
    #0 0x517d58 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x535305 in __gnu_cxx::new_allocator<vec<3ul, float> >::allocate(unsigned long, void const*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/new_allocator.h:104:27
    #2 0x5352ab in __gnu_cxx::__alloc_traits<std::allocator<vec<3ul, float> > >::allocate(std::allocator<vec<3ul, float> >&, unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/alloc_traits.h:182:18
    #3 0x534ed2 in std::_Vector_base<vec<3ul, float>, std::allocator<vec<3ul, float> > >::_M_allocate(unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:170:20
    #4 0x5340c6 in std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > >::_M_insert_aux(__gnu_cxx::__normal_iterator<vec<3ul, float>*, std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > > >, vec<3ul, float> const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/vector.tcc:353:30
    #5 0x5318a8 in std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > >::push_back(vec<3ul, float> const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:925:4
    #6 0x52ded8 in Model::Model(char const*) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:19:20
    #7 0x54133c in main /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:78:21
    #8 0x7f0574f4582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_interceptors_memintrinsics.cc:23 in __asan_memcpy
Shadow bytes around the buggy address:
  0x0c467fff7fc0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff7fd0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff7fe0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff7ff0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8000: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c467fff8010: fa fa fa fa fa fa fa fa fa fa fa fa fa fa[fa]fa
  0x0c467fff8020: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8030: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8040: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8050: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8060: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==31108==ABORTING
```





# SEGV in function Model::uv

I used **Clang 6.0 and AddressSanitizer**  to build **[tinyrenderer](https://github.com/ssloy/tinyrenderer)**, this [obj file](https://github.com/fouzhe/security/blob/master/tinyrenderer/SEGV_Model::uv.obj) with those tga file [tga1](https://github.com/fouzhe/security/blob/master/tinyrenderer/SEGV_Model::uv_diffuse.tga),[tga2](https://github.com/fouzhe/security/blob/master/tinyrenderer/SEGV_Model::uv_nm_tangent.tga),[tga3](https://github.com/fouzhe/security/blob/master/tinyrenderer/SEGV_Model::uv_spec.tga) can cause SEGV in function Model::uv  in model.cpp when executing this command:

```shell
./main $POC(obj file only)
```

This is the ASAN information:

```shell
=================================================================
==5610==ERROR: AddressSanitizer: SEGV on unknown address 0x000000000004 (pc 0x000000530bbd bp 0x7ffc0d6ba490 sp 0x7ffc0d6ba380 T0)
==5610==The signal is caused by a READ memory access.
==5610==Hint: address points to the zero page.
    #0 0x530bbc in Model::uv(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:96:16
    #1 0x542798 in Shader::vertex(int, int) /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:26:44
    #2 0x54146b in main /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main.cpp:82:24
    #3 0x7f6109abe82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #4 0x41c098 in _start (/home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/main+0x41c098)

AddressSanitizer can not provide additional info.
SUMMARY: AddressSanitizer: SEGV /home/fouzhe/my_fuzz/tinyrenderer_test/tinyrenderer/model.cpp:96:16 in Model::uv(int, int)
==5610==ABORTING
```



# Heap buffer overflow in function vec<3ul, float>::norm

I used **Clang 6.0 and AddressSanitizer**  to build **[tinyrenderer](https://github.com/ssloy/tinyrenderer)**, this [obj file](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_norm.obj) with those tga file [tga1](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_norm_diffuse.tga),[tga2](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_norm_nm_tangent.tga),[tga3](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_norm_spec.tga) can cause heap buffer overflow in function vec<3ul, float>::norm in geometry.h when executing this command:

```shell
./main $POC(obj file only)
```

This is the ASAN information:

```shell
=================================================================
==32048==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x623000001903 at pc 0x00000053905d bp 0x7ffcd16f47e0 sp 0x7ffcd16f47d8
READ of size 8 at 0x623000001903 thread T0
    #0 0x53905c in vec<3ul, float>::norm() /home/fouzhe/my_fuzz/tinyrenderer/./geometry.h:38:41
    #1 0x53905c in vec<3ul, float>::normalize(float) /home/fouzhe/my_fuzz/tinyrenderer/./geometry.h:39
    #2 0x53905c in Model::normal(int, int) /home/fouzhe/my_fuzz/tinyrenderer/model.cpp:106
    #3 0x5480d4 in Shader::vertex(int, int) /home/fouzhe/my_fuzz/tinyrenderer/main.cpp:27:104
    #4 0x546295 in main /home/fouzhe/my_fuzz/tinyrenderer/main.cpp:82:24
    #5 0x7f9b5f1e782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #6 0x41c188 in _start (/home/fouzhe/my_fuzz/tinyrenderer/main+0x41c188)

0x623000001903 is located 3 bytes to the right of 6144-byte region [0x623000000100,0x623000001900)
allocated by thread T0 here:
    #0 0x517e48 in operator new(unsigned long) /home/fouzhe/llvm/llvm/projects/compiler-rt/lib/asan/asan_new_delete.cc:92
    #1 0x539a6d in __gnu_cxx::new_allocator<vec<3ul, float> >::allocate(unsigned long, void const*) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/new_allocator.h:104:27
    #2 0x539a6d in __gnu_cxx::__alloc_traits<std::allocator<vec<3ul, float> > >::allocate(std::allocator<vec<3ul, float> >&, unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/ext/alloc_traits.h:182
    #3 0x539a6d in std::_Vector_base<vec<3ul, float>, std::allocator<vec<3ul, float> > >::_M_allocate(unsigned long) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:170
    #4 0x539a6d in std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > >::_M_insert_aux(__gnu_cxx::__normal_iterator<vec<3ul, float>*, std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > > >, vec<3ul, float> const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/vector.tcc:353
    #5 0x53148d in std::vector<vec<3ul, float>, std::allocator<vec<3ul, float> > >::push_back(vec<3ul, float> const&) /usr/lib/gcc/x86_64-linux-gnu/5.4.0/../../../../include/c++/5.4.0/bits/stl_vector.h:925:4
    #6 0x53148d in Model::Model(char const*) /home/fouzhe/my_fuzz/tinyrenderer/model.cpp:19
    #7 0x5461f7 in main /home/fouzhe/my_fuzz/tinyrenderer/main.cpp:78:21
    #8 0x7f9b5f1e782f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/my_fuzz/tinyrenderer/./geometry.h:38:41 in vec<3ul, float>::norm()
Shadow bytes around the buggy address:
  0x0c467fff82d0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff82e0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff82f0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8300: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0c467fff8310: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0c467fff8320:[fa]fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff8330: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff8340: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff8350: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff8360: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff8370: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==32048==ABORTING
```





# Heap buffer overflow in function vec<3ul, float>::normalize(float)

I used **Clang 6.0 and AddressSanitizer**  to build **[tinyrenderer](https://github.com/ssloy/tinyrenderer)**, this [obj file](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_normalize.obj) with those tga file [tga1](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_normalize_diffuse.tga),[tga2](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_normalize_nm_tangent.tga),[tga3](https://github.com/fouzhe/security/blob/master/tinyrenderer/heap-buffer-overflow_normalize_spec.tga) can cause heap buffer overflow in function vec<3ul, float>::normalize(float) in geometry.h when executing this command:

```shell
./main $POC(obj file only)
```

This is the ASAN information:

```shell
=================================================================
==18198==ERROR: AddressSanitizer: heap-buffer-overflow on address 0x623000008d8c at pc 0x000000538fa2 bp 0x7ffd3d4292c0 sp 0x7ffd3d4292b8
READ of size 8 at 0x623000008d8c thread T0
    #0 0x538fa1 in vec<3ul, float>::normalize(float) /home/fouzhe/my_fuzz/tinyrenderer/./geometry.h:39:43
    #1 0x538fa1 in Model::normal(int, int) /home/fouzhe/my_fuzz/tinyrenderer/model.cpp:106
    #2 0x5480d4 in Shader::vertex(int, int) /home/fouzhe/my_fuzz/tinyrenderer/main.cpp:27:104
    #3 0x546295 in main /home/fouzhe/my_fuzz/tinyrenderer/main.cpp:82:24
    #4 0x7f93897a582f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)
    #5 0x41c188 in _start (/home/fouzhe/my_fuzz/tinyrenderer/main+0x41c188)

Address 0x623000008d8c is a wild pointer.
SUMMARY: AddressSanitizer: heap-buffer-overflow /home/fouzhe/my_fuzz/tinyrenderer/./geometry.h:39:43 in vec<3ul, float>::normalize(float)
Shadow bytes around the buggy address:
  0x0c467fff9160: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff9170: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff9180: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff9190: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff91a0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
=>0x0c467fff91b0: fa[fa]fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff91c0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff91d0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff91e0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff91f0: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x0c467fff9200: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
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
==18198==ABORTING
```





