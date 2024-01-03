#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class Util
{
    public:
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);

        void GetOpenGLVersionInfo();

        void sdlinit();
        void gladinit();
};
extern Util util;
