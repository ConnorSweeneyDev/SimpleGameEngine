# g++ -g -std=c++23 prog/*.cpp src/glad.c -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2 -Lsrc/lib -Wall -lmingw32 -lSDL2main -lSDL2 -o 3DGameEngine.exe

CXX = g++
CC = gcc

CXXFLAGS = -g -std=c++23 -Wall
CFLAGS = -g -Wall

INCLUDES = -Iprog/include -Isrc/include -Isrc/include/glad -Isrc/include/glm -Isrc/include/KHR -Isrc/include/SDL2
LIBS = -Lsrc/lib -lmingw32 -lSDL2main -lSDL2
CPP_SRCS = $(wildcard prog/*.cpp)
C_SRCS = src/glad.c

OUTPUT = 3DGameEngine.exe

OBJ_DIR = prog/object
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
