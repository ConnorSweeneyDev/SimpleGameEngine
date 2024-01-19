#include "Render.hpp"

Render render;

void Render::SpecifyObjects()
{ 
    PlayerPtr player;
    SpecifyObject(
                  "Player 1",
                  player, players
                 );
    SpecifyObject(
                  "Player 2",
                  player, players
                 );

    ItemPtr item;
    SpecifyObject(
                  "Floor",
                  item, items
                 );
}
template<typename Type> void Render::SpecifyObject(std::string name, std::shared_ptr<Type>& object, std::vector<std::shared_ptr<Type>>& objectList)
{
    object = std::make_shared<Type>(name);
    SpecifyVertices(object);
    objectList.push_back(object);
}
template void Render::SpecifyObject<Player>(std::string name, std::shared_ptr<Player>& object, std::vector<std::shared_ptr<Player>>& objectList);
template void Render::SpecifyObject<Item>(std::string name, std::shared_ptr<Item>& object, std::vector<std::shared_ptr<Item>>& objectList);

template<typename Type> void Render::SpecifyVertices(std::shared_ptr<Type>& object)
{
    glGenVertexArrays(1, &object->getVertexArrayObject());
    glBindVertexArray(object->getVertexArrayObject());

    glGenBuffers(1, &object->getVertexBufferObject());
    glBindBuffer(GL_ARRAY_BUFFER, object->getVertexBufferObject());
    glBufferData(GL_ARRAY_BUFFER, defaultQuadVertices.size() * sizeof(GLfloat), defaultQuadVertices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)0);
    glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)(sizeof(GLfloat)*3));

    glGenBuffers(1, &object->getIndexBufferObject());
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->getIndexBufferObject());
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, defaultQuadIndices.size() * sizeof(GLfloat), defaultQuadIndices.data(), GL_STATIC_DRAW);
}
template void Render::SpecifyVertices<Player>(std::shared_ptr<Player>& object);
template void Render::SpecifyVertices<Item>(std::shared_ptr<Item>& object);
template<typename Type> void Render::PreDraw(std::shared_ptr<Type>& object)
{
    glUseProgram(object->getShaderProgram());
    
    glm::mat4 projection = camera.getProjectionMatrix();
    GLint uProjectionMatrixLocation = glGetUniformLocation(object->getShaderProgram(), "uProjectionMatrix");
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
    GLint uViewMatrixLocation = glGetUniformLocation(object->getShaderProgram(), "uViewMatrix");
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

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(
                           model,
                           glm::vec3(object->getTranslationX(), object->getTranslationY(), object->getTranslationZ())
                          );
    model = glm::rotate(
                        model,
                        glm::radians(object->getRotationX()),
                        glm::vec3(1.0f, 0.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(object->getRotationY()),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(object->getRotationZ()),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                       );
    model = glm::scale(
                       model,
                       glm::vec3(object->getScaleX(), object->getScaleY(), object->getScaleZ())
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(object->getShaderProgram(), "uModelMatrix");
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
template void Render::PreDraw<Player>(std::shared_ptr<Player>& object);
template void Render::PreDraw<Item>(std::shared_ptr<Item>& object);
template<typename Type> void Render::Draw(std::shared_ptr<Type>& object)
{
    glUseProgram(object->getShaderProgram());
    glBindVertexArray(object->getVertexArrayObject());
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}
template void Render::Draw<Player>(std::shared_ptr<Player>& object);
template void Render::Draw<Item>(std::shared_ptr<Item>& object);

void Render::PreDrawObjects()
{
    for (auto& player : players)
        PreDraw(player);

    for (auto& item : items)
        PreDraw(item);
}
void Render::DrawObjects()
{
    for (auto& player : players)
        Draw(player);

    for (auto& item : items)
        Draw(item);
}
void Render::CleanupObjects()
{
    for (auto& player : players)
        objectcleanup(player);

    for (auto& item : items)
        objectcleanup(item);
}

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

template<typename Type> void Render::objectcleanup(std::shared_ptr<Type>& object)
{
    glDeleteVertexArrays(1, &object->getVertexArrayObject());
    glDeleteBuffers(1, &object->getVertexBufferObject());
    glDeleteBuffers(1, &object->getIndexBufferObject());
    glDeleteProgram(object->getShaderProgram());
}
template void Render::objectcleanup<Player>(std::shared_ptr<Player>& object);
template void Render::objectcleanup<Item>(std::shared_ptr<Item>& object);
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
