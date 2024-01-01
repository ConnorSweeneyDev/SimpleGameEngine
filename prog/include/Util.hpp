#pragma once

#include <iostream> // Console output

#include <SDL2/SDL.h>  // SDL_... 
#include <glad/glad.h> // Load OpenGL functions

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__); // Macro for use in finding and displaying OpenGL function errors

class Util // Stores utility functions for platform code
{
    public:
        void ClearAllGLErrors();                                                           // Functions for #define CheckGL(function), used to clear
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line); // Used to check for and display OpenGL errors

        void GetOpenGLVersionInfo();

        void sdlinit();
        void gladinit();
};
extern Util util;
