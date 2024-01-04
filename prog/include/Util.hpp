#pragma once

#include "Window.hpp"

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class Util
{
    public:
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);

        void getOpenGLVersionInfo();

        void sdlinit();
        void gladinit();
        void predrawinit();
        
        void sdlcleanup();
        void vertexcleanup();
        void drawcleanup();
};
extern Util util;
