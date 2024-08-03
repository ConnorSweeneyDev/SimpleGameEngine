#pragma once

#include <vector>

#include "rename.hpp"
#include <SDL.h>

namespace cse::system
{
  class Window
  {
  public:
    void handle_move();
    void handle_fullscreen();

    void initialize();
    void cleanup();

    bool should_quit = false;
    int width = 0;
    int height = 0;

    sdl::Window *application = nullptr;

  private:
    void disable_fullscreen();
    void enable_fullscreen();

    bool fullscreen = false;
    int display_index = 0;
    std::vector<sdl::Rect> display_bounds;

    int position_x = 0;
    int position_y = 0;
    static constexpr int starting_width = 1280;
    static constexpr int starting_height = 720;

    sdl::Gl_context gl_context = nullptr;
    sdl::Display_mode display_mode = {};
  };

  extern Window window;
}
