This is a simple program that uses the portaudio library to record audio from the microphone and play it back in real time. It is a simple example of how to use the portaudio library.

# Requirements:
 - Portaudio library

# Installation:
Install C++ compiler and portaudio library. Then run the following command:
```
g++ main.cpp -o main.exe -lportaudio
```

## Setting up compiler in Windows:
- Install MSYS2 from https://www.msys2.org/
- Install C++ compiler by running the following command in the MSYS2 MSYS terminal:
```
pacman -S mingw-w64-ucrt-x86_64-gcc
```
- Install portaudio library by running the following command in the MSYS2 UCRT64 terminal:
```
pacman -S mingw-w64-ucrt-x86_64-portaudio
```
