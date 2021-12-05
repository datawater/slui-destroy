<<<<<<< Updated upstream:make.bat
g++ main.cpp -std=c++17 -o a.exe -O3 -lm -static 
=======
@echo off

set PATH=C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin;%PATH%
rem echo %PATH%
rem cd "C:\Program Files (x86)\mingw-w64\i686-8.1.0-posix-dwarf-rt_v6-rev0\mingw32\bin"
g++ main.cpp -std=c++17 -o a.exe -O3 -lm -lpthread -flto -ffunction-sections -fdata-sections -static
if %errorlevel% == 0 (echo CMD: built with no errors && exit 0) else (exit 1)
>>>>>>> Stashed changes:1_make.bat
