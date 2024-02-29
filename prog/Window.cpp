#include "Window.hpp"

Window window;

SDL_Window* Window::getWindow() const { return graphicsApplicationWindow; }
const SDL_GLContext& Window::getGLContext() const { return GLContext; }
const int& Window::getWidth() const { return width; }
const int& Window::getHeight() const { return height; }
const bool& Window::getQuit() const { return quit; }

void Window::HandleFullscreen()
{
    if (SDL_GetDesktopDisplayMode(0, &displayMode))
    {
        std::cout << "Couldn't get desktop display mode!" << std::endl;
        return;
    }

    if (fullscreen)
    {
        SDL_SetWindowSize(graphicsApplicationWindow, startingWidth, startingHeight);
        SDL_SetWindowPosition(graphicsApplicationWindow, startingPosX, startingPosY);

        width = startingWidth;
        height = startingHeight;

        fullscreen = false;
        return;
    }

    SDL_SetWindowSize(graphicsApplicationWindow, displayMode.w, displayMode.h);
    SDL_SetWindowPosition(graphicsApplicationWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    width = displayMode.w;
    height = displayMode.h;

    fullscreen = true;
}
void Window::HandleQuit()
{
    quit = true;
}

void Window::init()
{ 
    graphicsApplicationWindow = SDL_CreateWindow("3D Game Engine",
                                                 startingPosX, startingPosY,
                                                 startingWidth, startingHeight,
                                                 SDL_WINDOW_OPENGL);

    if (graphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window could not be created!" << std::endl;
        exit(1);
    }

    GLContext = SDL_GL_CreateContext(graphicsApplicationWindow);
    if (GLContext == nullptr)
    {
        std::cout << "OpenGl context could not be created!" << std::endl;
        exit(1);
    }

    if (SDL_GetDesktopDisplayMode(0, &displayMode))
    {
        std::cout << "Couldn't get desktop display mode!" << std::endl;
        exit(1);
    }
    if (fullscreen)
    {
        SDL_SetWindowSize(graphicsApplicationWindow, displayMode.w, displayMode.h);
        SDL_SetWindowPosition(graphicsApplicationWindow, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

        width = displayMode.w;
        height = displayMode.h;
    }
}
void Window::cleanup()
{
    SDL_GL_DeleteContext(GLContext);
    SDL_DestroyWindow(graphicsApplicationWindow);

    graphicsApplicationWindow = nullptr;
}
