#include "rename.hpp"

#include "time.hpp"

namespace cse::time
{
  constexpr double poll_rate = 60.0;
  double target = 1000.0 / poll_rate;

  double previous = (double)sdl::get_ticks_64();
  double lag = 0.0;
  void update()
  {
    double current = (double)sdl::get_ticks_64();
    double elapsed = current - previous;
    previous = current;
    lag += elapsed;
  }
  bool is_behind() { return lag >= target; }
  void catchup() { lag -= target; }
}
