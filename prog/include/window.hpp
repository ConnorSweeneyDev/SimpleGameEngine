#pragma once

#include <SDL2/SDL.h>

namespace cse
{
    class Window
    {
        public:
            SDL_Window* get_window() const;
            const int& get_width() const;
            const int& get_height() const;

            void handle_fullscreen();

            void init();
            void cleanup();

            bool should_quit = false;

        private:
            bool fullscreen = false;

            const int starting_pos_x = 100;
            const int starting_pos_y = 100;
            const int starting_width = 1280;
            const int starting_height = 720;
            int width = starting_width;
            int height = starting_height;

            SDL_Window* application_window = nullptr;
            SDL_GLContext gl_context = nullptr;
            SDL_DisplayMode display_mode = {0, 0, 0, 0, 0};
    };
    extern Window window;
}
