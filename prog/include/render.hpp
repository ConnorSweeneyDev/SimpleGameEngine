#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>

namespace cse
{
    class Render
    {
        public:
            template <typename Type> std::shared_ptr<Type> get_object_by_name(const std::string& name) const;

            void specify_objects();
            template <typename Type> std::shared_ptr<Type> specify_object(const std::string name);
            template <typename Type> std::shared_ptr<Type> specify_dynamic_object(const std::string name, const std::string vertex_shader, const std::string fragment_shader, const std::vector<float> default_geometry);

            template <typename Type> void add_object(const std::string name);
            template <typename Type> void add_dynamic_object(const std::string name, const std::string vertex_shader, const std::string fragment_shader, const std::vector<float> default_geometry);
            template <typename Type> void remove_object(std::shared_ptr<Type>& object);
            template <typename Type> void specify_vertices(std::shared_ptr<Type>& object);

            template <typename Type> void pre_draw(std::shared_ptr<Type>& object); 
            template <typename Type> void draw(std::shared_ptr<Type>& object);
            void pre_draw_objects();
            void draw_objects();
            void cleanup_objects();
            void update();

            void pre_draw_init();
            template <typename Type> void object_cleanup(std::shared_ptr<Type>& object);
            void vertex_cleanup();
            void draw_cleanup();
        
        private:
            std::vector<GLfloat> default_quad_vertices =
            {
                // Vertex 0
                -0.5f, -0.5f, 0.0f, // Bottom left vertex position
                1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                0.0f, 0.0f,         // Bottom left vertex texture coordinates
                // Vertex 1
                0.5f, -0.5f, 0.0f,  // Bottom right vertex position
                0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                1.0f, 0.0f,         // Bottom right vertex texture coordinates
                // Vertex 2
                -0.5f, 0.5f, 0.0f,  // Top left vertex position
                0.0f, 0.0f, 1.0f,   // Top left vertex color
                0.0f, 1.0f,         // Top left vertex texture coordinates
                // Vertex 3
                0.5f, 0.5f, 0.0f,   // Top right vertex position
                1.0f, 0.0f, 0.0f,   // Top right vertex color
                1.0f, 1.0f          // Top right vertex texture coordinates
            };
            std::vector<GLuint> default_quad_indices =
            {
                0, 1, 2, // Triangle 1
                2, 1, 3  // Triangle 2
            };
    };
    extern Render render;
}

#include "render.tpl.hpp"
