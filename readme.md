# 3DGameEngine
After following the platform specific instructions you can run `make all` to build the executable.

## Building the project
### Windows
You must either have the same [version](https://github.com/brechtsanders/winlibs_mingw/releases/download/13.2.0posix-17.0.6-11.0.1-ucrt-r5/winlibs-x86_64-posix-seh-gcc-13.2.0-llvm-17.0.6-mingw-w64ucrt-11.0.1-r5.zip)
of MinGW as me, or replace `libgcc_s_seh-1.dll` and `libstdc++-6.dll` in the `binary/windows` folder with the ones from your MinGW installation, as long as it is a 64-bit version. This will also
give you access to the unix tools that are used in the makefile.

### Linux
Run the following commands to ensure your environment is set up correctly:
- `sudo apt install g++ make llvm clang clang-format`
- Only run `sudo apt install alsa xorg openbox` if you dont already have a window and audio manager.

### Mac
Not yet supported.

## Updating SDL
Since the library files are all within the project, to update SDL for each platform some extra steps are required. The releases can be found [here](https://github.com/libsdl-org/SDL/releases).

### Windows
On top of the previous windows setup, go to the releases page and download the file ending `mingw.zip`. Extract this and go to `x86_64-w64-mingw32` and you will have access to three important folders:
- `bin` which contains SDL2.dll, which goes in the `binary/windows` directory of this project.
- `include/SDL2` which contains files that can replace the contents of the `external/include/SDL2/windows` directory of this project.
- `lib` which contains the files to replace the contents of the `external/library/SDL2/windows` directory of this project.

### Linux
On top of having run the previous linux commands, run the following commands to ensure your environment is set up correctly:
- `sudo sed -i~orig -e 's/# deb-src/deb-src/' /etc/apt/sources.list`
- `sudo apt update`
- `sudo apt build-dep libsdl2-dev`

Now you can download a .tar.gz file from the releases page and extract it, to build it from source. This can be done by doing the following:
- Run `tar -xvzf [SDL VERSION].tar.gz` to extract.
- Run `cd [SDL VERSION]` to enter the extracted folder.
- Run `mkdir build && cd build` to go into the directory that will be used to build.
- Run `../configure` to make SDL configure your environment for you.
- Run `make` to build the project.

Now you have two important directories, `[SDL VERSION]/include` and `[SDL VERSION]/build/build/.libs`. The contents of these can replace the contents of this project's
`external/include/SDL2/linux` and `external/library/SDL2/linux` respectively. You don't need to include .d or .o files in the library directory.

### Mac
Not yet supported.
