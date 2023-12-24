#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <glad/glad.h>
#include <SDL2/SDL.h>

int gScreenWidth = 1280;
int gScreenHeight = 720;
SDL_Window* gGraphicsApplicationWindow = nullptr; 
SDL_GLContext gOpenGLContext = nullptr;

bool gQuit = false;

GLuint gVertexArrayObject = 0;
GLuint gVertexBufferObject = 0;
GLuint gVertexBufferObject2 = 0;
GLuint gGraphicsPipelineShaderProgram = 0;

std::string LoadShaderAsString(const std::string& fileName)
{
    std::string result;

    std::string line;
    std::ifstream file(fileName.c_str());

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

void GetOpenGLVersionInfo()
{
    std::cout << "Vendor: " << glGetString(GL_VENDOR) << std::endl;
    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;
    std::cout << "Version:" << glGetString(GL_VERSION) << std::endl;
    std::cout << "Shading Language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}

void InitializeProgram()
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

    gGraphicsApplicationWindow = SDL_CreateWindow("SDLGL Test", 100, 100, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL);
    if (gGraphicsApplicationWindow == nullptr)
    {
        std::cout << "SDL_Window could not be created!" << std::endl;
        exit(1);
    }

    gOpenGLContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if (gOpenGLContext == nullptr)
    {
        std::cout << "OpenGl context could not be created!" << std::endl;
        exit(1);
    }

    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }

    GetOpenGLVersionInfo();
}

void VertexSpecification()
{
    const std::vector<GLfloat> vertexPositions
    {
        // x      y      z
        -0.8f, -0.8f, 0.0f, // left vertex position
        0.8f, -0.8f, 0.0f,  // right vertex position
        0.0f, 0.8f, 0.0f    // top vertex position
    };
    const std::vector<GLfloat> vertexColors
    {
        // x      y      z
        1.0f, 0.0f, 0.0f,   // left vertex color
        0.0f, 1.0f, 0.0f,   // right vertex color
        0.0f, 0.0f, 1.0f    // top vertex color
    };

    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject); 

    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexPositions.size() * sizeof(GLfloat), vertexPositions.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0); 

    glGenBuffers(1, &gVertexBufferObject2);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject2);
    glBufferData(GL_ARRAY_BUFFER, vertexColors.size() * sizeof(GLfloat), vertexColors.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

GLuint CompileShader(GLuint type, const std::string& shaderSource)
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
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);
    
    int result;
    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(shaderObject, GL_INFO_LOG_LENGTH, &length);
        char* errorMessages = new char[length];
        glGetShaderInfoLog(shaderObject, length, &length, errorMessages);

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

    return shaderObject;
}

GLuint CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
{
    GLuint programObject = glCreateProgram();

    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    return programObject;
}

void CreateGraphicsPipeline()
{
    std::string vertexShaderSource = LoadShaderAsString("prog/shaders/vertexShader.glsl");
    std::string fragmentShaderSource = LoadShaderAsString("prog/shaders/fragmentShader.glsl");

    gGraphicsPipelineShaderProgram = CreateShaderProgram(vertexShaderSource, fragmentShaderSource); 
}

void Input()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            std::cout << "Goodbye!" << std::endl;
            gQuit = true;
        }
    }
}

void PreDraw()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(0.2f, 0.2f, 0.2f, 1.f);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram);
}

void Draw()
{
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);
}

void MainLoop()
{
    while (!gQuit)
    {
        Input();

        PreDraw();

        Draw();

        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}

void CleanUp()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_Quit(); 
}

int main(int argc, char* argv[])
{
    InitializeProgram();

    VertexSpecification();

    CreateGraphicsPipeline();

    MainLoop();

    CleanUp();

    return 0;
}
