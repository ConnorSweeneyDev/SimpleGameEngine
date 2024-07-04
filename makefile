RM = rm -r
CXX = g++
CC = gcc

#RELEASE FLAGS:
#CXXFLAGS = -s -O3 -std=c++20 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
#CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong

#DEBUG FLAGS:
CXXFLAGS = -g -O2 -std=c++20 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong
CFLAGS = -g -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong

WARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
SYSTEM_INCLUDES = -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows -isystemexternal/include/sdl2/linux -isystemexternal/include/stbi

ifeq ($(OS), Windows_NT)
  INCLUDES = -Iprogram/include -Iexternal/include -Iexternal/include/glad -Iexternal/include/glm -Iexternal/include/khr -Iexternal/include/sdl2/windows -Iexternal/include/stbi
  LIBRARIES = -Lexternal/library/sdl2/windows -lSDL2
  OUTPUT = binary/windows/3DGameEngine.exe
else
  UNAME_S := $(shell uname -s)
  ifeq ($(UNAME_S), Linux)
    INCLUDES = -Iprogram/include -Iexternal/include -Iexternal/include/glad -Iexternal/include/glm -Iexternal/include/khr -Iexternal/include/sdl2/linux -Iexternal/include/stbi
    LIBRARIES = -Lexternal/library/sdl2/linux -lSDL2 -Wl,-rpath,'$$ORIGIN'
    OUTPUT = binary/linux/3DGameEngine.out
  endif
  #MAC IS NOT SUPPORTED YET
  #ifeq ($(UNAME_S), Darwin)
  #endif
endif

CPP_SOURCES = $(wildcard program/source/*.cpp)
C_SOURCES = $(wildcard external/source/*.c)

OBJECTS_DIRECTORY = object
COMMANDS_DIRECTORY = compile_commands.json
CLANGD_DIRECTORY = .clangd
FORMAT_DIRECTORY = .clang-format

OBJECTS = $(patsubst program/source/%.cpp,$(OBJECTS_DIRECTORY)/%.o,$(CPP_SOURCES)) $(patsubst external/source/%.c,$(OBJECTS_DIRECTORY)/%.o,$(C_SOURCES))

all: compile_commands clangd clang-format object $(OUTPUT)

compile_commands:
	@echo -n > $(COMMANDS_DIRECTORY)
	@echo "[" >> $(COMMANDS_DIRECTORY)
	@for source in $(CPP_SOURCES); do echo "    { \"directory\": \"$(CURDIR)\", \"command\": \"$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $(LIBRARIES) -c $$source -o $(OBJECTS_DIRECTORY)/$$(basename $$source .cpp).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_DIRECTORY)
	@for source in $(C_SOURCES); do echo "    { \"directory\": \"$(CURDIR)\", \"command\": \"$(CC) $(CFLAGS) $(INCLUDES) -c $$source -o $(OBJECTS_DIRECTORY)/$$(basename $$source .c).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_DIRECTORY)
	@sed -i "$$ s/,$$//" $(COMMANDS_DIRECTORY)
	@echo "]" >> $(COMMANDS_DIRECTORY)
	@echo "$(COMMANDS_DIRECTORY) updated."

clangd:
	@echo -n > $(CLANGD_DIRECTORY)
	@echo "Diagnostics:" >> $(CLANGD_DIRECTORY)
	@echo "    UnusedIncludes: None" >> $(CLANGD_DIRECTORY)
	@echo "$(CLANGD_DIRECTORY) updated."

clang-format:
	@echo -n > $(FORMAT_DIRECTORY)
	@echo "---" >> $(FORMAT_DIRECTORY)
	@echo "BasedOnStyle: LLVM" >> $(FORMAT_DIRECTORY)
	@echo "IndentWidth: 2" >> $(FORMAT_DIRECTORY)
	@echo "ConstructorInitializerIndentWidth: 2" >> $(FORMAT_DIRECTORY)
	@echo "ContinuationIndentWidth: 2" >> $(FORMAT_DIRECTORY)
	@echo "BreakBeforeBraces: Allman" >> $(FORMAT_DIRECTORY)
	@echo "---" >> $(FORMAT_DIRECTORY)
	@echo "Language: Cpp" >> $(FORMAT_DIRECTORY)
	@echo "ColumnLimit: 100" >> $(FORMAT_DIRECTORY)
	@echo "AllowShortBlocksOnASingleLine: true" >> $(FORMAT_DIRECTORY)
	@echo "AllowShortFunctionsOnASingleLine: true" >> $(FORMAT_DIRECTORY)
	@echo "AllowShortIfStatementsOnASingleLine: true" >> $(FORMAT_DIRECTORY)
	@echo "AllowShortLoopsOnASingleLine: true" >> $(FORMAT_DIRECTORY)
	@echo "AllowShortCaseLabelsOnASingleLine: true" >> $(FORMAT_DIRECTORY)
	@echo "IndentPPDirectives: BeforeHash" >> $(FORMAT_DIRECTORY)
	@echo "NamespaceIndentation: All" >> $(FORMAT_DIRECTORY)
	@echo "FixNamespaceComments: false" >> $(FORMAT_DIRECTORY)
	@echo "IndentCaseLabels: true" >> $(FORMAT_DIRECTORY)
	@echo "AlwaysBreakTemplateDeclarations: false" >> $(FORMAT_DIRECTORY)
	@echo "..." >> $(FORMAT_DIRECTORY)
	@clang-format -i program/**/*
	@echo "$(FORMAT_DIRECTORY) updated."

object:
	@if [ ! -d "$(OBJECTS_DIRECTORY)" ]; then mkdir -p $(OBJECTS_DIRECTORY); fi

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(OUTPUT)
$(OBJECTS_DIRECTORY)/%.o: program/source/%.cpp
	$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
$(OBJECTS_DIRECTORY)/%.o: external/source/%.c
	$(CC) $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@

clean:
	@if [ -d "$(OBJECTS_DIRECTORY)" ]; then $(RM) $(OBJECTS_DIRECTORY); fi
	@if [ -f $(OUTPUT) ]; then $(RM) $(OUTPUT); fi
