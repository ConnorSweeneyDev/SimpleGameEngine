#include <fstream> // File input and output
#include <vector>  // std::vector
#include <string>  // std::getline

#include <glm/gtc/type_ptr.hpp> // glm::value_ptr

#include "Error.hpp"
#include "Window.hpp"
#include "Camera.hpp" 

#define CheckGL(function) error.ClearAllGLErrors(); function; error.CheckGLErrorStatus(#function, __FILE__, __LINE__); // Macro for use in finding and displaying OpenGL function errors

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;
GLuint gIndexBufferObject = 0;
GLuint gGraphicsPipelineShaderProgram = 0;

float gOffsetTranslationX = 0.0f;
float gOffsetTranslationY = 0.0f;
float gOffsetTranslationZ = 0.0f;
float gOffsetRotationX = 0.0f;
float gOffsetRotationY = 0.0f;
float gOffsetRotationZ = 0.0f;
float gOffsetScale = 1.0f;

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}

void InitializeProgram() // Initializes SDL2 4.1, the OpenGL window, and functions via GLAD
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL2 could not be initialized!" << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // Double buffering enabled
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);  // 24 layers of depth
    
    window.init();

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress)) // Loads OpenGL functions using GLAD
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void VertexSpecification() // Creates a vertex array object, a vertex buffer object, and an index buffer object
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
                 GL_ARRAY_BUFFER,                     // Type of buffer to target
                 vertexData.size() * sizeof(GLfloat), // Size of the buffer in bytes
                 vertexData.data(),                   // The data to be used
                 GL_STATIC_DRAW                       // How the data will be used
                );
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(                    // Vertix attribute pointer for the vertex position
                          0,                  // Index of the vertex attribute pointer
                          3,                  // Number of components per vertex attribute
                          GL_FLOAT,           // Type of data of each component
                          GL_FALSE,           // Whether the data is normalized
                          sizeof(GLfloat)*6, // Stride (the space between consecutive vertex attributes)
                          (GLvoid*)0          // Offset of the first component
                         ); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(                              
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
        1, 2, 3  // second triangle
    };

    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,
                 indexData.size() * sizeof(GLuint),
                 indexData.data(),
                 GL_STATIC_DRAW
                );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::string LoadShaderAsString(const std::string& fileName) // Loads a shader from a file and returns it as a string
{
    std::string result;

    std::ifstream file(fileName.c_str());
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line))
        {
            result += line + "\n";
        }
        file.close();
    }
    else
    {
        std::cout << "Unable to open file: " << fileName << "!" << std::endl;
    }

    return result;
}

GLuint CompileShader(GLuint type, const std::string& shaderSource) // Compiles a shader and returns its ID
{
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER)
    {
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    }
    else if (type == GL_FRAGMENT_SHADER)
    {
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER); 
    }
    else
    {
        shaderObject = glCreateShader(GL_NONE);
    }
    
    const char* source = shaderSource.c_str();
    glShaderSource(
                   shaderObject, // Destination for the shader source
                   1,            // Number of elements in the string and length arrays
                   &source,      // The shader source code as a string
                   nullptr       // Array of string lengths
                  );
    glCompileShader(shaderObject);
    
    int result;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result); // Gets the compile status of the shader

    if (result == GL_FALSE) // If the shader failed to compile
    {
        int length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);         // Gets the length of the array of error messages
        char* errorMessages = new char[length];                           // Creates a new char array with the length of the error message array
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages); // Puts the error messages inside the array

        if (type == GL_VERTEX_SHADER)
        {
            std::cout << "GL_VERTEX_SHADER compilation failed!\n" << errorMessages << std::endl;
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << std::endl;
        }

        delete[] errorMessages;
        glDeleteShader(shaderObject);

        return 0;
    }

    return shaderObject; // Upon successful compilation, returns the shader object
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) // Creates a shader program and returns its ID
{
    GLuint programObject = glCreateProgram();

    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, vertexShader);
    glAttachShader(programObject, fragmentShader);
    
    glLinkProgram(programObject);
    glValidateProgram(programObject);

    return programObject;
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
{
    std::string vertexShaderSource = LoadShaderAsString("prog/shaders/vertexShader.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("prog/shaders/fragmentShader.glsl");

    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource); 
}

void InitializeGame()
{
    camera.init();
}

void Input() // Handles input and window events
{
    SDL_Event e;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)  // Code for the window close button
            window.handleQuit(); // Sets the quit flag to true

        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window.handleResize(); // Sets the viewport to the new window size
            }
        }
        
        if (e.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                window.handleQuit(); // Sets the quit flag to true
            }

            if (keyState[SDL_SCANCODE_L]) // Fullscreen toggle is on L
            {
                window.handleFullscreen(); // Switches between fullscreen borderless and windowed mode and updates the flag
            }
        }
    }

    if (keyState[SDL_SCANCODE_UP])     // Camera movement is on the arrow keys
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

    if (keyState[SDL_SCANCODE_A])      // Translations are on WASD
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

    if (keyState[SDL_SCANCODE_Q])      // Rotations are on QERTFG
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
    
    if (keyState[SDL_SCANCODE_C])      // Scaling is on CV
        gOffsetScale -= 0.005f;
    if (keyState[SDL_SCANCODE_V])
        gOffsetScale += 0.005f;

    if (keyState[SDL_SCANCODE_SPACE])  // Reset is on space
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
}

void PreDraw()
{
    glDisable(GL_DEPTH_TEST); // Depth testing disabled
    glDisable(GL_CULL_FACE);  // Face culling disabled

    glViewport(
               0,                 // X position of the lower left corner of the viewport rectangle
               0,                 // Y position of the lower left corner of the viewport rectangle
               window.getWidth(), // Width of the viewport rectangle
               window.getHeight() // Height of the viewport rectangle
              );
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Resets the depth and color buffers to the values set above

    glUseProgram(gGraphicsPipelineShaderProgram);
    
    glm::mat4 perspective = glm::perspective(
                                             glm::radians(45.0f),                                  // Field of view
                                             (float)window.getWidth() / (float)window.getHeight(), // Aspect ratio
                                             0.1f, 10.0f                                           // Near and far clipping planes
                                            );
    GLint uProjectionMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uProjectionMatrix"); // Gets the location of the uniform variable
    if (uProjectionMatrixLocation >= 0)                                                                          // If the uniform variable exists, it's value is passed to the shader
    {
        glUniformMatrix4fv(
                           uProjectionMatrixLocation,  // Location of the uniform variable
                           1,                          // Number of matrices
                           GL_FALSE,                   // Whether to transpose the matrix
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
                           model,                                                                   // Identity matrix (the matrix to translate)
                           glm::vec3(gOffsetTranslationX, gOffsetTranslationY, gOffsetTranslationZ) // Translation vector
                          );
    model = glm::rotate(
                        model,                          // Identity matrix (the matrix to rotate)
                        glm::radians(gOffsetRotationX), // Rotation vector
                        glm::vec3(1.0f, 0.0f, 0.0f)     // Axis of rotation
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
                       model,                  // Identity matrix (the matrix to scale)
                       glm::vec3(gOffsetScale) // Scale vector
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
}

void Draw()
{
    glBindVertexArray(gVertexArrayObject);

    glDrawElements(
                   GL_TRIANGLES,    // Type of primitive to draw
                   6,               // Number of vertexes to be rendered
                   GL_UNSIGNED_INT, // Type of the vertexes values
                   (GLvoid*)0       // Offset of the first index
                  );

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

void CleanUp() // Runs at the end of the program
{
    glDeleteProgram(gGraphicsPipelineShaderProgram);
    SDL_GL_DeleteContext(window.getGLContext());
    SDL_DestroyWindow(window.getWindow());
    SDL_Quit();
}

int main(int argc, char* argv[]) // The entry point of the program
{
    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();

    InitializeGame();

    MainLoop();

    CleanUp();

    return 0;
}
