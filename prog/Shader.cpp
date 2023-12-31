#include "Shader.hpp"

Shader shader;

std::string Shader::LoadShaderAsString(const std::string& fileName) // Loads a shader from a file and returns it as a string
{
    std::string result;

    std::ifstream file(fileName.c_str());
    std::string line;

    if (file.is_open())
    {
        while (std::getline(file, line)) // Concatenates each line of the file into a single string
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

GLuint Shader::CompileShader(GLuint type, const std::string& shaderSource) // Compiles a shader and returns its ID
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
GLuint Shader::CreateShaderProgram(const std::string& vertexShaderSource, const std::string& fragmentShaderSource) // Creates a shader program and returns its ID
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
