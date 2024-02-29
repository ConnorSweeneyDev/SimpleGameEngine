# g++ -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Isrc/include/STBI prog/*.cpp src/glad.c -Lsrc/lib -lmingw32 -lSDL2main -lSDL2 -o 3DGameEngine.exe

CXX = g++
CC = gcc

# RELEASE FLAGS:
# CXXFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong -std=c++20 -Wall
# CFLAGS = -s -O3 -DNDEBUG -D_FORTIFY_SOURCE=2 -fstack-protector-strong -Wall

# DEBUG FLAGS:
CXXFLAGS = -g -O0 -std=c++20 -Wall -Wextra -Wpedantic -Wno-unused-parameter
CFLAGS = -g -O0 -Wall

INCLUDES = -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Isrc/include/STBI
LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2
CPP_SRCS = $(wildcard prog/*.cpp)
C_SRCS = src/glad.c
OUTPUT = 3DGameEngine.exe

OBJ_DIR = prog/object
$(shell if [ ! -d "$(OBJ_DIR)" ]; then mkdir -p $(OBJ_DIR); fi)
OBJS = $(patsubst prog/%.cpp,$(OBJ_DIR)/%.o,$(CPP_SRCS)) $(patsubst src/%.c,$(OBJ_DIR)/%.o,$(C_SRCS))

all: $(OUTPUT)

$(OUTPUT): $(OBJS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(OBJS) $(LIBS) -o $(OUTPUT)

$(OBJ_DIR)/%.o: prog/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@
$(OBJ_DIR)/%.o: src/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)/*.o $(OUTPUT)
