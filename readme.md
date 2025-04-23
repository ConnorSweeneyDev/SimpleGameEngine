# Building and Execuing
This project is optimized to be built with the following targets in mind:
- Windows 10/11:
  - MSVC
  - MinGW 64-bit GCC
- Ubuntu 22.04 GLIBC Version 2.35 GCC

Version information for dependencies can be found in `external/version_info.txt`.

Part of the build process is to use my [ResourceGenerator](https://github.com/ConnorSweeneyDev/ResourceGenerator) to
make assets such as shaders and textures a part of the program rather than needing them present at runtime, with the
cost of longer linking times and a larger executable.

After following the platform specific instructions below you can execute `script/build.sh` followed by `script/run.sh`
from the root of the project to build and run the project.

### Windows
Do the following to ensure your environment is set up correctly:
- Ensure that you have either [MSVC](https://visualstudio.microsoft.com/downloads/) or [MinGW](https://winlibs.com/)
  installed.
- Ensure that you have CMake installed, you can run `winget install Kitware.CMake` if you don't.
- Ensure that you have LLVM installed, you can run `winget install LLVM.LLVM` and put the install location in your
  environment variables if you don't (for language server and clang-format support).

### Linux
Do the following on Ubuntu 22.04 to ensure your environment is set up correctly:
- Only run `sudo sed -i~orig -e 's/# deb-src/deb-src/' /etc/apt/sources.list` if you haven't already.
- Run `sudo apt update && sudo apt upgrade`.
- Run `sudo apt build-dep libsdl2-dev`.
- Run `mkdir ~/temp_cmake && cd ~/temp_cmake && wget https://cmake.org/files/v4.0/cmake-4.0.1-linux-x86_64.sh && sudo
  mkdir /opt/cmake && sudo sh cmake-4.0.1-linux-x86_64.sh --prefix=/opt/cmake && sudo ln -s
  /opt/cmake/cmake-4.0.1-linux-x86_64/bin/cmake /usr/local/bin/cmake && cd ~ && rm -rf temp_cmake` and say yes to
  everything.
- Run `mkdir ~/temp_llvm && cd ~/temp_llvm && wget https://apt.llvm.org/llvm.sh && chmod +x llvm.sh && sudo ./llvm.sh 19
  && sudo apt install clang-format-19 && sudo ln -s /usr/lib/llvm-19/bin/clang-format /usr/bin/clang-format && cd ~ &&
  rm -rf temp_llvm` and say yes to everything.
- Only run `sudo apt install alsa xorg openbox` if you don't already have an audio and window manager.

# Updating Dependencies
All dependencies can be updated by replacing the existing files in the `external` directory with new ones.

### ResourceGenerator
Go to the [releases](https://github.com/ConnorSweeneyDev/ResourceGenerator/releases) page and download the
`ResourceGenerator-Light.zip` file for the version you want. Extract it and replace the contents of the
`external/ResourceGenerator` directory with the contents of the extracted folder.

### SDL
Go to the [releases](https://github.com/libsdl-org/SDL/releases) page and download the desired release's source code.
Extract it and replace all of the existing files and folders in the `external/SDL2` directory with the contents of the
extracted folder.

### Glad
Go through the [installation](https://glad.dav1d.de/) for glad to get a zip file, extract it and replace all of the
existing files and folders in the `external/glad` directory with the contents of the extracted folder.

### GLM
Go to the [releases](https://github.com/g-truc/glm/releases) page and download the light zip file for the one you want,
extract it and replace the contents of the `external/glm/include` directory with the contents of the extracted zip file.
You can delete the `CMakeLists.txt`, `copying.txt`, `glm.cppm` and `detail/glm.cpp` files as they are not needed.
