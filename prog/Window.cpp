#include "Window.hpp" // Window

Window window;

SDL_Window* Window::getWindow() const { return graphicsApplicationWindow; }
SDL_GLContext Window::getGLContext() const { return GLContext; }
int Window::getWidth() const { return width; }
int Window::getHeight() const { return height; }
bool Window::getQuit() const { return quit; }

void Window::handleFullscreen()
{
    if (fullscreen)
    {
        SDL_SetWindowFullscreen(graphicsApplicationWindow, 0); // Windowed
        fullscreen = false;
    }
    else
    {
        SDL_SetWindowFullscreen(graphicsApplicationWindow, SDL_WINDOW_FULLSCREEN_DESKTOP); // Borderless fullscreen
        fullscreen = true;
    }
}
void Window::handleResize()
{
    SDL_GetWindowSize(graphicsApplicationWindow, &width, &height);
    glViewport(0, 0, width, height);
}
void Window::handleQuit()
{
    quit = true;
}

void Window::init()
{ 
    graphicsApplicationWindow = SDL_CreateWindow(
                                                  "SDLGL Test",     // Window title
                                                  100, 100,         // Window top left corner coordinates
                                                  width, height,    // Window width and height
                                                  SDL_WINDOW_OPENGL // Window type
                                                 );
    if (graphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window could not be created!" << std::endl;
        exit(1);
    }    

    GLContext = SDL_GL_CreateContext(graphicsApplicationWindow); // Creates an OpenGL context associated with the window
    if (GLContext == nullptr)
    {
        std::cout << "OpenGl context could not be created!" << std::endl;
        exit(1);
    }
}
