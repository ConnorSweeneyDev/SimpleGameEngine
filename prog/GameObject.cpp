#include "GameObject.hpp"

GameObject player1;
GameObject player2;

void GameObject::specifyVertices(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData)
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

void GameObject::setShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    shaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void GameObject::preDraw()
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

void GameObject::draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}

void GameObject::moveUp(float speed) { translationY += speed; }
void GameObject::moveDown(float speed) { translationY -= speed; }
void GameObject::moveLeft(float speed) { translationX -= speed; }
void GameObject::moveRight(float speed) { translationX += speed; }
void GameObject::moveForward(float speed) { translationZ -= speed; }
void GameObject::moveBackward(float speed) { translationZ += speed; }

void GameObject::rotateXPos(float speed) { rotationX += speed; }
void GameObject::rotateXNeg(float speed) { rotationX -= speed; }
void GameObject::rotateYPos(float speed) { rotationY += speed; }
void GameObject::rotateYNeg(float speed) { rotationY -= speed; }
void GameObject::rotateZPos(float speed) { rotationZ += speed; }
void GameObject::rotateZNeg(float speed) { rotationZ -= speed; }

void GameObject::scaleUp(float speed) { scale += speed; }
void GameObject::scaleDown(float speed) { scale -= speed; }

void GameObject::reset()
{
    translationX = 0.0f;
    translationY = 0.0f;
    translationZ = 0.0f;
    rotationX = 0.0f;
    rotationY = 0.0f;
    rotationZ = 0.0f;
    scale = 1.0f;
}

void GameObject::init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scale)
{
    this->translationX = translationX;
    this->translationY = translationY;
    this->translationZ = translationZ;
    this->rotationX = rotationX;
    this->rotationY = rotationY;
    this->rotationZ = rotationZ;
    this->scale = scale;
}

void GameObject::cleanup()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteProgram(shaderProgram);
}
