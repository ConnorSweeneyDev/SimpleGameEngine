#include "SystemUtil.hpp"

SystemUtil system_util;

void SystemUtil::getOpenGLVersionInfo() const
{
    std::cout << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl
              << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl
              << "GL Version: " << glGetString(GL_VERSION) << std::endl
              << "GL Shading Language Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl; 
}

template <typename Type> std::shared_ptr<Type> getObjectByName(const std::string& name);
template<> PlayerPtr SystemUtil::getObjectByName<Player>(const std::string& name) const
{
    for (auto &player : players)
    {
        if (player->getName() == name)
            return player;
    }
    return nullptr;
}
template<> ItemPtr SystemUtil::getObjectByName<Item>(const std::string& name) const
{
    for (auto &item : items)
    {
        if (item->getName() == name)
            return item;
    }
    return nullptr;
}

void SystemUtil::ClearAllGLErrors()
{
    while (glGetError() != GL_NO_ERROR);
}
void SystemUtil::CheckGLErrorStatus(const char* functionName, const char* fileName, int line) const
{
    while (GLenum error = glGetError())
    {
        std::cout << "OpenGL Error " << std::hex << error << std::dec << "!" // OpenGL errors are in hex
                  << "    Function: " << functionName
                  << "    File: " << fileName
                  << "    Line: " << line << std::endl;
        return;
    }
}

void SystemUtil::sdlinit()
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
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1); // Antialiasing
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
    SDL_GL_SetSwapInterval(1); // Vsync
}
void SystemUtil::gladinit()
{
    if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
    {
        std::cout << "Glad could not be initialized!" << std::endl;
        exit(1);
    }
}

void SystemUtil::sdlcleanup()
{
    window.cleanup();
    SDL_Quit();
}
