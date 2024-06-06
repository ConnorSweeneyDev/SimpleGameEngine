#include <iostream>

#include "rename.hpp"
#include <SDL.h>
#include <glad.h>

#include "window.hpp"

namespace cse::platform
{
  Window window;

  void fullscreen_disable(bool &fullscreen, int starting_width, int starting_height,
                          int starting_pos_x, int starting_pos_y)
  {
#ifdef _WIN32
    sdl::set_window_bordered(window.application, SDL_TRUE);
    sdl::set_window_size(window.application, starting_width, starting_height);
    sdl::set_window_position(window.application, starting_pos_x, starting_pos_y);
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(window.application, 0);
    gl::viewport(0, 0, starting_width, starting_height);
#endif
    // #ifdef __APPLE__
    // Mac not yet supported.
    // #endif

    window.width = starting_width;
    window.height = starting_height;
    fullscreen = false;
  }

  void fullscreen_enable(bool &fullscreen, sdl::Display_mode &display_mode)
  {
#ifdef _WIN32
    sdl::set_window_bordered(window.application, SDL_FALSE);
    sdl::set_window_size(window.application, display_mode.w, display_mode.h);
    sdl::set_window_position(window.application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(window.application, SDL_WINDOW_FULLSCREEN_DESKTOP);
    gl::viewport(0, 0, display_mode.w, display_mode.h);
#endif
    // #ifdef __APPLE__
    // Mac not yet supported.
    // #endif

    window.width = display_mode.w;
    window.height = display_mode.h;
    fullscreen = true;
  }

  void Window::handle_fullscreen()
  {
    if (sdl::get_desktop_display_mode(0, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode!" << std::endl;
      return;
    }

    if (fullscreen)
      fullscreen_disable(fullscreen, starting_width, starting_height, starting_pos_x,
                         starting_pos_y);
    else
      fullscreen_enable(fullscreen, display_mode);
  }

  void Window::init()
  {
    width = starting_width;
    height = starting_height;

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
    if (fullscreen) fullscreen_enable(fullscreen, display_mode);
  }

  void Window::cleanup()
  {
    sdl::gl_delete_context(gl_context);
    sdl::destroy_window(application);
    application = nullptr;

    sdl::quit();
  }
}
