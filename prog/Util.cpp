#include "Util.hpp"

Util util;

void Util::getOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl
              << "Renderer: " << glGetString(GL_RENDERER) << std::endl
              << "Version: " << glGetString(GL_VERSION) << std::endl
              << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}
float Util::getDeltaTime() { return deltaTime; }

void Util::ClearAllGLErrors() // OpenGL errors can stack up
{
    while (glGetError() != GL_NO_ERROR);
}
bool Util::CheckGLErrorStatus(const char* functionName, const char* fileName, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "OpenGL Error " << std::hex << error << std::dec << "!" // OpenGL errors are in hex
                  << "    Function: " << functionName
                  << "    File: " << fileName
                  << "    Line: " << line << std::endl;
        return true;
    }

    return false;
}

void Util::DefineVertices()
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
void Util::UpdateDeltaTime()
{
    currentTime = SDL_GetTicks64();
    deltaTime = (currentTime - lastTime);
    lastTime = currentTime;
}

void Util::sdlinit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL2 could not be initialized!" << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(0); // Vsync
}
void Util::gladinit()
{
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }
}
void Util::predrawinit()
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

void Util::sdlcleanup()
{
    SDL_GL_DeleteContext(window.getGLContext());
    SDL_DestroyWindow(window.getWindow()); 
    SDL_Quit();
}
void Util::vertexcleanup()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Util::drawcleanup()
{
    glBindVertexArray(0);
    glUseProgram(0);
}
