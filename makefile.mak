# g++ -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Isrc/include/stbi prog/*.cpp src/glad.c -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -o 3DGameEngine.exe

RM = rm -rf
CXX = g++
CC = gcc

# RELEASE FLAGS:
# CXXFLAGS = -s -O3 -std=c++20 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wall -Wextra -Wpedantic
# CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-all

# DEBUG FLAGS:
CXXFLAGS = -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter
CFLAGS = -g -O0

INCLUDES = -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Isrc/include/stbi
LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2
CPP_SRCS = $(wildcard prog/*.cpp)
C_SRCS = src/glad.c
OUTPUT = 3DGameEngine.exe

OBJ_DIR = prog/object
$(shell if [ ! -d "$(OBJ_DIR)" ]; then mkdir -p $(OBJ_DIR); fi)
OBJS = $(patsubst prog/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS)) $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

FLAGS_DIR = compile_flags.txt

all: $(OUTPUT) compile_flags

compile_flags:
	@echo -n > $(FLAGS_DIR)
	@for flag in $(CXXFLAGS); do echo $$flag; done >> $(FLAGS_DIR) 
	@for flag in $(INCLUDES); do echo $$flag; done >> $(FLAGS_DIR)
	@for flag in $(LIBS); do echo $$flag; done >> $(FLAGS_DIR) 
	@echo -o$(OUTPUT) >> $(FLAGS_DIR) 
	@echo "$(FLAGS_DIR) updated."

$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(OUTPUT)
$(OBJ_DIR)/%.o: prog/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)/* $(OUTPUT) $(FLAGS_DIR)
