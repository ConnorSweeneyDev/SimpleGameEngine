#include <vector> // std::vector

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Util.hpp"
#include "Window.hpp"
#include "Shader.hpp"
#include "Camera.hpp" 

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;
GLuint gIndexBufferObject = 0;
GLuint gGraphicsPipelineShaderProgram = 0;
GLuint gVertexArrayObject2 = 0;
GLuint gVertexBufferObject2 = 0;
GLuint gIndexBufferObject2 = 0;
GLuint gGraphicsPipelineShaderProgram2 = 0;

float gOffsetTranslationX = 0.0f;
float gOffsetTranslationY = 0.0f;
float gOffsetTranslationZ = 0.0f;
float gOffsetRotationX = 0.0f;
float gOffsetRotationY = 0.0f;
float gOffsetRotationZ = 0.0f;
float gOffsetScale = 1.0f;
float gOffsetTranslationX2 = 0.0f;
float gOffsetTranslationY2 = 0.0f;
float gOffsetTranslationZ2 = 0.0f;

void InitializeProgram() // SDL2 4.1
{
    util.sdlinit();
    window.init();
    util.gladinit();

    util.GetOpenGLVersionInfo();
}

void VertexSpecification()
{
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    const std::vector<GLfloat> vertexData
    {
        // Vertex 0
        -0.5f, -0.5f, 0.0f, // Bottom left vertex position
        1.0f, 0.0f, 0.0f,   // Bottom left vertex color
        // Vertex 1
        0.5f, -0.5f, 0.0f,  // Bottom right vertex position
        0.0f, 1.0f, 0.0f,   // Bottom right vertex color
        // Vertex 2
        -0.5f, 0.5f, 0.0f,  // Top left vertex position
        0.0f, 0.0f, 1.0f,   // Top left vertex color
        // Vertex 3
        0.5f, 0.5f, 0.0f,   // Top right vertex position
        1.0f, 0.0f, 0.0f    // Top right vertex color
    };

    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(
                 GL_ARRAY_BUFFER,
                 vertexData.size() * sizeof(GLfloat),
                 vertexData.data(),
                 GL_STATIC_DRAW
                );
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(                   // Vertex attribute pointer for the vertex position
                          0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*6,
                          (GLvoid*)0
                         ); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(                   // Vertex attribute pointer for the vertex color
                          1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*6,
                          (GLvoid*)(sizeof(GLfloat)*3)
                         );

    const std::vector<GLuint> indexData
    {
        0, 1, 2, // first triangle
        3, 2, 1  // second triangle
    };

    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,
                 indexData.size() * sizeof(GLuint),
                 indexData.data(),
                 GL_STATIC_DRAW
                );
    
    glGenVertexArrays(1, &gVertexArrayObject2);
    glBindVertexArray(gVertexArrayObject2);

    const std::vector<GLfloat> vertexData2
    {
        // Vertex 0
        -0.1f, -0.1f, 0.0f, // Bottom left vertex position
        1.0f, 0.0f, 0.0f,   // Bottom left vertex color
        // Vertex 1
        0.1f, -0.1f, 0.0f,  // Bottom right vertex position
        0.0f, 1.0f, 0.0f,   // Bottom right vertex color
        // Vertex 2
        -0.1f, 0.1f, 0.0f,  // Top left vertex position
        0.0f, 0.0f, 1.0f,   // Top left vertex color
        // Vertex 3
        0.1f, 0.1f, 0.0f,   // Top right vertex position
        1.0f, 0.0f, 0.0f    // Top right vertex color
    };

    glGenBuffers(1, &gVertexBufferObject2);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject2);
    glBufferData(
                 GL_ARRAY_BUFFER,
                 vertexData2.size() * sizeof(GLfloat),
                 vertexData2.data(),
                 GL_STATIC_DRAW
                );
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(                   // Vertex attribute pointer for the vertex position
                          0,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*6,
                          (GLvoid*)0
                         ); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(                   // Vertex attribute pointer for the vertex color
                          1,
                          3,
                          GL_FLOAT,
                          GL_FALSE,
                          sizeof(GLfloat)*6,
                          (GLvoid*)(sizeof(GLfloat)*3)
                         );

    const std::vector<GLuint> indexData2
    {
        0, 1, 2, // first triangle
        3, 2, 1  // second triangle
    };

    glGenBuffers(1, &gIndexBufferObject2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject2);
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,
                 indexData2.size() * sizeof(GLuint),
                 indexData2.data(),
                 GL_STATIC_DRAW
                );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
{
    std::string vertexShaderSource = shader.LoadShaderAsString("prog/shaders/vertexShader.glsl");
    std::string fragmentShaderSource = shader.LoadShaderAsString("prog/shaders/fragmentShader.glsl");
    gGraphicsPipelineShaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource); 

    std::string vertexShaderSource2 = shader.LoadShaderAsString("prog/shaders/vertexShader2.glsl");
    std::string fragmentShaderSource2 = shader.LoadShaderAsString("prog/shaders/fragmentShader2.glsl");
    gGraphicsPipelineShaderProgram2 = shader.CreateShaderProgram(vertexShaderSource2, fragmentShaderSource2);
}

void InitializeGame()
{
    camera.init();
}

void Input()
{
    SDL_Event e;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            window.handleQuit();

        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window.handleResize();
            }
        }
        
        if (e.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                window.handleQuit();
            }

            if (keyState[SDL_SCANCODE_L])
            {
                window.handleFullscreen(); // Borderless fullscreen
            }
        }
    }

    if (keyState[SDL_SCANCODE_UP])
        camera.moveUp(0.005f);
    if (keyState[SDL_SCANCODE_DOWN])
        camera.moveDown(0.005f);
    if (keyState[SDL_SCANCODE_LEFT])
        camera.moveLeft(0.005f);
    if (keyState[SDL_SCANCODE_RIGHT])
        camera.moveRight(0.005f);
    if (keyState[SDL_SCANCODE_RSHIFT])
        camera.moveForward(0.005f);
    if (keyState[SDL_SCANCODE_RCTRL])
        camera.moveBackward(0.005f);

    if (keyState[SDL_SCANCODE_A])
        gOffsetTranslationX -= 0.005f;
    if (keyState[SDL_SCANCODE_D])
        gOffsetTranslationX += 0.005f;
    if (keyState[SDL_SCANCODE_W])
        gOffsetTranslationY += 0.005f;
    if (keyState[SDL_SCANCODE_S])
        gOffsetTranslationY -= 0.005f;
    if (keyState[SDL_SCANCODE_Z])
        gOffsetTranslationZ -= 0.005f;
    if (keyState[SDL_SCANCODE_X])
        gOffsetTranslationZ += 0.005f;

    if (keyState[SDL_SCANCODE_Q])
        gOffsetRotationX -= 0.5f;
    if (keyState[SDL_SCANCODE_E])
        gOffsetRotationX += 0.5f;
    if (keyState[SDL_SCANCODE_R])
        gOffsetRotationY -= 0.5f;
    if (keyState[SDL_SCANCODE_T])
        gOffsetRotationY += 0.5f;
    if (keyState[SDL_SCANCODE_F])
        gOffsetRotationZ += 0.5f;
    if (keyState[SDL_SCANCODE_G])
        gOffsetRotationZ -= 0.5f;
    
    if (keyState[SDL_SCANCODE_C])
        gOffsetScale -= 0.005f;
    if (keyState[SDL_SCANCODE_V])
        gOffsetScale += 0.005f;

    if (keyState[SDL_SCANCODE_SPACE])
    {
        camera.resetPosition();
        gOffsetTranslationX = 0.0f;
        gOffsetTranslationY = 0.0f;
        gOffsetTranslationZ = 0.0f;
        gOffsetRotationX = 0.0f;
        gOffsetRotationY = 0.0f;
        gOffsetRotationZ = 0.0f;
        gOffsetScale = 1.0f;
    }

    if (keyState[SDL_SCANCODE_H])
        gOffsetTranslationX2 -= 0.005f;
    if (keyState[SDL_SCANCODE_K])
        gOffsetTranslationX2 += 0.005f;
    if (keyState[SDL_SCANCODE_U])
        gOffsetTranslationY2 += 0.005f;
    if (keyState[SDL_SCANCODE_J])
        gOffsetTranslationY2 -= 0.005f;
}

void PreDraw()
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

    glUseProgram(gGraphicsPipelineShaderProgram);
    
    glm::mat4 perspective = glm::perspective(
                                             glm::radians(45.0f),                                  // Field of view
                                             (float)window.getWidth() / (float)window.getHeight(), // Aspect ratio
                                             0.1f, 10.0f                                           // Near and far clipping planes
                                            );
    GLint uProjectionMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uProjectionMatrix");
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
    GLint uViewMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uViewMatrix");
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
                           glm::vec3(gOffsetTranslationX, gOffsetTranslationY, gOffsetTranslationZ)
                          );
    model = glm::rotate(
                        model,
                        glm::radians(gOffsetRotationX),
                        glm::vec3(1.0f, 0.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(gOffsetRotationY),
                        glm::vec3(0.0f, 1.0f, 0.0f)
                       );
    model = glm::rotate(
                        model,
                        glm::radians(gOffsetRotationZ),
                        glm::vec3(0.0f, 0.0f, 1.0f)
                       );
    model = glm::scale(
                       model,
                       glm::vec3(gOffsetScale)
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uModelMatrix");
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
    
    glUseProgram(gGraphicsPipelineShaderProgram2);
    
    glm::mat4 perspective2 = glm::perspective(
                                              glm::radians(45.0f),                                  // Field of view
                                              (float)window.getWidth() / (float)window.getHeight(), // Aspect ratio
                                              0.1f, 10.0f                                           // Near and far clipping planes
                                             );
    GLint uProjectionMatrixLocation2 = glGetUniformLocation(gGraphicsPipelineShaderProgram2, "uProjectionMatrix");
    if (uProjectionMatrixLocation2 >= 0)
    {
        glUniformMatrix4fv(
                           uProjectionMatrixLocation2,
                           1,
                           GL_FALSE,
                           glm::value_ptr(perspective2) // Pointer to the data of perspective, &perspective2[0][0] also works
                          );
    }
    else
    {
        std::cout << "uProjectionMatrix could not be found!" << std::endl;
    }

    glm::mat4 view2 = camera.getViewMatrix();
    GLint uViewMatrixLocation2 = glGetUniformLocation(gGraphicsPipelineShaderProgram2, "uViewMatrix");
    if (uViewMatrixLocation2 >= 0)
    {
        glUniformMatrix4fv(
                           uViewMatrixLocation2,
                           1,
                           GL_FALSE,
                           glm::value_ptr(view2) // Pointer to the data of view, &view2[0][0] also works
                          );
    }
    else
    {
        std::cout << "uViewMatrix could not be found!" << std::endl;
    }

    glm::mat4 model2 = glm::mat4(1.0f); // Initialize the model's identity matrix
    model2 = glm::translate(
                           model2,
                           glm::vec3(gOffsetTranslationX2, gOffsetTranslationY2, gOffsetTranslationZ2)
                          );
    GLint uModelMatrixLocation2 = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uModelMatrix");
    if (uModelMatrixLocation2 >= 0)
    {
        glUniformMatrix4fv(
                           uModelMatrixLocation2,
                           1,
                           GL_FALSE,
                           glm::value_ptr(model2) // Pointer to the data of model, &model2[0][0] also works
                          );
    } 
    else
    {
        std::cout << "uModelMatrix could not be found!" << std::endl;
    }
}

void Draw()
{
    glUseProgram(gGraphicsPipelineShaderProgram);
    glBindVertexArray(gVertexArrayObject);
    glDrawElements(
                   GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   (GLvoid*)0
                  );

    glUseProgram(gGraphicsPipelineShaderProgram2);
    glBindVertexArray(gVertexArrayObject2);
    glDrawElements(
                   GL_TRIANGLES,
                   6,
                   GL_UNSIGNED_INT,
                   (GLvoid*)0
                  );

    glBindVertexArray(0);
    glUseProgram(0);
}

void MainLoop()
{
    while (!window.getQuit())
    {
        Input();
        PreDraw();

        Draw();
        SDL_GL_SwapWindow(window.getWindow()); // Swaps the front and back buffers, presenting the rendered image to the screen
    }
}

void CleanUp()
{
    glDeleteProgram(gGraphicsPipelineShaderProgram);
    SDL_GL_DeleteContext(window.getGLContext());
    SDL_DestroyWindow(window.getWindow());
    
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    InitializeProgram();

    VertexSpecification();
    CreateGraphicsPipeline();

    InitializeGame();
    MainLoop();

    CleanUp();

    return 0;
}
