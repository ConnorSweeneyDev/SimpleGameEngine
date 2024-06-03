# 3DGameEngine
You will need access to the following commands to build on any platform:
- `gcc`
- `g++`
- `make`
- `clang-format`

After following the platform specific instructions you can run `make all` to build the project.

### Windows
For windows you either need to have the same [version](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0posix-17.0.6-11.0.1-ucrt-r5/winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-17.0.6-mingw-w64ucrt-11.0.1-r5.zip)
of MinGW as me or replace the dlls in the binary folder with the ones from your MinGW installation, as long as it is a 64-bit version. This will also give you access to all of
the above commands.

### Linux
For linux you need to have `libsdl2-dev` installed. On Ubuntu it can be installed with `sudo apt install libsdl2-dev`. You can ensure that `clang-format` is installed
using `sudo apt install clang`, `sudo apt install llvm` and finally `sudo apt install clang-format`. You can install `make` and `g++` with apt as well.

### Mac
Not yet supported.
