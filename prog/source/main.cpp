#include "system_util.hpp"
#include "time_util.hpp"
#include "window.hpp"
#include "render.hpp"
#include "shader.hpp"
#include "game.hpp"
#include "input.hpp"

void initialize_program()
{
    system_util.sdl_init();
    window.init();
    system_util.glad_init();
}

void create_objects()
{
    render.specify_objects();
}

void create_graphics_pipeline()
{
    shader.specify_shaders();
}

void initialize_game()
{
    game.specify_game_state();
}

void read_input()
{
    input.read();
}

void pre_draw()
{
    render.pre_draw_init();
    render.pre_draw_objects();
}

void draw()
{
    pre_draw();

    render.draw_objects();
    render.draw_cleanup();

    SDL_GL_SwapWindow(window.get_window());
}

void game_loop()
{
    while (!window.should_quit())
    {
        time_util.update_delta_time();

        read_input();

        draw();
    }
}

void cleanup_program()
{
    render.cleanup_objects();
    system_util.sdl_cleanup();
}

int main(int argc, char* argv[])
{
    initialize_program();

    create_objects();
    create_graphics_pipeline();
    initialize_game();

    game_loop();

    cleanup_program();

    return 0;
}
