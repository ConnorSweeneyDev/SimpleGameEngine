#include <climits>
#include <iostream>
#include <string>

#include "glad.h"
#include "rename.hpp"

#include "item.hpp"
#include "player.hpp"
#include "render.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace cse::object
{
  void Render::initialize()
  {
    players.reserve(2);
    add<Player>("Player 1");
    add<Player>("Player 2");

    items.reserve(50);
    add<Item>("Background 1");
    add<Item>("Background 2");
    add<Item>("Background 3");
    add<Item>("Shop");
    add<Item>("Floor");
  }

  void Render::update_all()
  {
    call_for_all(
      [](auto object)
      {
        if (object->lifetime_frames % 60 == 0 && object->lifetime_frames != 0)
        {
          object->texture_data.current_frame++;
          if (object->texture_data.current_frame > object->texture_data.total_frames)
            object->texture_data.current_frame = 1;

          texture.update(object);
        }

        object->lifetime_frames++;
        if (object->lifetime_frames == ULLONG_MAX) object->lifetime_frames = 0;
      });

    initialize_pre_draw();
    call_for_all([this](auto object) { pre_draw_vertices(object); });
    call_for_all([this](auto object) { draw_vertices(object); });
    cleanup_draw();
    sdl::gl_swap_window(system::window.application);
  }

  void Render::remove_all()
  {
    call_for_all([this](auto object) { cleanup(object); }, Call_action::REMOVE);
  }

  gl::Int Render::get_uniform_location_by_name(const gl::Uint shader_object, const std::string &name)
  {
    gl::Int uniform_location = gl::get_uniform_location(shader_object, name.c_str());
    if (uniform_location <= -1)
    {
      std::cout << "Uniform location could not be found: " << name << std::endl;
      return -1;
    }

    return uniform_location;
  }

  void Render::initialize_pre_draw()
  {
    gl::enable(GL_DEPTH_TEST);
    gl::disable(GL_CULL_FACE);
    gl::enable(GL_MULTISAMPLE);
    gl::enable(GL_BLEND);
    gl::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    gl::viewport(0, 0, system::window.width, system::window.height);

    gl::clear_color(0.0f, 0.0f, 0.0f, 1.0f);
    gl::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
  }

  void Render::cleanup_vertices()
  {
    gl::bind_vertex_array(0);
    gl::disable_vertex_attrib_array(0);
    gl::disable_vertex_attrib_array(1);
    gl::disable_vertex_attrib_array(2);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }

  void Render::cleanup_draw()
  {
    gl::bind_vertex_array(0);
    gl::use_program(0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
