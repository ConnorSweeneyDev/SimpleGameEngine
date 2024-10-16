ifeq ($(UNAME), Windows)
  ECHO := echo -e
  RESOURCE_GENERATOR := binary/windows/ResourceGenerator.exe
  TARGET_PLATFORM_DIRECTORY := binary/windows
  OUTPUT_FILE := binary/windows/SimpleGameEngine.exe
else ifeq ($(UNAME), Linux)
  ECHO := echo
  RESOURCE_GENERATOR := binary/linux/ResourceGenerator.out
  TARGET_PLATFORM_DIRECTORY := binary/linux
  OUTPUT_FILE := binary/linux/SimpleGameEngine.out
endif

PROGRAM_SOURCE_DIRECTORY := program/source
PROGRAM_INCLUDE_DIRECTORY := program/include
EXTERNAL_SOURCE_DIRECTORY := external/source
BINARY_DIRECTORY := binary
OBJECT_DIRECTORY := binary/object
CPP_SOURCE_FILES := $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
HPP_SOURCE_FILES := $(wildcard $(PROGRAM_INCLUDE_DIRECTORY)/*.hpp)
INL_SOURCE_FILES := $(wildcard $(PROGRAM_INCLUDE_DIRECTORY)/*.inl)
CC_SOURCE_FILES := $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECT_FILES := $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp, $(OBJECT_DIRECTORY)/%.o, $(CPP_SOURCE_FILES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c, $(OBJECT_DIRECTORY)/%.o, $(CC_SOURCE_FILES))
DEPENDENCY_FILES := $(patsubst $(OBJECT_DIRECTORY)/%.o, $(OBJECT_DIRECTORY)/%.d, $(OBJECT_FILES))

PROGRAM_SHADER_DIRECTORY := program/shader
SHADER_SOURCE_FILES := $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl)
RESOURCE_SOURCE_FILES := $(PROGRAM_SOURCE_DIRECTORY)/resource.cpp $(PROGRAM_INCLUDE_DIRECTORY)/resource.hpp
