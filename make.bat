@echo off
cls
g++ main.cpp -std=c++17 -o a.exe -O3 -lm -lpthread -static
exit
