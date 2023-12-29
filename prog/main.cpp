#include <iostream> // For console output
#include <fstream>  // For file input and output
#include <string>   // std::string
#include <vector>   // std::vector

#include <SDL2/SDL.h>                    // Create an OpenGL context and manage the window
#include <glad/glad.h>                   // Load OpenGL functions
#include <glm/glm.hpp>                   // Mathematics library
#include <glm/vec2.hpp>                  // glm::vec2
#include <glm/vec3.hpp>                  // glm::vec3
#include <glm/vec4.hpp>                  // glm::vec4
#include <glm/mat4x4.hpp>                // glm::mat4
#include <glm/ext/matrix_transform.hpp>  // glm::translate, glm::rotate, glm::scale
#include <glm/gtc/type_ptr.hpp>          // glm::value_ptr, glm::perspective
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp>  // glm::pi

#include "Camera.hpp" // Camera::...

int gWindowWidth = 1280;
int gWindowHeight = 720;
SDL_Window* gGraphicsApplicationWindow = nullptr;
SDL_GLContext gOpenGLContext = nullptr;

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;
GLuint gIndexBufferObject = 0;
GLuint gGraphicsPipelineShaderProgram = 0;

Camera gCamera;

float gOffsetTranslationX = 0.0f;
float gOffsetTranslationY = 0.0f;
float gOffsetTranslationZ = 0.0f;
float gOffsetRotationX = 0.0f;
float gOffsetRotationY = 0.0f;
float gOffsetRotationZ = 0.0f;
float gOffsetScale = 1.0f;

bool gQuit = false;
bool gFullscreen = false;

void ClearAllGLErrors() // Clears any errors that might have been generated previously
{
    while (glGetError() != GL_NO_ERROR){ }
}

bool CheckGLErrorStatus(const char* functionName, const char* fileName, int line) // Checks for errors and displays them
{
    while (GLenum error = glGetError())
    {
        std::cout << "OpenGL Error " << std::hex << error << std::dec << "!"
                  << "    Function: " << functionName
                  << "    File: " << fileName
                  << "    Line: " << line << std::endl;
        return true;
    }

    return false;
}

#define CheckGL(function) ClearAllGLErrors(); function; CheckGLErrorStatus(#function, __FILE__, __LINE__); // Macro for use in finding and displaying errors

void GetOpenGLVersionInfo() // Displays information about the OpenGL version
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}

void InitializeProgram() // Initializes SDL2 4.1, OpenGL, and GLAD
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

    gGraphicsApplicationWindow = SDL_CreateWindow(
                                                  "SDLGL Test",                // Window title
                                                  100, 100,                    // Window top left corner coordinates
                                                  gWindowWidth, gWindowHeight, // Window width and height
                                                  SDL_WINDOW_OPENGL            // Window type
                                                 );
    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window could not be created!" << std::endl;
        exit(1);
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow); // Creates an OpenGL context associated with the window
    if (gOpenGLContext == nullptr)
    {
        std::cout << "OpenGl context could not be created!" << std::endl;
        exit(1);
    }

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
                          sizeof(GL_FLOAT)*6, // Stride (the space between consecutive vertex attributes)
                          (GLvoid*)0          // Offset of the first component
                         ); 
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(                              // Vertex attribute pointer for the vertex color
                          1,                            // Index of the vertex attribute pointer
                          3,                            // Number of components per vertex attribute
                          GL_FLOAT,                     // Type of data of each component
                          GL_FALSE,                     // Whether the data is normalized
                          sizeof(GL_FLOAT)*6,           // Stride (the space between consecutive vertex attributes)
                          (GLvoid*)(sizeof(GL_FLOAT)*3) // Offset of the first component
                         );

    const std::vector<GLuint> indexData
    {
        0, 1, 2, // first triangle
        1, 2, 3  // second triangle
    };

    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(
                 GL_ELEMENT_ARRAY_BUFFER,           // Type of buffer to target
                 indexData.size() * sizeof(GLuint), // Size of the buffer in bytes
                 indexData.data(),                  // The data to be used
                 GL_STATIC_DRAW                     // How the data will be used
                );

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);         // Gets the length of the error message
        char* errorMessages = new char[length];                           // Creates a new char array with the length of the error message
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages); // Gets the error message

        if (type == GL_VERTEX_SHADER)
        {
            std::cout << "GL_VERTEX_SHADER compilation failed!\n" << errorMessages << std::endl;   // Displays the vertex shader error message
        }
        else if (type == GL_FRAGMENT_SHADER)
        {
            std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << std::endl; // Displays the fragment shader error message
        }

        delete[] errorMessages;       // Deletes the error message char array
        glDeleteShader(shaderObject); // Deletes the shader object

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

void Input() // Handles input events
{
    SDL_Event e;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT) // Code for the window close button
        {
            std::cout << "Goodbye!" << std::endl;
            gQuit = true;
        }

        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED) // Code for entering and exiting fullscreen mode
            {
                SDL_GetWindowSize(gGraphicsApplicationWindow, &gWindowWidth, &gWindowHeight);
                glViewport(0, 0, gWindowWidth, gWindowHeight);
            }
        }
        
        if (e.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])        // Gives the escape key the same functionality as the window close button
            {
                std::cout << "Goodbye!" << std::endl;
                gQuit = true;
            }

            if (keyState[SDL_SCANCODE_L])             // Fullscreen toggle is on L
            {
                if (!gFullscreen)
                {
                    SDL_SetWindowFullscreen(gGraphicsApplicationWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
                    gFullscreen = true;
                }
                else
                {
                    SDL_SetWindowFullscreen(gGraphicsApplicationWindow, 0);
                    gFullscreen = false;
                }
            }
        }
    }

    if (keyState[SDL_SCANCODE_UP])     // Camera movement is on the arrow keys
        gCamera.moveUp(0.005f);
    if (keyState[SDL_SCANCODE_DOWN])
        gCamera.moveDown(0.005f);
    if (keyState[SDL_SCANCODE_LEFT])
        gCamera.moveLeft(0.005f);
    if (keyState[SDL_SCANCODE_RIGHT])
        gCamera.moveRight(0.005f);
    if (keyState[SDL_SCANCODE_RSHIFT])
        gCamera.moveForward(0.005f);
    if (keyState[SDL_SCANCODE_RCTRL])
        gCamera.moveBackward(0.005f);

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
               0,            // X position of the lower left corner of the viewport rectangle
               0,            // Y position of the lower left corner of the viewport rectangle
               gWindowWidth, // Width of the viewport rectangle
               gWindowHeight // Height of the viewport rectangle
              );
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT); // Resets the depth and color buffers to the values set above

    glUseProgram(gGraphicsPipelineShaderProgram);
    
    glm::mat4 perspective = glm::perspective(
                                             glm::radians(45.0f),                        // Field of view
                                             (float)gWindowWidth / (float)gWindowHeight, // Aspect ratio
                                             0.1f, 10.0f                                 // Near and far clipping planes
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

    glm::mat4 view = gCamera.getViewMatrix();
    GLint uViewMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uViewMatrix"); // Gets the location of the uniform variable
    if (uViewMatrixLocation >= 0)                                                                    // If the uniform variable exists, it's value is passed to the shader
    {
        glUniformMatrix4fv(
                           uViewMatrixLocation, // Location of the uniform variable
                           1,                   // Number of matrices
                           GL_FALSE,            // Whether to transpose the matrix
                           glm::value_ptr(view) // Pointer to the data of view
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
                        model,                          // Identity matrix (the matrix to rotate)
                        glm::radians(gOffsetRotationY), // Rotation vector
                        glm::vec3(0.0f, 1.0f, 0.0f)     // Axis of rotation
                       );
    model = glm::rotate(
                        model,                          // Identity matrix (the matrix to rotate)
                        glm::radians(gOffsetRotationZ), // Rotation vector
                        glm::vec3(0.0f, 0.0f, 1.0f)     // Axis of rotation
                       );
    model = glm::scale(
                       model,                  // Identity matrix (the matrix to scale)
                       glm::vec3(gOffsetScale) // Scale vector
                      );
    GLint uModelMatrixLocation = glGetUniformLocation(gGraphicsPipelineShaderProgram, "uModelMatrix"); // Gets the location of the uniform variable
    if (uModelMatrixLocation >= 0)                                                                     // If the uniform variable exists, it's value is passed to the shader
    {
        glUniformMatrix4fv(
                           uModelMatrixLocation, // Location of the uniform variable
                           1,                    // Number of matrices
                           GL_FALSE,             // Whether to transpose the matrix
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

void MainLoop() // The main program loop
{
    while (!gQuit)
    {
        Input();

        PreDraw();

        Draw();

        SDL_GL_SwapWindow(gGraphicsApplicationWindow); // Swaps the front and back buffers, presenting the rendered image to the screen
    }
}

void CleanUp() // Cleans up the program
{
    glDeleteProgram(gGraphicsPipelineShaderProgram);
    SDL_GL_DeleteContext(gOpenGLContext);
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit();
}

int main(int argc, char* argv[]) // The entry point of the program
{
    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();

    MainLoop();

    CleanUp();

    return 0;
}
