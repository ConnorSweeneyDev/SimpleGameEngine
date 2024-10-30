#include <chrono>
#include <iostream>
#include <string>

#include "timer.hpp"

namespace cse::time
{
  Timer::Timer(const std::string &i_name) : name(i_name)
  {
    time = std::chrono::high_resolution_clock::now();
  }
  Timer::~Timer() { std::cout << name << ": " << milliseconds() << "ms\n"; }

  float Timer::microseconds() const
  {
    return (float)std::chrono::duration_cast<std::chrono::microseconds>(
             std::chrono::high_resolution_clock::now() - time)
      .count();
  }
  float Timer::milliseconds() const { return microseconds() * 0.001f; }
  float Timer::seconds() const { return milliseconds() * 0.001f; }
}
