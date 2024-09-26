#pragma once

#include <string>
#include <vector>

#include "rename.hpp"

#include "property.hpp"

namespace cse::object
{
  class Render
  {
  public:
    enum struct Call_action
    {
      NONE,
      REMOVE
    };
    template <typename Type = void, typename Callable>
    void call_for_all(Callable callable, const Call_action action = Call_action::NONE);
    template <typename Type> const Object_pointer<Type> get_by_name(const std::string &name);

    void initialize();
    template <typename Type>
    void initialize_dynamic(const std::string &name, const Texture_data &texture_data,
                            const Shader_data &shader_data, const Transform_data &transform_data);
    template <typename Type> void remove(Object_pointer<Type> &object);

    void remove_all();
    void update_all();

  private:
    template <typename Type> const Object_pointer<Type> create(const std::string &name);
    template <typename Type> void add(const std::string &name);
    template <typename Type>
    const Object_pointer<Type>
    add_dynamic(const std::string &name, const Texture_data &texture_data,
                const Shader_data &shader_data, const Transform_data &transform_data);

    gl::Int get_uniform_location_by_name(const gl::Uint shader_object, const std::string &name);
    template <typename Type> void specify_vertices(Object_pointer<Type> &object);
    template <typename Type> void pre_draw_vertices(Object_pointer<Type> &object);
    template <typename Type> void draw_vertices(Object_pointer<Type> &object);

    void initialize_pre_draw();
    void cleanup_vertices();
    void cleanup_draw();
    template <typename Type> void cleanup(Object_pointer<Type> &object);

    const std::vector<gl::Float> default_quad_vertices = {
      -0.5f, -0.5f, 0.0f, // Bottom left vertex position
      1.0f,  0.0f,  0.0f, // Bottom left vertex color
      0.0f,  0.0f,        // Bottom left vertex texture coordinates
      0.5f,  -0.5f, 0.0f, // Bottom right vertex position
      0.0f,  1.0f,  0.0f, // Bottom right vertex color
      1.0f,  0.0f,        // Bottom right vertex texture coordinates
      -0.5f, 0.5f,  0.0f, // Top left vertex position
      0.0f,  0.0f,  1.0f, // Top left vertex color
      0.0f,  1.0f,        // Top left vertex texture coordinates
      0.5f,  0.5f,  0.0f, // Top right vertex position
      1.0f,  0.0f,  0.0f, // Top right vertex color
      1.0f,  1.0f         // Top right vertex texture coordinates
    };
    const std::vector<gl::Uint> default_quad_indices = {
      0, 1, 2, // Triangle 1
      2, 1, 3  // Triangle 2
    };
  };

  inline Render render = {};
}

#include "render.inl"
