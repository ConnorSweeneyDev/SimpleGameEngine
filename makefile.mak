# g++ -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Iprog/include -Iexternal/include -Iexternal/include/glad -Iexternal/include/glm -Iexternal/include/KHR -Iexternal/include/SDL2 -Iexternal/include/stbi prog/source/*.cpp external/source/glad.c -Lexternal/lib -lmingw32 -lSDL2main -lSDL2 -o 3DGameEngine.exe

RM = rm -r

CXX = g++
CC = gcc

# RELEASE FLAGS:
# CXXFLAGS = -s -O3 -std=c++20 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wall -Wextra -Wpedantic
# CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-all

# DEBUG FLAGS:
CXXFLAGS = -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter
CFLAGS = -g -O0

INCLUDES = -Iprog/include -Iexternal/include -Iexternal/include/glad -Iexternal/include/glm -Iexternal/include/KHR -Iexternal/include/SDL2 -Iexternal/include/stbi
LIBS = -Lexternal/lib -lmingw32 -lSDL2main -lSDL2
CPP_SRCS = $(wildcard prog/source/*.cpp)
C_SRCS = external/source/glad.c
OUTPUT = 3DGameEngine.exe

OBJ_DIR = object
$(shell if [ ! -d "$(OBJ_DIR)" ]; then mkdir -p $(OBJ_DIR); fi)
OBJS = $(patsubst prog/source/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS)) $(patsubst external/source/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

FLAGS_DIR = compile_flags.txt

all: compile_flags $(OUTPUT)

compile_flags:
	@echo -n > $(FLAGS_DIR)
	@for flag in $(CXXFLAGS); do echo $$flag; done >> $(FLAGS_DIR)
	@for flag in $(INCLUDES); do echo $$flag; done >> $(FLAGS_DIR)
	@for flag in $(LIBS); do echo $$flag; done >> $(FLAGS_DIR)
	@echo -o$(OUTPUT) >> $(FLAGS_DIR)
	@echo "$(FLAGS_DIR) updated."

$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(OUTPUT)
$(OBJ_DIR)/%.o: prog/source/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
$(OBJ_DIR)/%.o: external/source/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@if [ -d "$(OBJ_DIR)" ]; then $(RM) $(OBJ_DIR); fi
	@if [ -f $(OUTPUT) ]; then $(RM) $(OUTPUT); fi
