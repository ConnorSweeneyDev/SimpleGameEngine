#include "Input.hpp"

void InitializeProgram()
{
    util.sdlinit();
    window.init();
    util.gladinit();
}

void VertexSpecification()
{
    util.DefineVertices();

    util.vertexcleanup();
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
{
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            player->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
        else if (player->getName() == "Player 2")
            player->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader2.glsl");
        else
            player->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
    }
}

void InitializeGame()
{
    camera.init(45.0f, 0.1f, 10.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            player->init(-1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f);
        else if (player->getName() == "Player 2")
            player->init(1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, -1.0f, 1.0f, 1.0f);
        else
            player->init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f);
    }
}

void Input()
{
    input.PollWindow();
    input.PollGame();
}

void PreDraw()
{
    util.predrawinit();
    
    for (auto& player : players)
        player->PreDraw();
}

void Draw()
{
    for (auto& player : players)
        player->Draw();
    
    util.drawcleanup();
}

void MainLoop()
{
    while (!window.getQuit())
    {
        util.UpdateDeltaTime();

        Input();
        
        PreDraw();
        Draw();

        SDL_GL_SwapWindow(window.getWindow()); // Swaps the front and back buffers, presenting the rendered image to the screen
    }
}

void CleanUpProgram()
{
    for (auto& player : players)
        player->cleanup();
 
    util.sdlcleanup();
}

int main(int argc, char* argv[])
{
    InitializeProgram();
    VertexSpecification();
    CreateGraphicsPipeline();
    InitializeGame();

    MainLoop();

    CleanUpProgram();

    return 0;
}
