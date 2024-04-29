#include "platform.hpp"
#include "window.hpp"
#include "render.hpp"
#include "time.hpp"
#include "shader.hpp"
#include "scene.hpp"
#include "input.hpp"

void platform_init()
{
    cse::platform::sdl_init();
    cse::window.init();
    cse::platform::glad_init();
}

void game_specification()
{
    cse::render.specify_objects();      // Go here to add objects
    cse::texture.specify_textures();    // Go here to set textures
    cse::shader.specify_shaders();      // Go here to set shaders

    csg::scene::specify();               // Go here to setup the scene
}

void game_loop()
{
    while (!cse::window.should_quit)
    {
        cse::time::update_delta_time();
        cse::input::read();             // Go here to set keybindings
        cse::render.update();
    }
}

void program_cleanup()
{
    cse::render.cleanup_objects();
    cse::window.cleanup();
}

int main(int argc, char* argv[])
{
    platform_init();

    game_specification();
    game_loop();

    program_cleanup();
    return 0;
}
