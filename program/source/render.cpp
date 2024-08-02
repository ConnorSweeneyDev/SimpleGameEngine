#include <iostream>
#include <string>

#include "rename.hpp"
#include <glad.h>

#include "item.hpp"
#include "player.hpp"
#include "render.hpp"
#include "window.hpp"

namespace cse::object
{
  Render render;

  void Render::specify()
  {
    add<Player>("Player 1");
    add<Player>("Player 2");

    add<Item>("Background 1");
    add<Item>("Background 2");
    add<Item>("Background 3");
    add<Item>("Shop");
    add<Item>("Floor");
  }

  void Render::cleanup_all()
  {
    call_for_all([this](auto object) { cleanup(object); }, Call_action::CLEANUP);
  }

  void Render::update()
  {
    pre_draw_init();
    call_for_all([this](auto object) { pre_draw_vertices(object); });
    call_for_all([this](auto object) { draw_vertices(object); });
    draw_cleanup();

    sdl::gl_swap_window(system::window.application);
  }

  gl::Int Render::get_uniform_location_by_name(const gl::Uint program, const std::string name)
  {
    gl::Int uniform_location = gl::get_uniform_location(program, name.c_str());
    if (uniform_location <= -1)
    {
      std::cout << "Uniform location could not be found: " << name << std::endl;
      return -1;
    }

    return uniform_location;
  }

  void Render::pre_draw_init()
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

  void Render::vertex_cleanup()
  {
    gl::bind_vertex_array(0);
    gl::disable_vertex_attrib_array(0);
    gl::disable_vertex_attrib_array(1);
    gl::disable_vertex_attrib_array(2);
    gl::bind_buffer(GL_ARRAY_BUFFER, 0);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }

  void Render::draw_cleanup()
  {
    gl::bind_vertex_array(0);
    gl::use_program(0);
    gl::bind_texture(GL_TEXTURE_2D, 0);
  }
}
