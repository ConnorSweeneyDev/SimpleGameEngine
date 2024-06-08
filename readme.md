# 3DGameEngine
After following the platform specific instructions you can run `make` in the project root to build the binary.

## Building the project

### Windows
You must either have the same [version](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0posix-17.0.6-11.0.1-ucrt-r5/winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-17.0.6-mingw-w64ucrt-11.0.1-r5.zip)
of MinGW as me, or replace `libgcc_s_seh-1.dll` and `libstdc++-6.dll` in the `binary/windows` folder with the ones from your MinGW installation, as long as it is a 64-bit version. This will also
give you access to the unix tools that are used in the makefile.

### Linux
Do the following to ensure your environment is set up correctly:

- Only run `sudo apt update && sudo apt upgrade` if you haven`t already.
- Run `sudo apt install git g++ make llvm clang clang-format`.
- Only run `sudo apt install alsa xorg openbox` if you don't already have an audio and window manager.

### Mac
Not yet supported.

## Updating SDL
Since the library files are all within the project, to update SDL for each platform some extra steps are required. The releases can be found [here](https://github.com/libsdl-org/SDL/releases).

### Windows
On top of the previous windows setup, go to the releases page and download the file ending `mingw.zip`. Extract this and go to `x86_64-w64-mingw32` and you will have access to three important folders:
- `bin` which contains SDL2.dll, which goes in the `binary/windows` folder of this project.
- `include/SDL2` which contains files that can replace the contents of the `external/include/SDL2/windows` folder of this project.
- `lib` which contains the files to replace the contents of the `external/library/SDL2/windows` folder of this project.

### Linux
On top of having followed the build instructions for linux, do the following to ensure your environment is set up correctly:
- Only run `sudo sed -i~orig -e 's/# deb-src/deb-src/' /etc/apt/sources.list` if you haven't already.
- Run `sudo apt update` if you just ran the previous command.
- Run `sudo apt build-dep libsdl2-dev`.

Now you can download the `SDL2-[VERSION].tar.gz` file from the releases page and extract it, to build it from source. This can be done by doing the following:
- Run `tar -xvzf SDL2-[VERSION].tar.gz` to extract.
- Run `cd SDL2-[VERSION] && mkdir build && cd build` as SDL won't build in the root.
- Run `../configure` to make SDL configure your environment for you.
- Run `make` to build the project.

Now you have two important directories:
- `SDL2-[VERSION]/include` which contains files that can replace the contents of the `external/include/SDL2/linux` directory of this project.
- `SDL2-[VERSION]/build/build/.libs` which contains files (excluding the `.d` and `.o` files) that can replace the `external/library/SDL2/linux` directory of this project.
  This directory has the caveat that you need to move `libSDL2-2.0.so.0` from the library directory into `binary/linux`.

### Mac
Not yet supported.
