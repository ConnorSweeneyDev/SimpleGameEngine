#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>

class Window
{
    public:
        SDL_Window* getWindow() const;
        SDL_GLContext getGLContext() const;
        int getWidth() const;
        int getHeight() const;
        bool getQuit() const;

        void handleFullscreen();
        void handleResize();
        void handleQuit();

        void init();

    private:
        SDL_Window* graphicsApplicationWindow = nullptr;
        SDL_GLContext GLContext = nullptr;
        int startingPosX = 100;
        int startingPosY = 100;
        int width = 1280;
        int height = 720;
        bool quit = false;
        bool fullscreen = false;
};
extern Window window;
