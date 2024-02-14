#pragma once

#include "Window.hpp"
#include "Player.hpp"
#include "Item.hpp"

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class Util
{
    public:
        void getOpenGLVersionInfo();
        template <typename Type> std::shared_ptr<Type> getObjectByName(const std::string& name);
 
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);

        std::vector<std::string> SplitStringByDelimiter(const std::string& string, std::string delimiter);

        void sdlinit();
        void gladinit();
        
        void sdlcleanup();
};
extern Util util;
