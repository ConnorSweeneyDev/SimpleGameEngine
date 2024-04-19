#pragma once

#include <SDL2/SDL.h>

class Window
{
    public:
        SDL_Window* get_window() const;
        const SDL_GLContext& get_gl_context() const;
        const int& get_width() const;
        const int& get_height() const;

        const bool& should_quit() const;
        void handle_quit();
        void handle_fullscreen();

        void init();
        void cleanup();

    private:
        bool quit = false;
        bool fullscreen = false;

        const int startingPosX = 100;
        const int startingPosY = 100;
        const int startingWidth = 1280;
        const int startingHeight = 720;
        int width = startingWidth;
        int height = startingHeight;

        SDL_Window* graphicsApplicationWindow = nullptr;
        SDL_GLContext glContext = nullptr;
        SDL_DisplayMode displayMode;
};
extern Window window;
