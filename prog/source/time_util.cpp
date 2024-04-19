#include "SDL2/SDL_timer.h"

#include "time_util.hpp"

TimeUtil time_util;

const float& TimeUtil::get_delta_time() const { return deltaTime; }

void TimeUtil::update_delta_time()
{
    currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
}
