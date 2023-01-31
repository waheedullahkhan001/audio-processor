@echo off
g++ audio.cpp -o audio.exe -lportaudio -lsoundtouch
pause
audio.exe
pause