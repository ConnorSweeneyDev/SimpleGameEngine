#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "rename.hpp"
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

#include "camera.hpp"
#include "item.hpp"
#include "player.hpp"
#include "render.hpp"
#include "shader.hpp"
#include "texture.hpp"

namespace cse::object
{
  template <typename Type>
  const std::shared_ptr<Type> Render::get_by_name(const std::string name) const
  {
    if constexpr (std::is_same<Type, Player>::value)
    {
      for (auto &player : players)
        if (player->name == name) return player;
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
      for (auto &item : items)
        if (item->name == name) return item;
    }
    return nullptr;
  }

  template <typename Type> const std::shared_ptr<Type> Render::specify(const std::string name)
  {
    auto object = std::make_shared<Type>(name);
    specify_vertices(object);

    return object;
  }

  // specify_dynamic only exists for Item, not player due to player's init
  // function taking specific parameters - will be changed to a different Type
  // later (Might not need to be a template function)
  template <typename Type>
  const std::shared_ptr<Type>
  Render::specify_dynamic(const std::string name, const std::string texture_path,
                          const std::string vertex_shader, const std::string fragment_shader,
                          const std::vector<float> default_geometry)
  {
    if constexpr (std::is_same<Type, Item>::value)
    {
      auto object = specify<Type>(name);
      specify_vertices(object);
      object->texture_path = texture_path;
      texture.load(object);
      shader.set_program(object, vertex_shader, fragment_shader);
      object->init(default_geometry);

      return object;
    }
  }

  template <typename Type> void Render::add(const std::string name)
  {
    if constexpr (std::is_same<Type, Player>::value)
      players.push_back(specify<Player>(name));

    else if constexpr (std::is_same<Type, Item>::value)
      items.push_back(specify<Item>(name));
  }

  // add_dynamic only exists for Item, not player due to player's init function
  // taking specific parameters - will be changed to a different Type later
  // (Might not need to be a template function)
  template <typename Type>
  void Render::add_dynamic(const std::string name, const std::string texture_path,
                           const std::string vertex_shader, const std::string fragment_shader,
                           const std::vector<float> default_geometry)
  {
    if constexpr (std::is_same<Type, Item>::value)
      if (get_by_name<Item>(name) == nullptr)
        items.push_back(specify_dynamic<Item>(name, texture_path, vertex_shader, fragment_shader,
                                              default_geometry));
  }

  template <typename Type> void Render::remove(std::shared_ptr<Type> &object)
  {
    if constexpr (std::is_same<Type, Player>::value)
    {
      players.erase(std::remove_if(players.begin(), players.end(),
                                   [&object](const Player_ptr &player)
                                   { return player == object; }),
                    players.end());
      cleanup(object);
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
      items.erase(std::remove_if(items.begin(), items.end(),
                                 [&object](const Item_ptr &item) { return item == object; }),
                  items.end());
      cleanup(object);
    }
  }

  template <typename Type> void Render::specify_vertices(std::shared_ptr<Type> &object)
  {
    gl::gen_vertex_arrays(1, &object->vertex_array_object);
    gl::bind_vertex_array(object->vertex_array_object);

    gl::gen_buffers(1, &object->vertex_buffer_object);
    gl::bind_buffer(GL_ARRAY_BUFFER, object->vertex_buffer_object);
    gl::buffer_data(GL_ARRAY_BUFFER,
                    (gl::Size_i)default_quad_vertices.size() * (gl::Size_i)sizeof(gl::Float),
                    default_quad_vertices.data(), GL_STATIC_DRAW);
    gl::vertex_attrib_pointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(gl::Float) * 8, (gl::Void *)0);
    gl::enable_vertex_attrib_array(0); // Vertex position

    gl::gen_buffers(1, &object->index_buffer_object);
    gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, object->index_buffer_object);
    gl::buffer_data(GL_ELEMENT_ARRAY_BUFFER,
                    (gl::Size_i)default_quad_indices.size() * (gl::Size_i)sizeof(gl::Float),
                    default_quad_indices.data(), GL_STATIC_DRAW);
    gl::vertex_attrib_pointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(gl::Float) * 8,
                              (gl::Void *)(sizeof(gl::Float) * 3));
    gl::enable_vertex_attrib_array(1); // Vertex color

    gl::gen_textures(1, &object->texture_object);
    gl::bind_texture(GL_TEXTURE_2D, object->texture_object);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl::tex_parameter_i(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl::vertex_attrib_pointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(gl::Float) * 8,
                              (gl::Void *)(sizeof(gl::Float) * 6));
    gl::enable_vertex_attrib_array(2); // Vertex texture coordinates

    vertex_cleanup();
  }

  template <typename Type> void Render::pre_draw_vertices(std::shared_ptr<Type> &object)
  {
    gl::use_program(object->shader_program);

    camera.update_projection_matrix();
    glm::Mat4 projection = camera.projection_matrix;
    gl::Int uniform_projection_matrix_location =
      gl::get_uniform_location(object->shader_program, "uniform_projection_matrix");
    if (uniform_projection_matrix_location <= -1)
      std::cout << "uniform_projection_matrix could not be found!" << std::endl;
    gl::uniform_matrix_4fv(uniform_projection_matrix_location, 1, GL_FALSE,
                           glm::value_ptr(projection));

    camera.update_view_matrix();
    glm::Mat4 view = camera.view_matrix;
    gl::Int uniform_view_matrix_location =
      gl::get_uniform_location(object->shader_program, "uniform_view_matrix");
    if (uniform_view_matrix_location <= -1)
      std::cout << "uniform_view_matrix could not be found!" << std::endl;
    gl::uniform_matrix_4fv(uniform_view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));

    glm::Mat4 model = glm::Mat4(1.0f);
    model = glm::translate(
      model, glm::Vec3(object->translation_x, object->translation_y, object->translation_z));
    model = glm::rotate(model, glm::radians(object->rotation_x), glm::Vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->rotation_y), glm::Vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->rotation_z), glm::Vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::Vec3(object->scale_x, object->scale_y, object->scale_z));
    gl::Int uniform_model_matrix_location =
      gl::get_uniform_location(object->shader_program, "uniform_model_matrix");
    if (uniform_model_matrix_location <= -1)
      std::cout << "uniform_model_matrix could not be found!" << std::endl;
    gl::uniform_matrix_4fv(uniform_model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));
  }

  template <typename Type> void Render::draw_vertices(std::shared_ptr<Type> &object)
  {
    gl::bind_vertex_array(object->vertex_array_object);
    gl::use_program(object->shader_program);
    gl::bind_texture(GL_TEXTURE_2D, object->texture_object);
    gl::draw_elements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (gl::Void *)0);
  }

  template <typename Type> void Render::cleanup(std::shared_ptr<Type> &object)
  {
    gl::delete_vertex_arrays(1, &object->vertex_array_object);
    gl::delete_buffers(1, &object->vertex_buffer_object);
    gl::delete_buffers(1, &object->index_buffer_object);
    gl::delete_textures(1, &object->texture_object);
    gl::delete_program(object->shader_program);
  }
}
