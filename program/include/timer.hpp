#pragma once

#include <chrono>
#include <string>

namespace cse::time
{
  class Timer
  {
  public:
    Timer(const std::string &i_name);
    ~Timer();

  private:
    float microseconds() const;
    float milliseconds() const;
    float seconds() const;

    std::string name;
    std::chrono::time_point<std::chrono::high_resolution_clock> time;
  };
}
