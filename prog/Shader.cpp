#include "Shader.hpp"

Shader shader;

template <typename Type> void Shader::setShaderProgram(std::shared_ptr<Type>& object, std::string vertexShaderPath, std::string fragmentShaderPath)
{
    std::string vertexShaderSource = shader.LoadShaderAsString(vertexShaderPath);
    std::string fragmentShaderSource = shader.LoadShaderAsString(fragmentShaderPath);
    object->shaderProgram = shader.CreateShaderProgram(vertexShaderSource, fragmentShaderSource);
}
template void Shader::setShaderProgram<Player>(PlayerPtr& object, std::string vertexShaderPath, std::string fragmentShaderPath);
template void Shader::setShaderProgram<Item>(ItemPtr& object, std::string vertexShaderPath, std::string fragmentShaderPath);

std::string Shader::LoadShaderAsString(const std::string& fileName)
{
    std::string result;

    std::ifstream file(fileName.c_str());
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line))
            result += line + "\n";

        file.close();
    }
    else
    {
        std::cout << "Unable to open file: " << fileName << "!" << std::endl;
    }

    return result;
}
GLuint Shader::CompileShader(GLuint type, const std::string& shaderSource)
{
    GLuint shaderObject;

    if (type == GL_VERTEX_SHADER)
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
    else if (type == GL_FRAGMENT_SHADER)
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER); 
    else
        shaderObject = glCreateShader(GL_NONE);
    
    const char* source = shaderSource.c_str();
    glShaderSource(
                   shaderObject,
                   1,
                   &source,
                   nullptr
                  );
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
            std::cout << "GL_VERTEX_SHADER compilation failed!\n" << errorMessages << std::endl;
        else if (type == GL_FRAGMENT_SHADER)
            std::cout << "GL_FRAGMENT_SHADER compilation failed!\n" << errorMessages << std::endl;

        delete[] errorMessages;
        glDeleteShader(shaderObject);

        return 0;
    }

    return shaderObject;
}
GLuint Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource)
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

void Shader::AssignShadersToObjects()
{
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            shader.setShaderProgram(player, "prog/shaders/vertexShader.glsl", "prog/shaders/player1.glsl");
        else if (player->getName() == "Player 2")
            shader.setShaderProgram(player, "prog/shaders/vertexShader.glsl", "prog/shaders/player2.glsl");
        else
            shader.setShaderProgram(player, "prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
    }

    for(auto& item : items)
    {
        if (item->getName() == "Floor")
            shader.setShaderProgram(item, "prog/shaders/vertexShader.glsl", "prog/shaders/floor.glsl");
        else
            shader.setShaderProgram(item, "prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
    }
}
