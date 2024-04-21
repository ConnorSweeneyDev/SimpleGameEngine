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

void game_specification()
{
    render.specify_objects(); //<-- Go here to add objects
  //texture.specify_textures(); <-- Go here to set textures
    shader.specify_shaders(); //<-- Go here to set shaders
    game.specify_scene();     //<-- Go here to setup the scene
}

void game_loop()
{
    while (!window.should_quit())
    {
        time_util.update_delta_time();
        input.read();
        render.draw();
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

    game_specification();
    game_loop();

    program_cleanup();
    return 0;
}
