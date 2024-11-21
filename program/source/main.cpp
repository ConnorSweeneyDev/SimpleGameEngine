#define SDL_MAIN_HANDLED

#include "main.hpp"
#include "input.hpp"
#include "render.hpp"
#include "scene.hpp"
#include "shader.hpp"
#include "system.hpp"
#include "texture.hpp"
#include "time.hpp"
#include "window.hpp"

int main()
{
  initialize_system();

  initialize_game();
  play_game();
  cleanup_game();

  cleanup_system();
  return 0;
}

void initialize_system()
{
  cse::system::initialize_sdl();
  cse::system::window.initialize();
  cse::system::initialize_glad();
}

void initialize_game()
{
  cse::object::render.initialize();  // Go here to set objects
  cse::object::texture.initialize(); // Go here to set object textures
  cse::object::shader.initialize();  // Go here to set object shaders
  cse::scene::initialize_objects();  // Go here to set up the scene
}

void play_game()
{
  while (!cse::system::window.should_quit)
  {
    cse::time::update();
    while (cse::time::is_behind())
    {
      cse::input::read(); // Go here to set keybindings
      cse::object::texture.update_all();
      cse::time::catchup();
    }
    cse::object::render.update_all();
  }
}

void cleanup_game() { cse::object::render.remove_all(); }

void cleanup_system()
{
  cse::system::window.cleanup();
  cse::system::cleanup_sdl();
}
