#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "glm/gtc/type_ptr.hpp"

#include "render.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "item.hpp"

namespace cse::object
{
    template <typename Type> std::shared_ptr<Type> Render::get_by_name(const std::string& name) const
    {
        if constexpr (std::is_same<Type, Player>::value)
        {
            for (auto &player : players)
                if (player->name == name)
                    return player;
        }
        else if constexpr (std::is_same<Type, Item>::value)
        {
            for (auto &item : items)
                if (item->name == name)
                    return item;
        }
        return nullptr;
    }

    template <typename Type> std::shared_ptr<Type> Render::specify(const std::string name)
    {
        auto object = std::make_shared<Type>(name);
        specify_vertices(object);

        return object;
    }

    // specify_dynamic only exists for Item, not player due to player's init function taking specific parameters - will be changed to a different Type later
    // (Might not need to be a template function)
    template <typename Type> std::shared_ptr<Type> Render::specify_dynamic(const std::string name, const std::string texture_path, const std::string vertex_shader, const std::string fragment_shader, const std::vector<float> default_geometry)
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

    // add_dynamic only exists for Item, not player due to player's init function taking specific parameters - will be changed to a different Type later
    // (Might not need to be a template function)
    template <typename Type> void Render::add_dynamic(const std::string name, const std::string texture_path, const std::string vertex_shader, const std::string fragment_shader, const std::vector<float> default_geometry)
    {
        if constexpr (std::is_same<Type, Item>::value)
        {
            if (get_by_name<Item>(name) == nullptr)
            {
                items.push_back(specify_dynamic<Item>(name, texture_path, vertex_shader, fragment_shader, default_geometry));
                vertex_cleanup();
            }
        }
    }

    template <typename Type> void Render::remove(std::shared_ptr<Type>& object)
    {
        if constexpr (std::is_same<Type, Player>::value)
        {
            players.erase(std::remove_if(players.begin(), players.end(), [&object](const Player_ptr& player){ return player == object; }), players.end());
            cleanup(object);
        }
        else if constexpr (std::is_same<Type, Item>::value)
        {
            items.erase(std::remove_if(items.begin(), items.end(), [&object](const Item_ptr& item){ return item == object; }), items.end());
            cleanup(object);
        }
    }

    template <typename Type> void Render::specify_vertices(std::shared_ptr<Type>& object)
    {
        glGenVertexArrays(1, &object->vertex_array_object);
        glBindVertexArray(object->vertex_array_object);

        glGenBuffers(1, &object->vertex_buffer_object);
        glBindBuffer(GL_ARRAY_BUFFER, object->vertex_buffer_object);
        glBufferData(GL_ARRAY_BUFFER, default_quad_vertices.size() * sizeof(GLfloat), default_quad_vertices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)0);
        glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position

        glGenBuffers(1, &object->index_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->index_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, default_quad_indices.size() * sizeof(GLfloat), default_quad_indices.data(), GL_STATIC_DRAW);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(sizeof(GLfloat)*3));
        glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color

        glGenTextures(1, &object->texture_object);
        glBindTexture(GL_TEXTURE_2D, object->texture_object);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(sizeof(GLfloat)*6));
        glEnableVertexAttribArray(2); // Vertex attribute pointer for the vertex texture coordinates

        vertex_cleanup();
    }

    template <typename Type> void Render::pre_draw_vertices(std::shared_ptr<Type>& object)
    {
        glUseProgram(object->shader_program);

        camera.update_projection_matrix();
        glm::mat4 projection = camera.projection_matrix;
        GLint u_projection_matrix_location = glGetUniformLocation(object->shader_program, "u_projection_matrix");
        if (u_projection_matrix_location <= -1)
            std::cout << "u_projection_matrix could not be found!" << std::endl;
        glUniformMatrix4fv(u_projection_matrix_location, 1, GL_FALSE, glm::value_ptr(projection));

        camera.update_view_matrix();
        glm::mat4 view = camera.view_matrix;
        GLint u_view_matrix_location = glGetUniformLocation(object->shader_program, "u_view_matrix");
        if (u_view_matrix_location <= -1)
            std::cout << "u_view_matrix could not be found!" << std::endl;
        glUniformMatrix4fv(u_view_matrix_location, 1, GL_FALSE, glm::value_ptr(view));

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(object->translation_x, object->translation_y, object->translation_z));
        model = glm::rotate(model, glm::radians(object->rotation_x), glm::vec3(1.0f, 0.0f, 0.0f));
        model = glm::rotate(model, glm::radians(object->rotation_y), glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::rotate(model, glm::radians(object->rotation_z), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, glm::vec3(object->scale_x, object->scale_y, object->scale_z));
        GLint u_model_matrix_location = glGetUniformLocation(object->shader_program, "u_model_matrix");
        if (u_model_matrix_location <= -1)
            std::cout << "u_model_matrix could not be found!" << std::endl;
        glUniformMatrix4fv(u_model_matrix_location, 1, GL_FALSE, glm::value_ptr(model));
    }

    template <typename Type> void Render::draw_vertices(std::shared_ptr<Type>& object)
    {
        glBindVertexArray(object->vertex_array_object);
        glUseProgram(object->shader_program);
        glBindTexture(GL_TEXTURE_2D, object->texture_object);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
    }

    template <typename Type> void Render::cleanup(std::shared_ptr<Type>& object)
    {
        glDeleteVertexArrays(1, &object->vertex_array_object);
        glDeleteBuffers(1, &object->vertex_buffer_object);
        glDeleteBuffers(1, &object->index_buffer_object);
        glDeleteTextures(1, &object->texture_object);
        glDeleteProgram(object->shader_program);
    }
}
