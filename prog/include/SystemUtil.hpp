#pragma once

#include "Window.hpp"
#include "Player.hpp"
#include "Item.hpp"

#define CheckGL(function) system_util.ClearAllGLErrors(); function; system_util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class SystemUtil
{
    public:
        void getOpenGLVersionInfo() const;
        template <typename Type> std::shared_ptr<Type> getObjectByName(const std::string& name) const;
 
        void ClearAllGLErrors();
        void CheckGLErrorStatus(const char* functionName, const char* fileName, int line) const;

        void sdlinit();
        void gladinit();
        
        void sdlcleanup();
};
extern SystemUtil system_util;
