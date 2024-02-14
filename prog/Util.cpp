#include "Util.hpp"

Util util;

void Util::getOpenGLVersionInfo()
{
    std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl
              << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl
              << "GL Version: " << glGetString(GL_VERSION) << std::endl
              << "GL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}
template <typename Type> std::shared_ptr<Type> getObjectByName(const std::string& name);
template<> PlayerPtr Util::getObjectByName<Player>(const std::string& name)
{
    for (auto &player : players)
    {
        if (player->getName() == name)
            return player;
    }
    return nullptr;
}
template<> ItemPtr Util::getObjectByName<Item>(const std::string& name)
{
    for (auto &item : items)
    {
        if (item->getName() == name)
            return item;
    }
    return nullptr;
}

void Util::ClearAllGLErrors()
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

std::vector<std::string> Util::SplitStringByDelimiter(const std::string& string, std::string delimiter)
{
    size_t pos_start = 0;
    size_t pos_end = 0;
    size_t delimiter_length = delimiter.length();
    std::string token;
    std::vector<std::string> result;

    while ((pos_end = string.find(delimiter, pos_start)) != std::string::npos)
    {
        token = string.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delimiter_length;
        result.push_back(token);
    }

    result.push_back(string.substr(pos_start));
    return result;
}

void Util::sdlinit()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL2 could not be initialized!" << std::endl;
        exit(1);
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetSwapInterval(1); // Vsync
}
void Util::gladinit()
{
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }
}

void Util::sdlcleanup()
{
    SDL_GL_DeleteContext(window.getGLContext());
    SDL_DestroyWindow(window.getWindow()); 
    SDL_Quit();
}
