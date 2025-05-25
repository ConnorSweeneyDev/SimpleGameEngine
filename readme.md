# Simple Game Engine
An engine meant for 2D/3D hybrid games.

# How to Build
This project is optimized to be built on Windows using MSVC.

1. Ensure that you have [MSVC](https://visualstudio.microsoft.com/downloads/) installed.
2. Ensure that you have [CMake](https://cmake.org/download/) installed, you can run `winget install Kitware.CMake` if
   you don't.
3. Ensure that you have [LLVM](https://releases.llvm.org/) installed, you can run `winget install LLVM.LLVM` and put the
   install location in your environment variables if you don't (for language server and clang-format support).
4. Execute `script/build.sh` followed by `script/run.sh`.

Part of the build process is to use my [ResourceGenerator](https://github.com/ConnorSweeneyDev/ResourceGenerator) to
make assets such as shaders and textures a part of the program rather than needing them present at runtime, with the
cost of longer linking times and a larger executable.

# How to Update Dependencies
All dependencies are vendored and stored in the `external` directory. Version information for dependencies can be found
in `external/version_info.txt`.

### ResourceGenerator
1. Download the source code (light) for the [release](https://github.com/ConnorSweeneyDev/ResourceGenerator/releases)
   you want.
2. Put the contents of the extracted folder in `external/ResourceGenerator`.

### SDL
1. Download the source code (light) for the [release](https://github.com/libsdl-org/SDL/releases) you want.
2. Put the contents of the extracted folder in `external/SDL2`.
3. Put a copy of `external/SDL_mixer/include/SDL_mixer.h` in `external/SDL2/include`.

### SDL_mixer
1. Download the source code (light) for the [release](https://github.com/libsdl-org/SDL_mixer/releases) you want.
2. Put the contents of the extracted folder in `external/SDL_mixer`.
3. Put a copy of `external/SDL_mixer/include/SDL_mixer.h` in `external/SDL2/include`.
4. Remove `external/SDL_mixer/.gitmodules`.

### Glad
1. Go through the [installation](https://glad.dav1d.de/) to get a zip file.
2. Put the contents of the extracted folder in `external/glad`.

### GLM
1. Download the source code (light) for the [release](https://github.com/g-truc/glm/releases) you want.
2. Put the contents of the extracted folder in `external/glm/include`.
3. You can remove anything that isn't a `.hpp`, `.inl` or `.h` file as they are not needed.
