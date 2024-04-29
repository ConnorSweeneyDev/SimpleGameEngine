#include <iostream>

#include "window.hpp"

namespace cse::platform
{
    Window window;

    void Window::handle_fullscreen()
    {
        if (SDL_GetDesktopDisplayMode(0, &display_mode))
        {
            std::cout << "Couldn't get desktop display mode!" << std::endl;
            return;
        }

        if (fullscreen)
        {
            SDL_SetWindowSize(application, starting_width, starting_height);
            SDL_SetWindowPosition(application, starting_pos_x, starting_pos_y);

            width = starting_width;
            height = starting_height;
            fullscreen = false;
            return;
        }

        SDL_SetWindowSize(application, display_mode.w, display_mode.h);
        SDL_SetWindowPosition(application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        width = display_mode.w;
        height = display_mode.h;
        fullscreen = true;
    }

    void Window::init()
    { 
        application = SDL_CreateWindow("3D Game Engine", starting_pos_x, starting_pos_y, starting_width, starting_height, SDL_WINDOW_OPENGL);

        if (application == nullptr)
        {
            std::cout << "SDL_Window could not be created!" << std::endl;
            exit(1);
        }

        gl_context = SDL_GL_CreateContext(application);
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
            SDL_SetWindowSize(application, display_mode.w, display_mode.h);
            SDL_SetWindowPosition(application, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

            width = display_mode.w;
            height = display_mode.h;
        }
    }

    void Window::cleanup()
    {
        SDL_GL_DeleteContext(gl_context);
        SDL_DestroyWindow(application);
        application = nullptr;

        SDL_Quit();
    }
}
