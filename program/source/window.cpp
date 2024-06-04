#include <iostream>

#include "rename.hpp"
#include <SDL.h>
#include <glad.h>

#include "window.hpp"

namespace cse::platform
{
  Window window;

  void Window::handle_fullscreen()
  {
    if (sdl::get_desktop_display_mode(0, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode!" << std::endl;
      return;
    }

    if (fullscreen)
    {
      sdl::set_window_size(application, starting_width, starting_height);
      sdl::set_window_position(application, starting_pos_x, starting_pos_y);

      width = starting_width;
      height = starting_height;
      fullscreen = false;
      return;
    }

    sdl::set_window_size(application, display_mode.w, display_mode.h);
    sdl::set_window_position(application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    width = display_mode.w;
    height = display_mode.h;
    fullscreen = true;
  }

  void Window::init()
  {
    application = sdl::create_window("3D Game Engine", starting_pos_x, starting_pos_y,
                                     starting_width, starting_height, SDL_WINDOW_OPENGL);
    if (application == nullptr)
    {
      std::cout << "SDL window could not be created!" << std::endl;
      exit(1);
    }

    gl_context = sdl::gl_create_context(application);
    if (gl_context == nullptr)
    {
      std::cout << "OpenGl context could not be created!" << std::endl;
      exit(1);
    }

    if (sdl::get_desktop_display_mode(0, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode!" << std::endl;
      exit(1);
    }
    if (fullscreen)
    {
      sdl::set_window_size(application, display_mode.w, display_mode.h);
      sdl::set_window_position(application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

      width = display_mode.w;
      height = display_mode.h;
    }
  }

  void Window::cleanup()
  {
    sdl::gl_delete_context(gl_context);
    sdl::destroy_window(application);
    application = nullptr;

    sdl::quit();
  }
}
