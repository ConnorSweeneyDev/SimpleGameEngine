#include "Window.hpp" // Window

Window window;

SDL_Window* Window::getWindow() const { return window.graphicsApplicationWindow; }
SDL_GLContext Window::getGLContext() const { return window.GLContext; }
int& Window::getWidth() const { return window.width; }
int& Window::getHeight() const { return window.height; }
bool Window::getFullscreen() const { return window.fullscreen; }
bool Window::getQuit() const { return window.quit; }

void Window::setFullscreen(bool fullscreen) { window.fullscreen = fullscreen; }
void Window::setQuit(bool quit) { window.quit = quit; }

void Window::handleFullscreen()
{
    if (window.fullscreen)
    {
        SDL_SetWindowFullscreen(window.getWindow(), 0); // Windowed
        window.setFullscreen(false);
    }
    else
    {
        SDL_SetWindowFullscreen(window.getWindow(), SDL_WINDOW_FULLSCREEN_DESKTOP); // Borderless fullscreen
        window.setFullscreen(true);
    }
}
void Window::handleResize()
{
    SDL_GetWindowSize(window.getWindow(), &window.getWidth(), &window.getHeight());
    glViewport(0, 0, window.getWidth(), window.getHeight());
}
void Window::handleQuit()
{
    window.setQuit(true);
}

void Window::init()
{ 
    window.graphicsApplicationWindow = SDL_CreateWindow(
                                                  "SDLGL Test",                // Window title
                                                  100, 100,                    // Window top left corner coordinates
                                                  window.width, window.height, // Window width and height
                                                  SDL_WINDOW_OPENGL            // Window type
                                                 );
    if (window.graphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window could not be created!" << std::endl;
        exit(1);
    }    

    window.GLContext = SDL_GL_CreateContext(window.graphicsApplicationWindow); // Creates an OpenGL context associated with the window
    if (window.GLContext == nullptr)
    {
        std::cout << "OpenGl context could not be created!" << std::endl;
        exit(1);
    }
}
