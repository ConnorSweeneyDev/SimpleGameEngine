#include <iostream>

#include "window.hpp"

namespace cse
{
    Window window;

    SDL_Window* Window::get_window() const { return application_window; }
    const SDL_GLContext& Window::get_gl_context() const { return gl_context; }
    const int& Window::get_width() const { return width; }
    const int& Window::get_height() const { return height; }

    const bool& Window::should_quit() const { return quit; }

    void Window::handle_quit() { quit = true; }

    void Window::handle_fullscreen()
    {
        if (SDL_GetDesktopDisplayMode(0, &display_mode))
        {
            std::cout << "Couldn't get desktop display mode!" << std::endl;
            return;
        }

        if (fullscreen)
        {
            SDL_SetWindowSize(application_window, starting_width, starting_height);
            SDL_SetWindowPosition(application_window, starting_pos_x, starting_pos_y);

            width = starting_width;
            height = starting_height;
            fullscreen = false;
            return;
        }

        SDL_SetWindowSize(application_window, display_mode.w, display_mode.h);
        SDL_SetWindowPosition(application_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        width = display_mode.w;
        height = display_mode.h;
        fullscreen = true;
    }

    void Window::init()
    { 
        application_window = SDL_CreateWindow("3D Game Engine", starting_pos_x, starting_pos_y, starting_width, starting_height, SDL_WINDOW_OPENGL);

        if (application_window == nullptr)
        {
            std::cout << "SDL_Window could not be created!" << std::endl;
            exit(1);
        }

        gl_context = SDL_GL_CreateContext(application_window);
        if (gl_context == nullptr)
        {
            std::cout << "OpenGl context could not be created!" << std::endl;
            exit(1);
        }

        if (SDL_GetDesktopDisplayMode(0, &display_mode))
        {
            std::cout << "Couldn't get desktop display mode!" << std::endl;
            exit(1);
        }
        if (fullscreen)
        {
            SDL_SetWindowSize(application_window, display_mode.w, display_mode.h);
            SDL_SetWindowPosition(application_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

            width = display_mode.w;
            height = display_mode.h;
        }
    }

    void Window::cleanup()
    {
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(application_window);
        application_window = nullptr;

        SDL_Quit();
    }
}
