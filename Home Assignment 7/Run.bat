@echo off
color DF
start /b /wait gcc -std=gnu99 -o my_program main.c
my_program.exe
pause