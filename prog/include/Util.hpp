#pragma once

#include "Window.hpp"
#include "Player.hpp"

#define CheckGL(function) util.ClearAllGLErrors(); function; util.CheckGLErrorStatus(#function, __FILE__, __LINE__);

class Util
{
    public:
        void getOpenGLVersionInfo();
        float getDeltaTime();
 
        void ClearAllGLErrors();
        bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line);

        void UpdateDeltaTime();

        void sdlinit();
        void gladinit();
        
        void sdlcleanup();

    private:
        float deltaTime = 0.0f;
        float currentTime = 0.0f;
        float lastTime = 0.0f;
};
extern Util util;
