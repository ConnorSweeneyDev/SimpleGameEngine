#pragma once

#include <iostream> // Console output

#include <SDL2/SDL.h>  // SDL, SDL_GL 
#include <glad/glad.h> // Load OpenGL functions

class PlatformUtil // Stores utility functions for platform code
{
    public:
        void ClearAllGLErrors();                                                           // Functions for #define CheckGL(function), used to clear
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line); // Used to check for and display OpenGL errors

        void GetOpenGLVersionInfo();

        void sdlinit();
        void gladinit();
};
extern PlatformUtil platformUtil;
