#define SDL_MAIN_HANDLED

#include "input.hpp"
#include "render.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "system.hpp"
#include "time.hpp"
#include "window.hpp"

void system_init()
{
  cse::system::sdl_init();
  cse::system::window.init();
  cse::system::glad_init();
}

void game_specification()
{
  cse::object::render.specify();  // Go here to add objects
  cse::object::texture.specify(); // Go here to set textures
  cse::object::shader.specify();  // Go here to set shaders
  cse::scene::specify();          // Go here to setup the scene
}

void game_loop()
{
  while (!cse::system::window.should_quit)
  {
    cse::time::update_delta_time();
    cse::input::read(); // Go here to set keybindings
    cse::object::render.update();
  }
}

void program_cleanup()
{
  cse::object::render.cleanup_all();
  cse::system::window.cleanup();
}

int main()
{
  system_init();

  game_specification();
  game_loop();

  program_cleanup();
  return 0;
}
