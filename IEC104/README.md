# Stack-buffer-overflow in function Iec104_Deal_I



I used **Clang 5.0 and AddressSanitizer** (`export CFLAGS="-g -fsanitize=address" CXXFLAGS="-g -fsanitize=address" LDFLAGS="-fsanitize=address"` before `make`) to build **IEC104**, this [file](https://github.com/fouzhe/security/blob/master/IEC104/crash) can cause stack buffer overflow in Iec104.c:



To compile the program, we modified the following two files:

```diff
diff --git a/test/Makefile b/test/Makefile
index cfcb1ff..5a19b05 100644
--- a/test/Makefile
+++ b/test/Makefile
@@ -1,15 +1,22 @@
 
-TOPDIR = ../../../../../..
+TOPDIR = ../
 INSTALLDIR = /usr/sbin
 #LIBDIR = /lib/
-MODULE_PATH=$(TOPDIR)/Module/IEC10X
+MODULE_PATH=$(TOPDIR)/IEC10X
 APP_PATH=$(TOPDIR)/Product/PollutionFlashover/AccessDevice/code/TEST/Iec104
 
+
+# CC = afl-clang-fast
 CC = gcc
 
+
+CFLAGS += -g -fsanitize=address
+CXXFLAGS += -g -fsanitize=address
+
 CFLAGS +=-I$(MODULE_PATH) -lpthread
 CFLAGS +=-I$(APP_PATH)
 
+
 OBJ=iec104_monitor
```



```diff
diff --git a/test/main.c b/test/main.c
index 19cc5a5..c6012d9 100644
--- a/test/main.c
+++ b/test/main.c
@@ -39,114 +39,6 @@ void Iec104_printhelp(void)
     printf("\n");
 }
 
-int main(int argc, char *argv[]){
-
-    pthread_t tid1,tid2; 
-    int err;  
-    void *tret;  
-    SocketArg_T Arg1;
-    unsigned int addr1 = 0,addr2 = 0;
-    int opt;  
-    char *optstring = "p:d:n:m:h";  
-    unsigned short port1 = 10000;
-    unsigned short port2 = 10001;
-    addr1 =  inet_addr("192.168.1.114");
-    addr2 =  inet_addr("192.168.1.114");
-    uint32_t Addr = 0,i;
-    void *ptemp = NULL;
-    
-    Arg1.port = 10000;
-    Arg1.addr = addr1;
-    
-    uint8_t mode = SOCKET_MODE_CLIENT;
-    uint8_t DstIp[32] = {0};
-    uint32_t Port = 0;
-    uint32_t NumSta = 0;
-    
-    ClientInfo_T clientinfo;
- 
-    Stm32f103RegisterIec10x(); 
-
-    while ((opt = getopt(argc, argv, optstring)) != -1){ 
-    #if 0 
-        printf("opt = %c\n", opt);  
-        printf("optarg = %s\n", optarg);  
-        printf("optind = %d\n", optind);  
-    #endif    
-        switch(opt){
-            case 'h':
-                Iec104_printhelp();
-                return;
-            case 'd':
-                if(optarg == NULL){
-                    printf("-d need argument \n");
-                    break;
-                }
-                Addr =  inet_addr(optarg);
-                strcpy(DstIp,optarg);
-                break;
-            case 'm':
-                if(strcmp("server", optarg) == 0)
-                    mode = SOCKET_MODE_SERVER;
-                else if(strcmp("client", optarg) == 0)
-                    mode = SOCKET_MODE_CLIENT;
-                else{
-                    LOG("mode error (%s) \n",optarg);
-                    return;
-                }
-                break; 
-            case 'p':
-                if(optarg == NULL){
-                    printf("-p need argument \n");
-                    break;
-                }
-                sscanf(optarg, "%d", &Port);
-                break;
-            case 'n':
-                if(optarg == NULL){
-                    printf("-n need argument \n");
-                    break;
-                }
-                sscanf(optarg, "%d", &NumSta);
-                break;
-            default :
-                break;
-        }
-    }  
-    
-    LOG("mode :(%d), port: (%d), ip: (%s), station num: (%d) \n",mode, Port,DstIp,NumSta);   
-    
-    pthread_mutex_init(&mutex,NULL);
-    pthread_mutex_init(&mutex2,NULL);
-    
-    if(NumSta<=0 || NumSta>10000){
-    
-        LOG("station number error:%d \n",NumSta);
-    } 
-    
-    if(mode == SOCKET_MODE_SERVER){
-        LOG("Iec104 Server Mode \n");
-        err=pthread_create(&tid1,NULL,Iec104_main,&Arg1);
-        if(err!=0)  {  
-            LOG("pthread_create error:%s\n",strerror(err));  
-            exit(-1);  
-        } 
-    }else if(mode == SOCKET_MODE_CLIENT){
-        LOG("Iec104 Client Mode \n");
-        for(i=0; i<NumSta; i++){
-            clientinfo.ClientId = i;
-            clientinfo.socketfd = 0;
-            err=pthread_create(&tid1,NULL,Iec104_Client,&clientinfo);
-            if(err!=0)  {  
-                printf("pthread_create error:%s\n",strerror(err));  
-                exit(-1);  
-            } 
-        }
-    }
-    while(1);
-
-    return 0;
-}
 
 void DumpHEX(uint8_t *buffer, uint32_t len){
 
@@ -315,4 +207,115 @@ void *Iec104_Client(void *arg)
     close(socketfd); 
  
     exit(0);  
+}
+
+
+
+int main(int argc, char *argv[]){
+
+    pthread_t tid1,tid2; 
+    int err;  
+    void *tret;  
+    SocketArg_T Arg1;
+    unsigned int addr1 = 0,addr2 = 0;
+    int opt;  
+    char *optstring = "p:d:n:m:h";  
+    unsigned short port1 = 10000;
+    unsigned short port2 = 10001;
+    addr1 =  inet_addr("192.168.1.114");
+    addr2 =  inet_addr("192.168.1.114");
+    uint32_t Addr = 0,i;
+    void *ptemp = NULL;
+    
+    Arg1.port = 10000;
+    Arg1.addr = addr1;
+    
+    uint8_t mode = SOCKET_MODE_CLIENT;
+    uint8_t DstIp[32] = {0};
+    uint32_t Port = 0;
+    uint32_t NumSta = 0;
+    
+    ClientInfo_T clientinfo;
+ 
+    Stm32f103RegisterIec10x(); 
+
+    while ((opt = getopt(argc, argv, optstring)) != -1){ 
+    #if 0 
+        printf("opt = %c\n", opt);  
+        printf("optarg = %s\n", optarg);  
+        printf("optind = %d\n", optind);  
+    #endif    
+        switch(opt){
+            case 'h':
+                Iec104_printhelp();
+                return;
+            case 'd':
+                if(optarg == NULL){
+                    printf("-d need argument \n");
+                    break;
+                }
+                Addr =  inet_addr(optarg);
+                strcpy(DstIp,optarg);
+                break;
+            case 'm':
+                if(strcmp("server", optarg) == 0)
+                    mode = SOCKET_MODE_SERVER;
+                else if(strcmp("client", optarg) == 0)
+                    mode = SOCKET_MODE_CLIENT;
+                else{
+                    LOG("mode error (%s) \n",optarg);
+                    return;
+                }
+                break; 
+            case 'p':
+                if(optarg == NULL){
+                    printf("-p need argument \n");
+                    break;
+                }
+                sscanf(optarg, "%d", &Port);
+                break;
+            case 'n':
+                if(optarg == NULL){
+                    printf("-n need argument \n");
+                    break;
+                }
+                sscanf(optarg, "%d", &NumSta);
+                break;
+            default :
+                break;
+        }
+    }  
+    
+    LOG("mode :(%d), port: (%d), ip: (%s), station num: (%d) \n",mode, Port,DstIp,NumSta);   
+    
+    pthread_mutex_init(&mutex,NULL);
+    pthread_mutex_init(&mutex2,NULL);
+    
+    if(NumSta<=0 || NumSta>10000){
+    
+        LOG("station number error:%d \n",NumSta);
+    } 
+    
+    if(mode == SOCKET_MODE_SERVER){
+        LOG("Iec104 Server Mode \n");
+        err=pthread_create(&tid1,NULL,Iec104_main,&Arg1);
+        if(err!=0)  {  
+            LOG("pthread_create error:%s\n",strerror(err));  
+            exit(-1);  
+        } 
+    }else if(mode == SOCKET_MODE_CLIENT){
+        LOG("Iec104 Client Mode \n");
+        for(i=0; i<NumSta; i++){
+            clientinfo.ClientId = i;
+            clientinfo.socketfd = 0;
+            err=pthread_create(&tid1,NULL,Iec104_Client,&clientinfo);
+            if(err!=0)  {  
+                printf("pthread_create error:%s\n",strerror(err));  
+                exit(-1);  
+            } 
+        }
+    }
+    while(1);
+
+    return 0;
 }
\ No newline at end of file

```

Then compile it by following command:

```shell
cd test && make
```

I run the program with the help of [preeny](https://github.com/zardus/preeny)(Channels socket communication to the console) by the following command:

```
LD_PRELOAD=/usr/lib/x86_64-linux-gnu/libasan.so.2:/root/preeny/x86_64-linux-gnu/desock.so ./iec104_monitor -m server < crash
```

Here is ASAN information:

```
==20667==ERROR: AddressSanitizer: stack-buffer-overflow on address 0x7f2ee8dfee6d at pc 0x000000409054 bp 0x7f2ee8dfe610 sp 0x7f2ee8dfe600
READ of size 2 at 0x7f2ee8dfee6d thread T1
    #0 0x409053 in Iec104_Deal_I ..//IEC10X/Iec104.c:1175
    #1 0x40972b in Iex104_Receive ..//IEC10X/Iec104.c:1305
    #2 0x40b661 in Iec104_main /root/feilong/4-3-104/IEC104/test/main.c:139
    #3 0x7f2eebf6d6b9 in start_thread (/lib/x86_64-linux-gnu/libpthread.so.0+0x76b9)
    #4 0x7f2eebca341c in clone (/lib/x86_64-linux-gnu/libc.so.6+0x10741c)

Address 0x7f2ee8dfee6d is located in stack of thread T1 at offset 1853 in frame
    #0 0x40b12a in Iec104_main /root/feilong/4-3-104/IEC104/test/main.c:72

  This frame has 6 object(s):
    [32, 36) 'sin_size'
    [96, 100) 'on'
    [160, 168) 'tid1'
    [224, 240) 's_add'
    [288, 304) 'c_add'
    [352, 1852) 'Iec104_RecvBuf' <== Memory access at offset 1853 overflows this variable
HINT: this may be a false positive if your program uses some custom stack unwind mechanism or swapcontext
      (longjmp and C++ exceptions *are* supported)
Thread T1 created by T0 here:
    #0 0x7f2eec3dd253 in pthread_create (/usr/lib/x86_64-linux-gnu/libasan.so.2+0x36253)
    #1 0x40c190 in main /root/feilong/4-3-104/IEC104/test/main.c:301
    #2 0x7f2eebbbc82f in __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x2082f)

SUMMARY: AddressSanitizer: stack-buffer-overflow ..//IEC10X/Iec104.c:1175 Iec104_Deal_I
Shadow bytes around the buggy address:
  0x0fe65d1b7d70: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7d80: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7d90: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7da0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7db0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
=>0x0fe65d1b7dc0: 00 00 00 00 00 00 00 00 00 00 00 00 00[04]f3 f3
  0x0fe65d1b7dd0: f3 f3 f3 f3 f3 f3 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7de0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7df0: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7e00: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
  0x0fe65d1b7e10: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00
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
==20667==ABORTING
```

