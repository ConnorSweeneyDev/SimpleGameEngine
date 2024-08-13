#include <cstdlib>
#include <iostream>

#include "rename.hpp"
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <glad.h>

#include "window.hpp"

namespace cse::system
{
  void Window::handle_move()
  {
    if (fullscreen) return;

    sdl::get_window_position(application, &position_x, &position_y);
    display_index = sdl::get_window_display_index(application);
  }

  void Window::handle_fullscreen()
  {
    if (sdl::get_desktop_display_mode(display_index, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode: " << sdl::get_error() << std::endl;
      return;
    }

    if (fullscreen)
      disable_fullscreen();
    else
      enable_fullscreen();
  }

  void Window::initialize()
  {
    width = starting_width;
    height = starting_height;
    position_x = (int)SDL_WINDOWPOS_CENTERED_DISPLAY(display_index);
    position_y = (int)SDL_WINDOWPOS_CENTERED_DISPLAY(display_index);

    for (int i = 0; i < sdl::get_num_video_displays(); i++)
    {
      sdl::Rect display_bound;
      sdl::get_display_bounds(i, &display_bound);
      display_bounds.push_back(display_bound);
    }
    if (display_bounds.empty())
    {
      std::cout << "Couldn't get display bounds: " << sdl::get_error() << std::endl;
      exit(1);
    }

    application =
      sdl::create_window("Simple Game Engine", display_bounds[(size_t)display_index].x + position_x,
                         display_bounds[(size_t)display_index].y + position_y, starting_width,
                         starting_height, SDL_WINDOW_OPENGL);
    if (application == nullptr)
    {
      std::cout << "SDL window could not be created: " << sdl::get_error() << std::endl;
      exit(1);
    }
    sdl::set_window_resizable(application, SDL_FALSE);

    gl_context = sdl::gl_create_context(application);
    if (gl_context == nullptr)
    {
      std::cout << "OpenGl context could not be created: " << sdl::get_error() << std::endl;
      exit(1);
    }

    if (sdl::get_desktop_display_mode(display_index, &display_mode))
    {
      std::cout << "Couldn't get desktop display mode: " << sdl::get_error() << std::endl;
      exit(1);
    }
    if (fullscreen) enable_fullscreen();
  }

  void Window::cleanup()
  {
    sdl::gl_delete_context(gl_context);
    sdl::destroy_window(application);
    application = nullptr;
  }

  void Window::disable_fullscreen()
  {
#ifdef _WIN32
    sdl::set_window_bordered(application, SDL_TRUE);
    sdl::set_window_size(application, starting_width, starting_height);
    sdl::set_window_position(application, position_x, position_y);
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(application, 0);
    sdl::set_window_position(application, position_x, position_y);
#endif

    width = starting_width;
    height = starting_height;
    fullscreen = false;
  }

  void Window::enable_fullscreen()
  {
#ifdef _WIN32
    sdl::set_window_bordered(application, SDL_FALSE);
    sdl::set_window_size(application, display_mode.w, display_mode.h + 1);
    sdl::set_window_position(application, (int)SDL_WINDOWPOS_CENTERED_DISPLAY(display_index),
                             (int)SDL_WINDOWPOS_CENTERED_DISPLAY(display_index));
#endif
#ifdef __linux__
    sdl::set_window_fullscreen(application, SDL_WINDOW_FULLSCREEN_DESKTOP);
#endif

    width = display_mode.w;
    height = display_mode.h;
    fullscreen = true;
  }
}
