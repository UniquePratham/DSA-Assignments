@echo off
color DF
start /b /wait gcc -std=gnu99 -o spiral spiral.c
spiral.exe
pause