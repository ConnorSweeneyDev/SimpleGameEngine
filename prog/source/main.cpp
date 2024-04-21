#include "system_util.hpp"
#include "time_util.hpp"
#include "window.hpp"
#include "render.hpp"
#include "shader.hpp"
#include "game.hpp"
#include "input.hpp"

void platform_init()
{
    system_util.sdl_init();
    window.init();
    system_util.glad_init();
}

void game_init()
{
    render.specify_objects();
    shader.specify_shaders();
    game.specify_game_state();
}

void draw()
{
    render.pre_draw_init();
    render.pre_draw_objects();
    render.draw_objects();
    render.draw_cleanup();
    SDL_GL_SwapWindow(window.get_window());
}

void game_loop()
{
    while (!window.should_quit())
    {
        time_util.update_delta_time();
        input.read();

        draw();
    }
}

void program_cleanup()
{
    render.cleanup_objects();
    window.cleanup();
}

int main(int argc, char* argv[])
{
    platform_init();
    game_init();

    game_loop();

    program_cleanup();
    return 0;
}
