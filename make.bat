@echo off

set PATH=C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin;%PATH%
rem echo %PATH%
rem cd "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin"
g++ main.cpp -std=c++17 -o a.exe -O3 -lm -lpthread -flto -ffunction-sections -fdata-sections -static 
exit