ifeq ($(UNAME), Windows)
  ECHO := echo -e
  RESOURCE_LOADER := binary/windows/ResourceLoader.exe
  OUTPUT_FILE := binary/windows/SimpleGameEngine.exe
else ifeq ($(UNAME), Linux)
  ECHO := echo
  RESOURCE_LOADER := binary/linux/ResourceLoader.out
  OUTPUT_FILE := binary/linux/SimpleGameEngine.out
endif

PROGRAM_SOURCE_DIRECTORY := program/source
PROGRAM_INCLUDE_DIRECTORY := program/include
EXTERNAL_SOURCE_DIRECTORY := external/source
OBJECT_DIRECTORY := binary/object
CPP_SOURCE_FILES := $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
CC_SOURCE_FILES := $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECT_FILES := $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp,$(OBJECT_DIRECTORY)/%.o,$(CPP_SOURCE_FILES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c,$(OBJECT_DIRECTORY)/%.o,$(CC_SOURCE_FILES))
DEPENDENCY_FILES := $(patsubst $(OBJECT_DIRECTORY)/%.o,$(OBJECT_DIRECTORY)/%.d,$(OBJECT_FILES))

PROGRAM_SHADER_DIRECTORY := program/shader
SHADER_FILES := $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl)
RESOURCE_FILES := $(PROGRAM_SOURCE_DIRECTORY)/resource.cpp $(PROGRAM_INCLUDE_DIRECTORY)/resource.hpp
RESOURCE_OBJECT_FILE := $(OBJECT_DIRECTORY)/resource.o
