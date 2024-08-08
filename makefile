ifeq ($(OS), Windows_NT)
  UNAME := Windows
else
  UNAME := $(shell uname -s)
endif

DEBUG := 1
CXX := g++
CC := gcc
ifeq ($(DEBUG), 1)
  CXX_FLAGS := -g -O2 -MD -MP -std=c++17 -DDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
  CC_FLAGS := -g -O2 -MD -MP -DDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
else
  CXX_FLAGS := -s -O3 -std=c++17 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
  CC_FLAGS := -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong
endif

WARNINGS := -Wall -Wextra -Wpedantic -Wconversion -Wshadow -Wcast-qual -Wcast-align -Wfloat-equal -Wlogical-op -Wduplicated-cond -Wshift-overflow=2 -Wformat=2
INCLUDES := -Iprogram/include
ifeq ($(UNAME), Windows)
  ECHO := echo -e
  RESOURCE_LOADER := binary/windows/ResourceLoader.exe
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/windows -isystemexternal/include/stb
  LIBRARIES := -Lexternal/library/sdl2/windows -static -Wl,-Bstatic -lgcc -lstdc++ -lssp -lwinpthread -Wl,-Bdynamic -lSDL2
  OUTPUT_FILE := binary/windows/SimpleGameEngine.exe
else ifeq ($(UNAME), Linux)
  ECHO := echo
  RESOURCE_LOADER := binary/linux/ResourceLoader.out
  SYSTEM_INCLUDES := -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/khr -isystemexternal/include/sdl2/linux -isystemexternal/include/stb
  LIBRARIES := -Lexternal/library/sdl2/linux -static-libgcc -static-libstdc++ -ldl -lpthread -lSDL2 -Wl,-rpath,'$$ORIGIN'
  OUTPUT_FILE := binary/linux/SimpleGameEngine.out
#else ifeq ($(UNAME), Darwin)
endif

PROGRAM_SOURCE_DIRECTORY := program/source
PROGRAM_INCLUDE_DIRECTORY := program/include
EXTERNAL_SOURCE_DIRECTORY := external/source
OBJECT_DIRECTORY := binary/object
CPP_SOURCE_FILES := $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp)
CC_SOURCE_FILES := $(wildcard $(EXTERNAL_SOURCE_DIRECTORY)/*.c)
OBJECT_FILES := $(patsubst $(PROGRAM_SOURCE_DIRECTORY)/%.cpp,$(OBJECT_DIRECTORY)/%.o,$(CPP_SOURCE_FILES)) $(patsubst $(EXTERNAL_SOURCE_DIRECTORY)/%.c,$(OBJECT_DIRECTORY)/%.o,$(CC_SOURCE_FILES))
DEPENDENCY_FILES := $(patsubst $(OBJECT_DIRECTORY)/%.o,$(OBJECT_DIRECTORY)/%.d,$(OBJECT_FILES))
-include $(DEPENDENCY_FILES)

PROGRAM_SHADER_DIRECTORY := program/shader
RESOURCE_POSTFIX := _resource
RESOURCE_SOURCE_FILE := $(PROGRAM_SOURCE_DIRECTORY)/resource.cpp
RESOURCE_INCLUDE_FILE := $(PROGRAM_INCLUDE_DIRECTORY)/resource.hpp
RESOURCE_OBJECT_FILE := $(OBJECT_DIRECTORY)/resource.o
SHADER_SOURCE_FILES := $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl)

COMPILE_COMMANDS_FILE := compile_commands.json
CLANGD_FILE := .clangd
UNUSED_INCLUDES := UnusedIncludes: Strict
MISSING_INCLUDES := MissingIncludes: Strict
IGNORE_HEADERS := IgnoreHeader: tpl.hpp
CLANG_FORMAT_FILE := .clang-format
STYLE := BasedOnStyle: LLVM
TAB_WIDTH := IndentWidth: 2
INITIALIZER_WIDTH := ConstructorInitializerIndentWidth: 2
CONTINUATION_WIDTH := ContinuationIndentWidth: 2
BRACES := BreakBeforeBraces: Allman
LANGUAGE := Language: Cpp
LIMIT := ColumnLimit: 100
BLOCKS := AllowShortBlocksOnASingleLine: true
FUNCTIONS := AllowShortFunctionsOnASingleLine: true
IFS := AllowShortIfStatementsOnASingleLine: true
LOOPS := AllowShortLoopsOnASingleLine: true
CASE_LABELS := AllowShortCaseLabelsOnASingleLine: true
PP_DIRECTIVES := IndentPPDirectives: BeforeHash
NAMESPACE_INDENTATION := NamespaceIndentation: All
NAMESPACE_COMMENTS := FixNamespaceComments: false
INDENT_CASE_LABELS := IndentCaseLabels: true
BREAK_TEMPLATE_DECLARATIONS := AlwaysBreakTemplateDeclarations: false
FORMAT_FILES := $(filter-out $(RESOURCE_INCLUDE_FILE) $(RESOURCE_SOURCE_FILE), $(wildcard $(PROGRAM_SOURCE_DIRECTORY)/*.cpp) $(wildcard $(PROGRAM_INCLUDE_DIRECTORY)/*.hpp) $(wildcard $(PROGRAM_SHADER_DIRECTORY)/*.glsl))

main: directories $(RESOURCE_OBJECT_FILE) $(OUTPUT_FILE)
external: compile_commands clang-format clangd directories $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE)

compile_commands:
	@$(ECHO) "[" > $(COMPILE_COMMANDS_FILE)
	@for source in $(CPP_SOURCE_FILES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECT_DIRECTORY)/$$(basename $$source .cpp).o\", \"file\": \"$$source\" },"; done >> $(COMPILE_COMMANDS_FILE)
	@for source in $(CC_SOURCE_FILES); do $(ECHO) "\t{ \"directory\": \"$(CURDIR)\", \"command\": \"$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $$source -o $(OBJECT_DIRECTORY)/$$(basename $$source .c).o\", \"file\": \"$$source\" },"; done >> $(COMPILE_COMMANDS_FILE)
	@sed -i "$$ s/,$$//" $(COMPILE_COMMANDS_FILE)
	@$(ECHO) "]" >> $(COMPILE_COMMANDS_FILE)
	@$(ECHO) "Write | $(COMPILE_COMMANDS_FILE)"

clangd:
	@$(ECHO) "Diagnostics:\n  $(UNUSED_INCLUDES)\n  $(MISSING_INCLUDES)\n  Includes:\n    $(IGNORE_HEADERS)" > $(CLANGD_FILE)
	@$(ECHO) "Write | $(CLANGD_FILE)"

clang-format:
	@$(ECHO) "---\n$(STYLE)\n$(TAB_WIDTH)\n$(INITIALIZER_WIDTH)\n$(CONTINUATION_WIDTH)\n$(BRACES)\n---\n$(LANGUAGE)\n$(LIMIT)\n$(BLOCKS)\n$(FUNCTIONS)\n$(IFS)\n$(LOOPS)\n$(CASE_LABELS)\n$(PP_DIRECTIVES)\n$(NAMESPACE_INDENTATION)\n$(NAMESPACE_COMMENTS)\n$(INDENT_CASE_LABELS)\n$(BREAK_TEMPLATE_DECLARATIONS)\n..." > $(CLANG_FORMAT_FILE)
	@$(ECHO) "Write | $(CLANG_FORMAT_FILE)"
	@for file in $(FORMAT_FILES); do clang-format -i $$file; done
	@$(ECHO) "FMT   | $(FORMAT_FILES)"

directories:
	@if [ ! -d $(OBJECT_DIRECTORY) ]; then mkdir -p $(OBJECT_DIRECTORY); $(ECHO) "Write | $(OBJECT_DIRECTORY)"; fi

$(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE): $(SHADER_SOURCE_FILES) | directories
	@./$(RESOURCE_LOADER) $(RESOURCE_POSTFIX) $(SHADER_SOURCE_FILES) $@
	@$(ECHO) "Load  | $@"
$(RESOURCE_OBJECT_FILE): $(RESOURCE_SOURCE_FILE) $(RESOURCE_INCLUDE_FILE) | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@;
	@$(ECHO) "CXX   | $@"

$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.tpl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp $(PROGRAM_INCLUDE_DIRECTORY)/%.inl.hpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(PROGRAM_SOURCE_DIRECTORY)/%.cpp | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CXX   | $@"
$(OBJECT_DIRECTORY)/%.o: $(EXTERNAL_SOURCE_DIRECTORY)/%.c | directories
	@$(CC) $(CC_FLAGS) $(INCLUDES) $(SYSTEM_INCLUDES) -c $< -o $@
	@$(ECHO) "CC    | $@"

$(OUTPUT_FILE): $(OBJECT_FILES) | directories
	@$(CXX) $(CXX_FLAGS) $(WARNINGS) $(INCLUDES) $(SYSTEM_INCLUDES) $(OBJECT_FILES) $(LIBRARIES) -o $(OUTPUT_FILE)
	@$(ECHO) "Link  | $(OBJECT_FILES) -> $(OUTPUT_FILE)"

clean:
	@if [ -d $(OBJECT_DIRECTORY) ]; then rm -r $(OBJECT_DIRECTORY); fi
	@if [ -f $(OUTPUT_FILE) ]; then rm -r $(OUTPUT_FILE); fi
