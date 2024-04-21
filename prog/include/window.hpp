#pragma once

#include <SDL2/SDL.h>

namespace cse
{
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

            const int starting_pos_x = 100;
            const int starting_pos_y = 100;
            const int starting_width = 1280;
            const int starting_height = 720;
            int width = starting_width;
            int height = starting_height;

            SDL_Window* application_window = nullptr;
            SDL_GLContext gl_context = nullptr;
            SDL_DisplayMode display_mode;
    };
    extern Window window;
}
