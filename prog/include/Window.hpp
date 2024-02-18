#pragma once

#include <iostream>

#include <SDL2/SDL.h>
#include <glad/glad.h>

class Window
{
    public:
        SDL_Window* getWindow() const;
        const SDL_GLContext getGLContext() const;
        const int getWidth() const;
        const int getHeight() const;
        const bool getQuit() const;

        void HandleFullscreen();
        void HandleResize();
        void HandleQuit();

        void init();

    private:
        SDL_Window* graphicsApplicationWindow = nullptr;
        SDL_GLContext GLContext = nullptr;
        const int startingPosX = 100;
        const int startingPosY = 100;
        const int startingWidth = 1280;
        const int startingHeight = 720;
        int width = startingWidth;
        int height = startingHeight;
        bool quit = false;
        bool fullscreen = false;
};
extern Window window;
