@ECHO OFF

g++ -std=c++11 prog\main.cpp src\glad.c -Isrc\include -Lsrc\lib -Wall -lmingw32 -lSDL2main -lSDL2 -o SDLGLTest
