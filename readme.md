# 3DGameEngine
After following the platform specific instructions you can run `make all` to build the executable.

### Windows
You must either have the same [version](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0posix-17.0.6-11.0.1-ucrt-r5/winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-17.0.6-mingw-w64ucrt-11.0.1-r5.zip)
of MinGW as me, or replace the dlls in the binary folder with the ones from your MinGW installation, as long as it is a 64-bit version. This will also give you access to the
unix tools that are used in the makefile.

### Linux
Run the following commands to ensure your environment is set up correctly:
- `sudo apt install g++`
- `sudo apt install make`
- `sudo apt install clang`
- `sudo apt install llvm`
- `sudo apt install clang-format`
- `sudo apt install libsdl2-dev`

### Mac
Not yet supported.
