RM = rm -r

CXX = g++
CC = gcc

# RELEASE FLAGS:
# CXXFLAGS = -s -O3 -std=c++20 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wall -Wextra -Wpedantic
# CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-all

# DEBUG FLAGS:
CXXFLAGS = -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wconversion -Wno-unused-parameter -isystemexternal/include -isystemexternal/include/glad -isystemexternal/include/glm -isystemexternal/include/KHR -isystemexternal/include/SDL2 -isystemexternal/include/stbi
CFLAGS = -g -O0

INCLUDES = -Iprogram/include -Iexternal/include -Iexternal/include/glad -Iexternal/include/glm -Iexternal/include/KHR -Iexternal/include/SDL2 -Iexternal/include/stbi
LIBRARIES = -Lexternal/library -lmingw32 -lSDL2main -lSDL2
CPP_SOURCES = $(wildcard program/source/*.cpp)
C_SOURCES = external/source/glad.c
OUTPUT = binary/3DGameEngine.exe

OBJECTS_DIR = object
FLAGS_DIR = compile_flags.txt

$(shell if [ ! -d "$(OBJECTS_DIR)" ]; then mkdir -p $(OBJECTS_DIR); fi)
OBJECTS = $(patsubst program/source/%.cpp,$(OBJECTS_DIR)/%.o,$(CPP_SOURCES)) $(patsubst external/source/%.c,$(OBJECTS_DIR)/%.o,$(C_SOURCES))

all: compile_flags $(OUTPUT)

compile_flags:
	@echo -n > $(FLAGS_DIR)
	@for flag in $(CXXFLAGS); do echo $$flag; done >> $(FLAGS_DIR)
	@for flag in $(INCLUDES); do echo $$flag; done >> $(FLAGS_DIR)
	@for flag in $(LIBRARIES); do echo $$flag; done >> $(FLAGS_DIR)
	@echo -o$(OUTPUT) >> $(FLAGS_DIR)
	@echo "$(FLAGS_DIR) updated."

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJECTS) $(LIBRARIES) -o $(OUTPUT)
$(OBJECTS_DIR)/%.o: program/source/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
$(OBJECTS_DIR)/%.o: external/source/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@if [ -d "$(OBJECTS_DIR)" ]; then $(RM) $(OBJECTS_DIR); fi
	@if [ -f $(OUTPUT) ]; then $(RM) $(OUTPUT); fi
