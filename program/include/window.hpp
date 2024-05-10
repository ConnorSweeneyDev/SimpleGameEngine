#pragma once

#include <SDL2/SDL.h>

namespace cse::platform
{
    class Window
    {
        public:
            void handle_fullscreen();

            void init();
            void cleanup();

            bool should_quit = false;
            const int starting_width = 1280;
            const int starting_height = 720;
            int width = starting_width;
            int height = starting_height;

            SDL_Window* application;

        private:
            bool fullscreen = false;

            const int starting_pos_x = 100;
            const int starting_pos_y = 100;

            SDL_GLContext gl_context;
            SDL_DisplayMode display_mode;
    };
    extern Window window;
}
