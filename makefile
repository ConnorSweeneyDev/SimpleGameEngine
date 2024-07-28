ifeq ($(OS), Windows_NT)
  UNAME := Windows
else
  UNAME := $(shell uname -s)
endif

CXX = g++
CC = gcc
#CXXFLAGS = -s -O3 -std=c++17 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
#CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
CXXFLAGS = -g -O2 -std=c++17 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong
CFLAGS = -g -O2 -D_GLIBCXX_DEBUG -D_GLIBCXX_DEBUG_PEDANTIC -D_FORTIFY_SOURCE=2 -fstack-protector-strong

WARNINGS = -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
INCLUDES = -Iprogram/include
ifeq ($(UNAME), Windows)
  ECHO = echo -e
  RESOURCE_LOADER = binary/windows/ResourceLoader.exe
  SYSTEM_INCLUDES = -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows -isystemexternal/include/stb
  LIBRARIES = -Lexternal/library/sdl2/windows -static -Wl,-Bstatic -lgcc -lstdc++ -lssp -lwinpthread -Wl,-Bdynamic -lSDL2
  OUTPUT = binary/windows/SimpleGameEngine.exe
else ifeq ($(UNAME), Linux)
  ECHO = echo
  RESOURCE_LOADER = binary/linux/ResourceLoader.out
  SYSTEM_INCLUDES = -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/linux -isystemexternal/include/stb
  LIBRARIES = -Lexternal/library/sdl2/linux -static-libgcc -static-libstdc++ -ldl -lpthread -lSDL2 -Wl,-rpath,'$$ORIGIN'
  OUTPUT = binary/linux/SimpleGameEngine.out
#else ifeq ($(UNAME), Darwin)
else
	$(error Unsupported OS)
endif

PROGRAM_SOURCE_DIRECTORY = program/source
PROGRAM_INCLUDE_DIRECTORY = program/include
EXTERNAL_SOURCE_DIRECTORY = external/source
OBJECT_DIRECTORY = binary/object
CPP_SOURCES = $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
C_SOURCES = $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECTS = $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp,$(OBJECT_DIRECTORY)/%.o,$(CPP_SOURCES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c,$(OBJECT_DIRECTORY)/%.o,$(C_SOURCES))

PROGRAM_SHADER_DIRECTORY = program/shader
RESOURCE_POSTFIX = _resource
RESOURCE_SOURCE_FILE = $(PROGRAM_SOURCE_DIRECTORY)/resource.cpp
RESOURCE_INCLUDE_FILE = $(PROGRAM_INCLUDE_DIRECTORY)/resource.hpp
RESOURCE_OBJECT_FILE = $(OBJECT_DIRECTORY)/resource.o
SHADER_SOURCES = $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl)

COMMANDS_FILE = compile_commands.json
FORMAT_FILE = .clang-format
CLANGD_FILE = .clangd
STYLE = BasedOnStyle: LLVM
TAB_WIDTH = IndentWidth: 2
INITIALIZER_WIDTH = ConstructorInitializerIndentWidth: 2
CONTINUATION_WIDTH = ContinuationIndentWidth: 2
BRACES = BreakBeforeBraces: Allman
LANGUAGE = Language: Cpp
LIMIT = ColumnLimit: 100
BLOCKS = AllowShortBlocksOnASingleLine: true
FUNCTIONS = AllowShortFunctionsOnASingleLine: true
IFS = AllowShortIfStatementsOnASingleLine: true
LOOPS = AllowShortLoopsOnASingleLine: true
CASE_LABELS = AllowShortCaseLabelsOnASingleLine: true
PP_DIRECTIVES = IndentPPDirectives: BeforeHash
NAMESPACE_INDENTATION = NamespaceIndentation: All
NAMESPACE_COMMENTS = FixNamespaceComments: false
INDENT_CASE_LABELS = IndentCaseLabels: true
BREAK_TEMPLATE_DECLARATIONS = AlwaysBreakTemplateDeclarations: false
FORMAT_FILES = $(filter-out $(RESOURCE_INCLUDE_FILE) $(RESOURCE_SOURCE_FILE), $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp) $(wildcard $(PROGRAM_INCLUDE_DIRECTORY)/*.hpp) $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl))

main: directories $(OUTPUT)
external: compile_commands clang-format clangd directories $(RESOURCE_OBJECT_FILE)

compile_commands:
	@$(ECHO) "[" > $(COMMANDS_FILE)
	@for source in $(CPP_SOURCES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECT_DIRECTORY)/$$(basename $$source .cpp).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_FILE)
	@for source in $(C_SOURCES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CC) $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECT_DIRECTORY)/$$(basename $$source .c).o\", \"file\": \"$$source\" },"; done >> $(COMMANDS_FILE)
	@sed -i "$$ s/,$$//" $(COMMANDS_FILE)
	@$(ECHO) "]" >> $(COMMANDS_FILE)
	@$(ECHO) "Write | $(COMMANDS_FILE)"

clang-format:
	@$(ECHO) "---\n$(STYLE)\n$(TAB_WIDTH)\n$(INITIALIZER_WIDTH)\n$(CONTINUATION_WIDTH)\n$(BRACES)\n---\n$(LANGUAGE)\n$(LIMIT)\n$(BLOCKS)\n$(FUNCTIONS)\n$(IFS)\n$(LOOPS)\n$(CASE_LABELS)\n$(PP_DIRECTIVES)\n$(NAMESPACE_INDENTATION)\n$(NAMESPACE_COMMENTS)\n$(INDENT_CASE_LABELS)\n$(BREAK_TEMPLATE_DECLARATIONS)\n..." > $(FORMAT_FILE)
	@$(ECHO) "Write | $(FORMAT_FILE)"
	@for file in $(FORMAT_FILES); do clang-format -i $$file; done
	@$(ECHO) "FMT   | $(FORMAT_FILES)"

clangd:
	@$(ECHO) "Diagnostics:\n\tUnusedIncludes: None" > $(CLANGD_FILE)
	@$(ECHO) "Write | $(CLANGD_FILE)"

directories:
	@if [ ! -d $(OBJECT_DIRECTORY) ]; then mkdir -p $(OBJECT_DIRECTORY); $(ECHO) "Write | $(OBJECT_DIRECTORY)"; fi

$(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE): $(SHADER_SOURCES)
	@./$(RESOURCE_LOADER) $(RESOURCE_POSTFIX) $(SHADER_SOURCES) $@
	@$(ECHO) "Load  | $@"
$(RESOURCE_OBJECT_FILE): $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE) | directories
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@;
	@$(ECHO) "CXX   | $@"

$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp | directories
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp | directories
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp | directories
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c | directories
	@$(CC) $(CFLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $@"
$(OUTPUT): $(OBJECTS)
	@$(CXX) $(CXXFLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(OUTPUT)
	@$(ECHO) "Link  | $(OBJECTS) -> $(OUTPUT)"

clean:
	@if [ -d $(OBJECT_DIRECTORY) ]; then rm -r $(OBJECT_DIRECTORY); fi
	@if [ -f $(OUTPUT) ]; then rm -r $(OUTPUT); fi
