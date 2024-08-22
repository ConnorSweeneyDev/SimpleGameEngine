# SimpleGameEngine
This engine provides an interface for creating 2D/3D hybrid games.

## Building and Running
This project is optimized to be built with the following targets in mind:
- Windows 11 MinGW 64-bit GCC 14.2.0
- Ubuntu 18.04 GLIBC Version 2.27

Version information for dependencies can be found in `external/version_info.txt`.

On Windows, the binary will be statically linked to any C++ runtime libraries that are used, but
dynamically linked to SDL2. On Linux, the binary will be statically linked where possible (libgcc
and libstdc++) but dynamically linked to everything else. Part of the build process is to use my
[ResourceLoader](https://github.com/ConnorSweeneyDev/ResourceLoader) to make shaders a part of the
program rather than needing them present at runtime. It is capable of loading png files aswell but I
don't want to include those directly into the binary due to the size increase.

After following the platform specific instructions below you can execute the `build.bat` file on
Windows or the `build.sh` file on Linux from the root of the project to build the binary. The
outputted binary must be run from the root to work as intended.

### Windows
You must have a 64-bit [MinGW](https://winlibs.com/) installation with clang/LLVM support in your
path, this will give you access to the unix tools that are used in the makefile. In addition, you
will need Python3 for parallel build support - `winget install --id Python.Python.3.12`.

### Linux
Do the following on Ubuntu to ensure your environment is set up correctly:
- Only run `sudo apt update && sudo apt upgrade` if you haven't already.
- Run `sudo apt install git g++ make`.
- Only run `sudo apt install alsa xorg openbox` if you don't already have an audio and window
  manager.

## Updating SDL
Since the library files are all within the project, to update SDL for each platform some extra steps
are required. The releases can be found [here](https://github.com/libsdl-org/SDL/releases).

### Windows
On top of the previous windows setup, go to the releases page and download the file ending
`mingw.zip`. Extract this and go to `x86_64-w64-mingw32` and you will have access to three important
folders:
- `bin` which contains the file that can replace the one in `binary/windows` folder of this project.
- `include/SDL2` which contains files that can replace the contents of the
  `external/include/sdl2/windows` folder of this project.
- `lib` which contains the files (not the folders) to replace the contents of the
  `external/library/sdl2/windows` folder of this project.

### Linux
On top of having followed the build instructions for linux, do the following to ensure your
environment is set up correctly:
- Only run `sudo sed -i~orig -e 's/# deb-src/deb-src/' /etc/apt/sources.list` if you haven't
  already.
- Only Run `sudo apt update` if you just ran the previous command.
- Run `sudo apt build-dep libsdl2-dev`.

Now you can download the `SDL2-[VERSION].tar.gz` file from the releases page and extract it, to
build it from source. This can be done by doing the following:
- Run `tar -xvzf SDL2-[VERSION].tar.gz` to extract.
- Run `cd SDL2-[VERSION] && mkdir build && cd build` as SDL won't build in the root.
- Run `../configure` to make SDL configure your environment for you.
- Run `make` to build the project.

Now you have two important directories:
- `SDL2-[VERSION]/include` which contains files (only the `.h` files) that can replace the contents
  of the `external/include/sdl2/linux` directory of this project.
- `SDL2-[VERSION]/build/build/.libs` which contains files (excluding the `.d` and `.o` files) that
  can replace the `external/library/sdl2/linux` directory of this project. This directory has the
  caveat that you need to move `libSDL2-2.0.so.0` from the library directory into `binary/linux`.

## Updating glad/khr
Go through the [installation](https://glad.dav1d.de/) for glad/khr to get a zip file, put `glad.h`
in the `external/include/glad` directory and `khrplatform.h` in the `external/include/khr`
directory. Then put `glad.c` in the `external/source` directory. Ensure that after replacing all of
those files, you remove all instances of `KHR/` from the `#include` statements in `glad.c` due to
the directory structure.

## Updating glm
Go to the [releases](https://github.com/g-truc/glm/releases) page and download the one you want,
extract it and replace the contents of the `external/include/glm` directory with the contents of the
`glm` directory in the extracted folder. Make sure to delete the `CMakeLists.txt`, `copying.txt`,
`glm.cppm` and `detail/glm.cpp` files as they are not needed.

## Updating stbi
Go to the stb_image.h [file](https://github.com/nothings/stb/blob/master/stb_image.h) and download
it as a raw file, then replace the file in `external/include/stbi` directory with that file.
