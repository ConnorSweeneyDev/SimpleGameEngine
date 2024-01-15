#include "Render.hpp"

Render render;

template <typename Type> void Render::setShaderProgram(std::shared_ptr<Type>& object, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    object->getShaderProgram() = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}
template void Render::setShaderProgram<Player>(std::shared_ptr<Player>& object, std::string vertexShaderPath, std::string fragmentShaderPath);
template void Render::setShaderProgram<Item>(std::shared_ptr<Item>& object, std::string vertexShaderPath, std::string fragmentShaderPath);

void Render::DefineVertices()
{ 
    PlayerPtr player;
    player = std::make_shared<Player>("Player 1");
    SpecifyVertices(
                    player,
                    {
                        // Vertex 0
                        -0.4f, -0.5f, 0.0f, // Bottom left vertex position
                        1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                        // Vertex 1
                        0.4f, -0.5f, 0.0f,  // Bottom right vertex position
                        0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                        // Vertex 2
                        -0.4f, 0.5f, 0.0f,  // Top left vertex position
                        0.0f, 0.0f, 1.0f,   // Top left vertex color
                        // Vertex 3
                        0.4f, 0.5f, 0.0f,   // Top right vertex position
                        1.0f, 0.0f, 0.0f    // Top right vertex color
                    },
                    {
                        0, 1, 2, // first triangle
                        3, 2, 1  // second triangle
                    }
                   );
    players.push_back(player);
    player = std::make_shared<Player>("Player 2");
    SpecifyVertices(
                    player,
                    {
                        // Vertex 0
                        -0.4f, -0.5f, 0.0f, // Bottom left vertex position
                        1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                        // Vertex 1
                        0.4f, -0.5f, 0.0f,  // Bottom right vertex position
                        0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                        // Vertex 2
                        -0.4f, 0.5f, 0.0f,  // Top left vertex position
                        0.0f, 0.0f, 1.0f,   // Top left vertex color
                        // Vertex 3
                        0.4f, 0.5f, 0.0f,   // Top right vertex position
                        1.0f, 0.0f, 0.0f    // Top right vertex color
                    },
                    {
                        0, 1, 2, // first triangle
                        3, 2, 1  // second triangle
                    }
                   );
    players.push_back(player);    

    ItemPtr item;
    item = std::make_shared<Item>("Floor");
    SpecifyVertices(
                    item,
                    {
                        // Vertex 0
                        -0.4f, -0.5f, 0.0f, // Bottom left vertex position
                        1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                        // Vertex 1
                        0.4f, -0.5f, 0.0f,  // Bottom right vertex position
                        0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                        // Vertex 2
                        -0.4f, 0.5f, 0.0f,  // Top left vertex position
                        0.0f, 0.0f, 1.0f,   // Top left vertex color
                        // Vertex 3
                        0.4f, 0.5f, 0.0f,   // Top right vertex position
                        1.0f, 0.0f, 0.0f    // Top right vertex color
                    },
                    {
                        0, 1, 2, // first triangle
                        3, 2, 1  // second triangle
                    }
                   );
    items.push_back(item);
}

template <typename Type> void Render::SpecifyVertices(std::shared_ptr<Type>& player, std::vector<GLfloat> vertexData, std::vector<GLuint>indexData)
{
    glGenVertexArrays(1, &player->getVertexArrayObject());
    glBindVertexArray(player->getVertexArrayObject());

    glGenBuffers(1, &player->getVertexBufferObject());
    glBindBuffer(GL_ARRAY_BUFFER, player->getVertexBufferObject());
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)0);
    glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)(sizeof(GLfloat)*3));

    glGenBuffers(1, &player->getIndexBufferObject());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, player->getIndexBufferObject());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLfloat), indexData.data(), GL_STATIC_DRAW);
}
template void Render::SpecifyVertices<Player>(std::shared_ptr<Player>& player, std::vector<GLfloat> vertexData, std::vector<GLuint>indexData);
template void Render::SpecifyVertices<Item>(std::shared_ptr<Item>& player, std::vector<GLfloat> vertexData, std::vector<GLuint>indexData);

template <typename Type> void Render::PreDraw(std::shared_ptr<Type>& player)
{
    glUseProgram(player->getShaderProgram());
    
    glm::mat4 projection = camera.getProjectionMatrix();
    GLint uProjectionMatrixLocation = glGetUniformLocation(player->getShaderProgram(), "uProjectionMatrix");
    if (uProjectionMatrixLocation >= 0)
    {
        glUniformMatrix4fv(
                           uProjectionMatrixLocation,
                           1,
                           GL_FALSE,
                           glm::value_ptr(projection) // Pointer to the data of projection, &projection[0][0] also works
                          );
    }
    else
    {
        std::cout << "uProjectionMatrix could not be found!" << std::endl;
    }

    glm::mat4 view = camera.getViewMatrix();
    GLint uViewMatrixLocation = glGetUniformLocation(player->getShaderProgram(), "uViewMatrix");
    if (uViewMatrixLocation >= 0)
    {
        glUniformMatrix4fv(
                           uViewMatrixLocation,
                           1,
                           GL_FALSE,
                           glm::value_ptr(view) // Pointer to the data of view, &view[0][0] also works
                          );
    }
    else
    {
        std::cout << "uViewMatrix could not be found!" << std::endl;
    }

    glm::mat4 model = glm::mat4(1.0f); // Initialize the model's identity matrix
    model = glm::translate(
                           model,
                           glm::vec3(player->getTranslationX(), player->getTranslationY(), player->getTranslationZ())
                          );
    model = glm::rotate(
                        model,
                        glm::radians(player->getRotationX()),
                        glm::vec3(1.0f, 0.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(player->getRotationY()),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(player->getRotationZ()),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                       );
    model = glm::scale(
                       model,
                       glm::vec3(player->getScaleX(), player->getScaleY(), player->getScaleZ())
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(player->getShaderProgram(), "uModelMatrix");
    if (uModelMatrixLocation >= 0)
    {
        glUniformMatrix4fv(
                           uModelMatrixLocation,
                           1,
                           GL_FALSE,
                           glm::value_ptr(model) // Pointer to the data of model, &model[0][0] also works
                          );
    } 
    else
    {
        std::cout << "uModelMatrix could not be found!" << std::endl;
    }
}
template void Render::PreDraw<Player>(std::shared_ptr<Player>& player);
template void Render::PreDraw<Item>(std::shared_ptr<Item>& player);

template <typename Type> void Render::Draw(std::shared_ptr<Type>& player)
{
    glUseProgram(player->getShaderProgram());
    glBindVertexArray(player->getVertexArrayObject());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}
template void Render::Draw<Player>(std::shared_ptr<Player>& player);
template void Render::Draw<Item>(std::shared_ptr<Item>& player);

void Render::predrawinit()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(
               0,
               0,
               window.getWidth(),
               window.getHeight()
              );
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

template <typename Type> void Render::objectcleanup(std::shared_ptr<Type>& player)
{
    glDeleteVertexArrays(1, &player->getVertexArrayObject());
    glDeleteBuffers(1, &player->getVertexBufferObject());
    glDeleteBuffers(1, &player->getIndexBufferObject());
    glDeleteProgram(player->getShaderProgram());
}
template void Render::objectcleanup<Player>(std::shared_ptr<Player>& player);
template void Render::objectcleanup<Item>(std::shared_ptr<Item>& player);

void Render::vertexcleanup()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Render::drawcleanup()
{
    glBindVertexArray(0);
    glUseProgram(0);
}
