#include "TimeUtil.hpp"

Time time_util;

float Time::getDeltaTime() { return deltaTime; }

void Time::UpdateDeltaTime()
{
    currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
}
