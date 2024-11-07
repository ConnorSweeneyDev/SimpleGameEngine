#include <chrono>
#include <iostream>
#include <string>

#include "rename.hpp"

#include "time.hpp"

namespace cse::time
{
  sdl::Uint64 target = 1000 / poll_rate;
  sdl::Uint64 previous = sdl::get_ticks_64();
  sdl::Uint64 lag = 0;
  void update()
  {
    sdl::Uint64 current = sdl::get_ticks_64();
    sdl::Uint64 elapsed = current - previous;
    previous = current;
    lag += elapsed;
  }
  bool is_behind() { return lag >= target; }
  void catchup() { lag -= target; }

  Timer::Timer(const std::string &i_name) : name(i_name) { time = std::chrono::high_resolution_clock::now(); }
  Timer::~Timer() { std::cout << name << ": " << milliseconds() << "ms\n"; }
  long long Timer::microseconds() const
  {
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - time)
      .count();
  }
  float Timer::milliseconds() const { return (float)microseconds() * 0.001f; }
  float Timer::seconds() const { return milliseconds() * 0.001f; }
}
