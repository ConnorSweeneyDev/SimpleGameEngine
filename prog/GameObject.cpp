#include "GameObject.hpp"

GameObjectPtr game_object_ptr; // For calling GameObject functions without referencing a specific object
GameObjectList game_objects;   // For storing all GameObjects

GameObject::GameObject(std::string name) { this->name = name; }

const std::string& GameObject::getName() const { return name; }

void GameObject::setShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    shaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void GameObject::DefineVertices()
{ 
    GameObjectPtr game_object;

    game_object = std::make_shared<GameObject>("Player 1");
    game_object->SpecifyVertices(
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
    game_objects.push_back(game_object);

    game_object = std::make_shared<GameObject>("Player 2");
    game_object->SpecifyVertices(
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
    game_objects.push_back(game_object);    
}
void GameObject::SpecifyVertices(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData)
{
    glGenVertexArrays(1, &vertexArrayObject);
    glBindVertexArray(vertexArrayObject);

    glGenBuffers(1, &vertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0); // Vertex attribute pointer for the vertex position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)0);
    glEnableVertexAttribArray(1); // Vertex attribute pointer for the vertex color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*6, (GLvoid*)(sizeof(GLfloat)*3));

    glGenBuffers(1, &indexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLfloat), indexData.data(), GL_STATIC_DRAW);
}
void GameObject::PreDraw()
{
    glUseProgram(shaderProgram);
    
    glm::mat4 perspective = glm::perspective(
                                             glm::radians(45.0f),                                  // Field of view
                                             (float)window.getWidth() / (float)window.getHeight(), // Aspect ratio
                                             0.1f, 10.0f                                           // Near and far clipping planes
                                            );
    GLint uProjectionMatrixLocation = glGetUniformLocation(shaderProgram, "uProjectionMatrix");
    if (uProjectionMatrixLocation >= 0)
    {
        glUniformMatrix4fv(
                           uProjectionMatrixLocation,
                           1,
                           GL_FALSE,
                           glm::value_ptr(perspective) // Pointer to the data of perspective, &perspective[0][0] also works
                          );
    }
    else
    {
        std::cout << "uProjectionMatrix could not be found!" << std::endl;
    }

    glm::mat4 view = camera.getViewMatrix();
    GLint uViewMatrixLocation = glGetUniformLocation(shaderProgram, "uViewMatrix");
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
                           glm::vec3(translationX, translationY, translationZ)
                          );
    model = glm::rotate(
                        model,
                        glm::radians(rotationX),
                        glm::vec3(1.0f, 0.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(rotationY),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(rotationZ),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                       );
    model = glm::scale(
                       model,
                       glm::vec3(scale)
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(shaderProgram, "uModelMatrix");
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
void GameObject::Draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}

void GameObject::MoveUp(float speed) { translationY += speed * util.getDeltaTime(); }
void GameObject::MoveDown(float speed) { translationY -= speed * util.getDeltaTime(); }
void GameObject::MoveLeft(float speed) { translationX -= speed * util.getDeltaTime(); }
void GameObject::MoveRight(float speed) { translationX += speed * util.getDeltaTime(); }
void GameObject::MoveForward(float speed) { translationZ -= speed * util.getDeltaTime(); }
void GameObject::MoveBackward(float speed) { translationZ += speed * util.getDeltaTime(); }

void GameObject::RotateXPos(float speed) { rotationX += speed * util.getDeltaTime(); }
void GameObject::RotateXNeg(float speed) { rotationX -= speed * util.getDeltaTime(); }
void GameObject::RotateYPos(float speed) { rotationY += speed * util.getDeltaTime(); }
void GameObject::RotateYNeg(float speed) { rotationY -= speed * util.getDeltaTime(); }
void GameObject::RotateZPos(float speed) { rotationZ += speed * util.getDeltaTime(); }
void GameObject::RotateZNeg(float speed) { rotationZ -= speed * util.getDeltaTime(); }

void GameObject::ScaleUp(float speed) { scale += speed * util.getDeltaTime(); }
void GameObject::ScaleDown(float speed) { scale -= speed * util.getDeltaTime(); }

void GameObject::Reset()
{
    translationX = initial[0];
    translationY = initial[1];
    translationZ = initial[2];
    rotationX = initial[3];
    rotationY = initial[4];
    rotationZ = initial[5];
    scale = initial[6];
}

void GameObject::init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scale)
{
    initial.push_back(this->translationX = translationX);
    initial.push_back(this->translationY = translationY);
    initial.push_back(this->translationZ = translationZ);
    initial.push_back(this->rotationX = rotationX);
    initial.push_back(this->rotationY = rotationY);
    initial.push_back(this->rotationZ = rotationZ);
    initial.push_back(this->scale = scale);
}
void GameObject::cleanup()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteProgram(shaderProgram);
}

GameObjectPtr getGameObjectByName(const std::string &name)
{
    for (auto &gameObject : game_objects)
    {
        if (gameObject->getName() == name)
        {
            return gameObject;
        }
    }
    return nullptr;
}
