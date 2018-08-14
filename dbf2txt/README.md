# Infinite Loop



I used **Clang 6.0 and AddressSanitizer**  to build **[dbf2txt](https://github.com/bcsanches/dbf2txt/commit/76e8f4f22ac7f8a99dea6d443c401c223e661472)**, in order to build it with `clang` in `ubuntu 16.04` , the `DbfFile.cpp` and `DbfFile.h` should be motified like following:

```diff
diff --git a/DbfFile.cpp b/DbfFile.cpp
index 9a7692e..8e19db2 100644
--- a/DbfFile.cpp
+++ b/DbfFile.cpp
@@ -23,7 +23,10 @@ DbfFile_c::DbfFile_c(const char *szFileName):
        clFile(szFileName, std::ios_base::binary | std::ios_base::in)
 {
        if(!clFile.good())
-               throw std::exception("Cannot open file");
+       {
+               std::logic_error ex("Cannot open file");
+               throw std::exception(ex);
+       }

        clFile.read(reinterpret_cast<char *>(&stHeader), sizeof(stHeader));
        size_t sz = sizeof(DbfRecord_s);
@@ -120,7 +123,8 @@ void DbfFile_c::DumpFields(const char *szDestFileName, const char **fields, size
        {
                std::stringstream stream;
                stream << "Field not found: " << fields[current];
-               throw std::exception(stream.str().c_str());
+               std::logic_error ex(stream.str().c_str());
+               throw std::exception(ex);
        }

        //Now build the skip table
diff --git a/DbfFile.h b/DbfFile.h
index ed7b4e1..4cda65b 100644
--- a/DbfFile.h
+++ b/DbfFile.h
@@ -15,10 +15,10 @@ subject to the following restrictions:

 #ifndef DBF_FILE_H
 #define DBF_FILE_H
-
+#include <stdexcept>
 #include <fstream>
 #include <vector>
-
+#include <string.h>
 typedef unsigned char uint8_t;
 typedef unsigned short uint16_t;
 typedef unsigned int uint32_t;
@@ -77,4 +77,4 @@ class DbfFile_c
 };
```



This [file](https://github.com/fouzhe/security/blob/master/dbf2txt/infinite_loop.dbf) can cause infinite loop when executing this command:

```shell
./dbf2txt infinite_loop.dbf 1.txt
```

