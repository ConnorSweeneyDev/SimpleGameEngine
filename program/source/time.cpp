#include "rename.hpp"

#include "time.hpp"

namespace cse::time
{
  float delta_time = 0.0f;
  float current_time = 0.0f;
  float last_time = 0.0f;

  void update_delta_time()
  {
    current_time = (float)sdl::get_ticks_64();
    delta_time = (current_time - last_time);
    last_time = current_time;
  }
}
