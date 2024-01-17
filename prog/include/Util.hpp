#pragma once

#include "Window.hpp"
#include "Player.hpp"

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class Util
{
    public:
        void getOpenGLVersionInfo();
 
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);

        std::vector<std::string> SplitStringByDelimiter(const std::string& string, std::string delimiter);

        void sdlinit();
        void gladinit();
        
        void sdlcleanup();
};
extern Util util;
