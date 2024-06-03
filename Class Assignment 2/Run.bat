@echo off
color DF
start /b /wait gcc -std=gnu99 -o my_program Result2.c
my_program.exe
pause