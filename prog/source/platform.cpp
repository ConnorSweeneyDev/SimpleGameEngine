#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>

#include "platform.hpp"
#include "window.hpp"

namespace cse
{
    Platform platform;

    void Platform::display_open_gl_version_info() const
    {
        std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl
                  << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl
                  << "GL Version: " << glGetString(GL_VERSION) << std::endl
                  << "GL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
    }

    void Platform::clear_all_gl_errors() { while (glGetError() != GL_NO_ERROR); }

    void Platform::check_gl_error_status(const char* function_name, const char* file_name, int line) const
    {
        while (GLenum error = glGetError())
        {
            std::cout << "OpenGL Error " << std::hex << error << std::dec << " | Function: " << function_name << " | File: " << file_name << " | Line: " << line << std::endl;
            return;
        }
    }

    void Platform::sdl_init()
    {
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        {
            std::cout << "SDL2 could not be initialized!" << std::endl;
            exit(1);
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // Antialiasing
        SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
        SDL_GL_SetSwapInterval(0); // Vsync
    }

    void Platform::glad_init()
    {
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        {
            std::cout << "Glad could not be initialized!" << std::endl;
            exit(1);
        }
    }
}
