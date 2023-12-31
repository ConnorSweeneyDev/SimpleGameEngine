#include "error.hpp"

Error error;

void Error::ClearAllGLErrors() // OpenGL errors can stack up, so this clears them all
{
    while (glGetError() != GL_NO_ERROR);
}
bool Error::CheckGLErrorStatus(const char* functionName, const char* fileName, int line) // Checks for errors and displays them
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
