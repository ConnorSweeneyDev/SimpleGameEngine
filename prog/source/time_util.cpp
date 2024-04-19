#include "SDL2/SDL_timer.h"

#include "time_util.hpp"

Time_util time_util;

const float& Time_util::get_delta_time() const { return delta_time; }

void Time_util::update_delta_time()
{
    current_time = SDL_GetTicks64();
    delta_time = (current_time - last_time);
    last_time = current_time;
}
