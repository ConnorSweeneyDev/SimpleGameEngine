#include "Player.hpp"

PlayerList players;

Player::Player(std::string name) { this->name = name; }

const std::string& Player::getName() const { return name; }

void Player::setShaderProgram(std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    shaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}
void Player::SpecifyVertices(std::vector<GLfloat> vertexData, std::vector<GLuint> indexData)
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
void Player::PreDraw()
{
    glUseProgram(shaderProgram);
    
    glm::mat4 projection = camera.getProjectionMatrix();
    GLint uProjectionMatrixLocation = glGetUniformLocation(shaderProgram, "uProjectionMatrix");
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
                       glm::vec3(scaleX, scaleY, scaleZ)
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
void Player::Draw()
{
    glUseProgram(shaderProgram);
    glBindVertexArray(vertexArrayObject);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
}

void Player::MoveUp(float speed) { translationY += speed * util.getDeltaTime(); }
void Player::MoveDown(float speed) { translationY -= speed * util.getDeltaTime(); }
void Player::MoveLeft(float speed) { translationX -= speed * util.getDeltaTime(); }
void Player::MoveRight(float speed) { translationX += speed * util.getDeltaTime(); }
void Player::MoveForward(float speed) { translationZ -= speed * util.getDeltaTime(); }
void Player::MoveBackward(float speed) { translationZ += speed * util.getDeltaTime(); }

void Player::RotateXPos(float speed) { rotationX += speed * util.getDeltaTime(); }
void Player::RotateXNeg(float speed) { rotationX -= speed * util.getDeltaTime(); }
void Player::RotateYPos(float speed) { rotationY += speed * util.getDeltaTime(); }
void Player::RotateYNeg(float speed) { rotationY -= speed * util.getDeltaTime(); }
void Player::RotateZPos(float speed) { rotationZ += speed * util.getDeltaTime(); }
void Player::RotateZNeg(float speed) { rotationZ -= speed * util.getDeltaTime(); }

void Player::ScaleXUp(float speed) { scaleX += speed * util.getDeltaTime(); }
void Player::ScaleXDown(float speed) { scaleX -= speed * util.getDeltaTime(); }
void Player::ScaleYUp(float speed) { scaleY += speed * util.getDeltaTime(); }
void Player::ScaleYDown(float speed) { scaleY -= speed * util.getDeltaTime(); }
void Player::ScaleZUp(float speed) { scaleZ += speed * util.getDeltaTime(); }
void Player::ScaleZDown(float speed) { scaleZ -= speed * util.getDeltaTime(); }

void Player::ResetModel()
{
    translationX = initialModel[0];
    translationY = initialModel[1];
    translationZ = initialModel[2];
    rotationX = initialModel[3];
    rotationY = initialModel[4];
    rotationZ = initialModel[5];
    scaleX = initialModel[6];
    scaleY = initialModel[7];
    scaleZ = initialModel[8];
}

void Player::init(float translationX, float translationY, float translationZ, float rotationX, float rotationY, float rotationZ, float scaleX, float scaleY, float scaleZ)
{
    initialModel.push_back(this->translationX = translationX);
    initialModel.push_back(this->translationY = translationY);
    initialModel.push_back(this->translationZ = translationZ);
    initialModel.push_back(this->rotationX = rotationX);
    initialModel.push_back(this->rotationY = rotationY);
    initialModel.push_back(this->rotationZ = rotationZ);
    initialModel.push_back(this->scaleX = scaleX);
    initialModel.push_back(this->scaleY = scaleY);
    initialModel.push_back(this->scaleZ = scaleZ);
}
void Player::cleanup()
{
    glDeleteVertexArrays(1, &vertexArrayObject);
    glDeleteBuffers(1, &vertexBufferObject);
    glDeleteBuffers(1, &indexBufferObject);
    glDeleteProgram(shaderProgram);
}

PlayerPtr getPlayerByName(const std::string &name)
{
    for (auto &player : players)
    {
        if (player->getName() == name)
        {
            return player;
        }
    }
    return nullptr;
}
