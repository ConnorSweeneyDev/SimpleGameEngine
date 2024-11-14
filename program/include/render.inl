#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

#include "ext/matrix_transform.hpp"
#include "glad.h"
#include "gtc/type_ptr.hpp"
#include "rename.hpp"

#include "camera.hpp"
#include "data.hpp"
#include "item.hpp"
#include "player.hpp"
#include "render.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace cse::object
{
  template <typename Type> const Object_pointer<Type> Render::get_by_name(const std::string &name)
  {
    Object_pointer<Type> result = nullptr;
    call_for_all<Type>(
      [name, &result](auto object)
      {
        if (object->name == name) result = object;
      });

    return result;
  }

  // initialize_dynamic only exists for Item, not player due to player's initialize function taking specific parameters
  // will be changed to a different Type later (might not need to be a template function)
  template <typename Type>
  void Render::initialize_dynamic(const std::string &name, const Texture_data &texture_data,
                                  const Shader_data &shader_data, const Transform_data &transform_data)
  {
    if constexpr (std::is_same<Type, Item>::value)
      if (get_by_name<Item>(name) == nullptr)
        items.push_back(add_dynamic<Item>(name, texture_data, shader_data, transform_data));
  }

  template <typename Type> void Render::remove(Object_pointer<Type> &object)
  {
    cleanup(object);

    if constexpr (std::is_same<Type, Player>::value)
    {
      players.erase(std::remove_if(players.begin(), players.end(),
                                   [&object](const Player_pointer &player) { return player == object; }),
                    players.end());
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
      items.erase(
        std::remove_if(items.begin(), items.end(), [&object](const Item_pointer &item) { return item == object; }),
        items.end());
    }
    else
      std::cout << "Invalid Type!" << std::endl;
  }

  template <typename Type, typename Callable> void Render::call_for_all(Callable callable, Call_action action)
  {
    if constexpr (std::is_same<Type, void>::value)
    {
      for (auto &player : players) callable(player);
      for (auto &item : items) callable(item);
      switch (action)
      {
        case Call_action::REMOVE:
          players.clear();
          items.clear();
          break;

        default: break;
      }
    }
    else if constexpr (std::is_same<Type, Player>::value)
    {
      for (auto &player : players) callable(player);
      switch (action)
      {
        case Call_action::REMOVE: players.clear(); break;
        default: break;
      }
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
      for (auto &item : items) callable(item);
      switch (action)
      {
        case Call_action::REMOVE: items.clear(); break;
        default: break;
      }
    }
    else
      std::cout << "Invalid Type!" << std::endl;
  }

  template <typename Type> const Object_pointer<Type> Render::create(const std::string &name)
  {
    auto object = std::make_shared<Type>(name);
    specify_vertices(object);

    return object;
  }

  template <typename Type> void Render::add(const std::string &name)
  {
    if constexpr (std::is_same<Type, Player>::value)
      players.push_back(create<Player>(name));
    else if constexpr (std::is_same<Type, Item>::value)
      items.push_back(create<Item>(name));
    else
      std::cout << "Invalid Type!" << std::endl;
  }

  // add_dynamic only exists for Item, not player due to player's initialize function taking specific parameters will be
  // changed to a different Type later (might not need to be a template function)
  template <typename Type>
  const Object_pointer<Type> Render::add_dynamic(const std::string &name, const Texture_data &texture_data,
                                                 const Shader_data &shader_data, const Transform_data &transform_data)
  {
    if constexpr (std::is_same<Type, Item>::value)
    {
      auto object = create<Type>(name);
      specify_vertices(object);
      object->texture_data = texture_data;
      texture.update(object);
      object->shader_data = shader_data;
      shader.update(object);
      object->initialize(transform_data);
      return object;
    }
  }

  template <typename Type> void Render::specify_vertices(Object_pointer<Type> &object)
  {
    gl::gen_vertex_arrays(1, &object->render_data.vertex_array_object);
    gl::bind_vertex_array(object->render_data.vertex_array_object);

    gl::gen_buffers(1, &object->render_data.vertex_buffer_object);
    gl::bind_buffer(GL_ARRAY_BUFFER, object->render_data.vertex_buffer_object);
    gl::buffer_data(GL_ARRAY_BUFFER, (gl::Sizei)default_quad_vertices.size() * (gl::Sizei)sizeof(gl::Float),
                    default_quad_vertices.data(), GL_STATIC_DRAW);
    gl::vertex_attrib_pointer(0, 3, GL_FLOAT, false, sizeof(gl::Float) * 8, (gl::Void *)0);
    gl::enable_vertex_attrib_array(0); // Vertex position

    gl::gen_buffers(1, &object->render_data.index_buffer_object);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, object->render_data.index_buffer_object);
    gl::buffer_data(GL_ELEMENT_ARRAY_BUFFER, (gl::Sizei)default_quad_indices.size() * (gl::Sizei)sizeof(gl::Float),
                    default_quad_indices.data(), GL_STATIC_DRAW);
    gl::vertex_attrib_pointer(1, 3, GL_FLOAT, false, sizeof(gl::Float) * 8, (gl::Void *)(sizeof(gl::Float) * 3));
    gl::enable_vertex_attrib_array(1); // Vertex color

    gl::gen_textures(1, &object->render_data.texture_object);
    gl::bind_texture(GL_TEXTURE_2D, object->render_data.texture_object);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::vertex_attrib_pointer(2, 2, GL_FLOAT, false, sizeof(gl::Float) * 8, (gl::Void *)(sizeof(gl::Float) * 6));
    gl::enable_vertex_attrib_array(2); // Vertex texture coordinates

    cleanup_vertices();
  }

  template <typename Type> void Render::pre_draw_vertices(Object_pointer<Type> &object)
  {
    gl::use_program(object->render_data.shader_object);

    camera.update_projection_matrix();
    glm::Mat4 projection = camera.matrix_data.projection;
    gl::Int uniform_projection_matrix_location =
      get_uniform_location_by_name(object->render_data.shader_object, "uniform_projection_matrix");
    gl::uniform_matrix_4fv(uniform_projection_matrix_location, 1, false, glm::value_ptr(projection));

    camera.update_view_matrix();
    glm::Mat4 view = camera.matrix_data.view;
    gl::Int uniform_view_matrix_location =
      get_uniform_location_by_name(object->render_data.shader_object, "uniform_view_matrix");
    gl::uniform_matrix_4fv(uniform_view_matrix_location, 1, false, glm::value_ptr(view));

    glm::Mat4 model = glm::Mat4(1.0f);
    model = glm::translate(model, glm::Vec3(object->transform_data.translation.x, object->transform_data.translation.y,
                                            object->transform_data.translation.z));
    model = glm::rotate(model, glm::radians(object->transform_data.rotation.x), glm::Vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->transform_data.rotation.y), glm::Vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->transform_data.rotation.z), glm::Vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(
      model, glm::Vec3(object->transform_data.scale.x, object->transform_data.scale.y, object->transform_data.scale.z));
    gl::Int uniform_model_matrix_location =
      get_uniform_location_by_name(object->render_data.shader_object, "uniform_model_matrix");
    gl::uniform_matrix_4fv(uniform_model_matrix_location, 1, false, glm::value_ptr(model));
  }

  template <typename Type> void Render::draw_vertices(Object_pointer<Type> &object)
  {
    gl::bind_vertex_array(object->render_data.vertex_array_object);
    gl::use_program(object->render_data.shader_object);
    gl::bind_texture(GL_TEXTURE_2D, object->render_data.texture_object);
    gl::draw_elements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (gl::Void *)0);
  }

  template <typename Type> void Render::cleanup(Object_pointer<Type> &object)
  {
    gl::delete_vertex_arrays(1, &object->render_data.vertex_array_object);
    gl::delete_buffers(1, &object->render_data.vertex_buffer_object);
    gl::delete_buffers(1, &object->render_data.index_buffer_object);
    gl::delete_textures(1, &object->render_data.texture_object);
    gl::delete_program(object->render_data.shader_object);
  }
}
