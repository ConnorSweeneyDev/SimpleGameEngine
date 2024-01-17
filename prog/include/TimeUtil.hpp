#pragma once

#include "SDL2/SDL.h"

class Time
{
    public:
        float getDeltaTime();
        
        void UpdateDeltaTime();

    private:
        float deltaTime = 0.0f;
        float currentTime = 0.0f;
        float lastTime = 0.0f;
};
extern Time time_util;
