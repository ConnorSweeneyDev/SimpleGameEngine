#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>

#include "glm/gtc/type_ptr.hpp"

#include "render.hpp"
#include "system_util.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "camera.hpp"
#include "item.hpp"
#include "player.hpp"

template<typename Type> std::shared_ptr<Type> Render::SpecifyObject(const std::string name)
{
    auto object = std::make_shared<Type>(name);
    SpecifyVertices(object);
    return object;
}

// AddObject only exists for Item, not player due to player's init function taking specific parameters - will be changed to a different Type later
// (Might not need to be a template function)
template<typename Type> void Render::AddObject(const std::string name, const std::string vertexShader, const std::string fragmentShader, const std::vector<float> defaultGeometry)
{
    if constexpr (std::is_same<Type, Item>::value)
    {
        if (system_util.getObjectByName<Item>(name) == nullptr)
        {
            items.push_back(SpecifyObject<Item>(name));
            vertexcleanup();

            auto item = system_util.getObjectByName<Item>(name);
            shader.setShaderProgram(item, vertexShader, fragmentShader);
            item->init(defaultGeometry);
        }
    }
}

template<typename Type> void Render::RemoveObject(std::shared_ptr<Type>& object)
{
    if constexpr (std::is_same<Type, Player>::value)
    {
        players.erase(std::remove_if(players.begin(), players.end(), [&object](const PlayerPtr& player){ return player == object; }), players.end());
        objectcleanup(object);
    }
    else if constexpr (std::is_same<Type, Item>::value)
    {
        items.erase(std::remove_if(items.begin(), items.end(), [&object](const ItemPtr& item){ return item == object; }), items.end());
        objectcleanup(object);
    }
}

template<typename Type> void Render::SpecifyVertices(std::shared_ptr<Type>& object)
{
    glGenVertexArrays(1, &object->vertexArrayObject);
    glBindVertexArray(object->vertexArrayObject);

    glGenBuffers(1, &object->vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, object->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, defaultQuadVertices.size() * sizeof(GLfloat), defaultQuadVertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)0);
    glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position

    glGenBuffers(1, &object->indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, defaultQuadIndices.size() * sizeof(GLfloat), defaultQuadIndices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(sizeof(GLfloat)*3));
    glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color

    glGenTextures(1, &object->textureObject);
    glBindTexture(GL_TEXTURE_2D, object->textureObject);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    texture.AssignTextureToObject(object);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*8, (GLvoid*)(sizeof(GLfloat)*6));
    glEnableVertexAttribArray(2); // Vertex attribute pointer for the vertex texture coordinates
}

template<typename Type> void Render::PreDraw(std::shared_ptr<Type>& object)
{
    glUseProgram(object->shaderProgram);

    camera.UpdateProjectionMatrix();
    glm::mat4 projection = camera.getProjectionMatrix();
    GLint uProjectionMatrixLocation = glGetUniformLocation(object->shaderProgram, "uProjectionMatrix");
    if (uProjectionMatrixLocation <= -1)
        std::cout << "uProjectionMatrix could not be found!" << std::endl;
    glUniformMatrix4fv(uProjectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(projection));

    camera.UpdateViewMatrix();
    glm::mat4 view = camera.getViewMatrix();
    GLint uViewMatrixLocation = glGetUniformLocation(object->shaderProgram, "uViewMatrix");
    if (uViewMatrixLocation <= -1)
        std::cout << "uViewMatrix could not be found!" << std::endl;
    glUniformMatrix4fv(uViewMatrixLocation, 1, GL_FALSE, glm::value_ptr(view));

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(object->translationX, object->translationY, object->translationZ));
    model = glm::rotate(model, glm::radians(object->rotationX), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->rotationY), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, glm::radians(object->rotationZ), glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, glm::vec3(object->scaleX, object->scaleY, object->scaleZ));
    GLint uModelMatrixLocation = glGetUniformLocation(object->shaderProgram, "uModelMatrix");
    if (uModelMatrixLocation <= -1)
        std::cout << "uModelMatrix could not be found!" << std::endl;
    glUniformMatrix4fv(uModelMatrixLocation, 1, GL_FALSE, glm::value_ptr(model));
}

template<typename Type> void Render::Draw(std::shared_ptr<Type>& object)
{
    glBindVertexArray(object->vertexArrayObject);
    glUseProgram(object->shaderProgram);
    glBindTexture(GL_TEXTURE_2D, object->textureObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}

template<typename Type> void Render::objectcleanup(std::shared_ptr<Type>& object)
{
    glDeleteVertexArrays(1, &object->vertexArrayObject);
    glDeleteBuffers(1, &object->vertexBufferObject);
    glDeleteBuffers(1, &object->indexBufferObject);
    glDeleteTextures(1, &object->textureObject);
    glDeleteProgram(object->shaderProgram);
}
