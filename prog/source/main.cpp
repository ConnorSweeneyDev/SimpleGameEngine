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

void vertex_specification()
{
    render.specify_objects();
    render.vertex_cleanup();
}

void create_graphics_pipeline()
{
    shader.assign_shaders_to_objects();
}

void initialize_game()
{
    game.object_init();
}

void read_input()
{
    input.poll_window();
    input.poll_game();
}

void pre_draw()
{
    render.pre_draw_init();
    render.pre_draw_objects();
}

void draw()
{
    render.draw_objects();
    render.draw_cleanup();
}

void game_loop()
{
    while (!window.should_quit())
    {
        time_util.update_delta_time();
        read_input();

        pre_draw();
        draw();

        SDL_GL_SwapWindow(window.get_window());
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

    vertex_specification();
    create_graphics_pipeline();
    initialize_game();

    game_loop();

    cleanup_program();

    return 0;
}
