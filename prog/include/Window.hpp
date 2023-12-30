#pragma once

#include <iostream> // Console output

#include <SDL2/SDL.h>  // SDL_Window, SDL_GLContext
#include <glad/glad.h> // Load OpenGL functions

class Window // Stores window settings and functions
{
    public:
        SDL_Window* getWindow() const;
        SDL_GLContext getGLContext() const;
        int& getWidth() const;
        int& getHeight() const;
        bool getFullscreen() const;
        bool getQuit() const;
        
        void setFullscreen(bool fullscreen);
        void setQuit(bool quit);

        void handleFullscreen();
        void handleResize();
        void handleQuit();

        void init();

    private:
        int width = 1280;
        int height = 720;
        SDL_Window* graphicsApplicationWindow = nullptr; // Pointer to the window
        SDL_GLContext GLContext = nullptr;
        bool quit = false;
        bool fullscreen = false;
};
extern Window window;
