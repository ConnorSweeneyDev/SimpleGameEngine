#pragma once

#include <chrono>
#include <string>

#include "rename.hpp"

namespace cse::time
{
  constexpr sdl::Uint64 poll_rate = 144;
  void update();
  bool is_behind();
  void catchup();

  class Timer
  {
  public:
    Timer(const std::string &i_name);
    ~Timer();

  private:
    long long microseconds() const;
    float milliseconds() const;
    float seconds() const;

    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
  };
}
