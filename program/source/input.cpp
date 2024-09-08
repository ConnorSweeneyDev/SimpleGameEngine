#include "rename.hpp"
#include <SDL_events.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

#include "camera.hpp"
#include "input.hpp"
#include "item.hpp"
#include "player.hpp"
#include "property.hpp"
#include "render.hpp"
#include "resource.hpp"
#include "window.hpp"

namespace cse::input
{
  sdl::Event handler;
  const sdl::Uint8 *key_state = sdl::get_keyboard_state(nullptr);

  void read()
  {
    while (sdl::poll_event(&handler) != 0)
    {
      switch (handler.type)
      {
        case SDL_QUIT: system::window.should_quit = true; break;

        case SDL_WINDOWEVENT:
          if (handler.window.event == SDL_WINDOWEVENT_MOVED) system::window.handle_move();
          break;

        case SDL_KEYDOWN:
          if (key_state[SDL_SCANCODE_ESCAPE]) system::window.should_quit = true;
          if (key_state[SDL_SCANCODE_F11]) system::window.handle_fullscreen();
          break;

        default: break;
      }
    }

    if (key_state[SDL_SCANCODE_H]) object::camera.move_right(0.005f);
    if (key_state[SDL_SCANCODE_F]) object::camera.move_left(0.005f);
    if (key_state[SDL_SCANCODE_T]) object::camera.move_up(0.005f);
    if (key_state[SDL_SCANCODE_G]) object::camera.move_down(0.005f);
    if (key_state[SDL_SCANCODE_Y]) object::camera.move_forward(0.005f);
    if (key_state[SDL_SCANCODE_R]) object::camera.move_backward(0.005f);
    if (key_state[SDL_SCANCODE_SPACE]) object::camera.reset_orientation();

    // Tests for adding and removing objects dynamically
    if (key_state[SDL_SCANCODE_9])
    {
      object::render.initialize_dynamic<object::Item>(
        "Item 1", object::Texture_data{"assets/redhood.png"},
        object::Shader_data{vertex_shader_resource, fragment_shader_resource},
        object::Transform_data{glm::Vec3(0.0f, 0.0f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.f),
                               glm::Vec3(1.0f, 1.0f, 1.0f)});
    }
    auto item1 = object::render.get_by_name<object::Item>("Item 1");
    if (item1)
      if (key_state[SDL_SCANCODE_0]) object::render.remove(item1);

    if (key_state[SDL_SCANCODE_7])
    {
      object::render.initialize_dynamic<object::Item>(
        "Item 2", object::Texture_data{"assets/lamp.png"},
        object::Shader_data{vertex_shader_resource, fragment_shader_resource},
        object::Transform_data{glm::Vec3(0.0f, 0.0f, 0.0f), glm::Vec3(0.0f, 0.0f, 0.f),
                               glm::Vec3(1.0f, 1.0f, 1.0f)});
    }
    auto item2 = object::render.get_by_name<object::Item>("Item 2");
    if (item2)
      if (key_state[SDL_SCANCODE_8]) object::render.remove(item2);

    auto player1 = object::render.get_by_name<object::Player>("Player 1");
    if (player1)
    {
      if (key_state[SDL_SCANCODE_D]) player1->move_right();
      if (key_state[SDL_SCANCODE_A]) player1->move_left();
      if (key_state[SDL_SCANCODE_W]) player1->move_up();
      if (key_state[SDL_SCANCODE_S]) player1->move_down();
      if (key_state[SDL_SCANCODE_E]) player1->move_forward();
      if (key_state[SDL_SCANCODE_Q]) player1->move_backward();
      if (key_state[SDL_SCANCODE_SPACE]) player1->reset_transform();
    }

    auto player2 = object::render.get_by_name<object::Player>("Player 2");
    if (player2)
    {
      if (key_state[SDL_SCANCODE_L]) player2->move_right();
      if (key_state[SDL_SCANCODE_J]) player2->move_left();
      if (key_state[SDL_SCANCODE_I]) player2->move_up();
      if (key_state[SDL_SCANCODE_K]) player2->move_down();
      if (key_state[SDL_SCANCODE_O]) player2->move_forward();
      if (key_state[SDL_SCANCODE_U]) player2->move_backward();
      if (key_state[SDL_SCANCODE_SPACE]) player2->reset_transform();
    }
  }
}
