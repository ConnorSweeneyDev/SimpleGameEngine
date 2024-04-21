#include "SDL2/SDL_timer.h"

#include "time.hpp"

namespace cse
{
    Time time;

    const float& Time::get_delta_time() const { return delta_time; }

    void Time::update_delta_time()
    {
        current_time = SDL_GetTicks64();
        delta_time = (current_time - last_time);
        last_time = current_time;
    }
}
