#define SDL_MAIN_HANDLED

#include "input.hpp"
#include "render.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "system.hpp"
#include "texture.hpp"
#include "time.hpp"
#include "window.hpp"

void system_init()
{
  cse::system::sdl_init();
  cse::system::window.init();
  cse::system::glad_init();
}

void specify_game()
{
  cse::object::render.specify();  // Go here to add objects
  cse::object::texture.specify(); // Go here to set textures
  cse::object::shader.specify();  // Go here to set shaders
  cse::scene::specify();          // Go here to setup the scene
}

void play_game()
{
  while (!cse::system::window.should_quit)
  {
    cse::time::update();
    while (cse::time::is_behind())
    {
      cse::input::read(); // Go here to set keybindings
      cse::time::catchup();
    }
    cse::object::render.update();
  }

  cse::object::render.cleanup_all();
}

int main()
{
  system_init();
  specify_game();
  play_game();
  cse::system::cleanup();
  return 0;
}
