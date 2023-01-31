This is a simple program that uses the portaudio library to get audio from the microphone and play it back in real time after changing it's volume and pitch. It is a simple example of how to use the portaudio library with soundtouch library.

# Requirements:
 - Portaudio library
 - SoundTouch library

# Setting up compiler in Windows:
- Download and install MSYS2 from https://www.msys2.org/
- Install C++ compiler by running the following command in the MSYS2 UCRT64 terminal:
```
pacman -S mingw-w64-ucrt-x86_64-gcc
```
- Install portaudio library by running the following command in the MSYS2 UCRT64 terminal:
```
pacman -S mingw-w64-ucrt-x86_64-portaudio
```
- Install SoundTouch library by running the following command in the MSYS2 UCRT64 terminal:
```
pacman -S mingw-w64-ucrt-x86_64-soundtouch
```
- Run the following command in the MSYS2 UCRT64 terminal to compile the program:
```
g++ audio.cpp -o audio.exe -lportaudio -lsoundtouch
```
You may also have to include some DLL files in the same folder as the executable. You can find them in the `C:\msys64\ucrt64\bin` folder. Copy the following files to the same folder as the executable:

- libgcc_s_seh-1.dll
- libportaudio.dll
- libSoundTouch-1.dll
- libstdc++-6.dll
- libwinpthread-1.dll

> **Note:** You may want to add the bin folder of the ucrt64 toolchain to environment variable PATH to compile and run the program from anywhere. Which in my case was: `C:\msys64\ucrt64\bin`
