#include "Render.hpp"

Render render;

void Render::SpecifyObjects()
{ 
    players.push_back(SpecifyObject<Player>("Player 1"));
    players.push_back(SpecifyObject<Player>("Player 2"));

    items.push_back(SpecifyObject<Item>("Floor"));
}
template<typename Type> std::shared_ptr<Type> Render::SpecifyObject(const std::string name)
{
    auto object = std::make_shared<Type>(name);
    SpecifyVertices(object);
    return object;
}
template PlayerPtr Render::SpecifyObject<Player>(std::string name);
template ItemPtr Render::SpecifyObject<Item>(std::string name);

template<typename Type> void Render::AddObject(const std::string name, const std::string vertexShader, const std::string fragmentShader, const std::vector<float> defaultPosition) { }
template<> void Render::AddObject<Item>(const std::string name, const std::string vertexShader, const std::string fragmentShader, const std::vector<float> defaultPosition)
{
    if (system_util.getObjectByName<Item>(name) == nullptr)
    {
        items.push_back(SpecifyObject<Item>(name));
        vertexcleanup();

        auto item = system_util.getObjectByName<Item>(name);
        shader.setShaderProgram(item, vertexShader, fragmentShader);
        item->init(defaultPosition);
    }
}
template<typename Type> void Render::RemoveObject(std::shared_ptr<Type>& object) { }
template<> void Render::RemoveObject<Player>(PlayerPtr& object)
{
    objectcleanup(object);
    players.erase(std::remove_if(players.begin(), players.end(), [&object](const PlayerPtr& player){ return player == object; }), players.end());
}
template<> void Render::RemoveObject<Item>(ItemPtr& object)
{
    objectcleanup(object);
    items.erase(std::remove_if(items.begin(), items.end(), [&object](const ItemPtr& item){ return item == object; }), items.end());
}

template<typename Type> void Render::SpecifyVertices(std::shared_ptr<Type>& object)
{
    glGenVertexArrays(1, &object->vertexArrayObject);
    glBindVertexArray(object->vertexArrayObject);

    glGenBuffers(1, &object->vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, object->vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, defaultQuadVertices.size() * sizeof(GLfloat), defaultQuadVertices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)0);
    glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)(sizeof(GLfloat)*3));

    glGenBuffers(1, &object->indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, object->indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, defaultQuadIndices.size() * sizeof(GLfloat), defaultQuadIndices.data(), GL_STATIC_DRAW);
}
template void Render::SpecifyVertices<Player>(PlayerPtr& object);
template void Render::SpecifyVertices<Item>(ItemPtr& object);
template<typename Type> void Render::PreDraw(std::shared_ptr<Type>& object)
{
    glUseProgram(object->shaderProgram);
    
    glm::mat4 projection = camera.getProjectionMatrix();
    GLint uProjectionMatrixLocation = glGetUniformLocation(object->shaderProgram, "uProjectionMatrix");
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
    GLint uViewMatrixLocation = glGetUniformLocation(object->shaderProgram, "uViewMatrix");
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
                           glm::vec3(object->translationX, object->translationY, object->translationZ)
                          );
    model = glm::rotate(
                        model,
                        glm::radians(object->rotationX),
                        glm::vec3(1.0f, 0.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(object->rotationY),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(object->rotationZ),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                       );
    model = glm::scale(
                       model,
                       glm::vec3(object->scaleX, object->scaleY, object->scaleZ)
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(object->shaderProgram, "uModelMatrix");
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
template void Render::PreDraw<Player>(PlayerPtr& object);
template void Render::PreDraw<Item>(ItemPtr& object);
template<typename Type> void Render::Draw(std::shared_ptr<Type>& object)
{
    glUseProgram(object->shaderProgram);
    glBindVertexArray(object->vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}
template void Render::Draw<Player>(PlayerPtr& object);
template void Render::Draw<Item>(ItemPtr& object);

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
    players.clear();

    for (auto& item : items)
        objectcleanup(item);
    items.clear();
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
    glDeleteVertexArrays(1, &object->vertexArrayObject);
    glDeleteBuffers(1, &object->vertexBufferObject);
    glDeleteBuffers(1, &object->indexBufferObject);
    glDeleteProgram(object->shaderProgram);
}
template void Render::objectcleanup<Player>(PlayerPtr& object);
template void Render::objectcleanup<Item>(ItemPtr& object);
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
