#include "Input.hpp"
#include "Render.hpp"

void InitializeProgram()
{
    util.sdlinit();
    window.init();
    util.gladinit();
}

void VertexSpecification()
{
    render.DefineVertices();

    render.vertexcleanup();
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
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

void InitializeGame()
{
    camera.init(45.0f, 0.1f, 10.0f, glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    
    for(auto& player : players)
    {
        if (player->getName() == "Player 1")
            player->init(-1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f,
                         200, 0.001);
        else if (player->getName() == "Player 2")
            player->init(1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, -1.0f, 1.0f, 1.0f,
                         100, 0.002);
        else
            player->init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f,
                         100, 0.001);
    }

    for(auto& item : items)
    {
        if (item->getName() == "Floor")
            item->init(0.0f, -1.2f, 0.0f, 0.0f, 0.0f, 0.f, 10.0f, 1.0f, 1.0f);
        else
            item->init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f);
    }
}

void Input()
{
    input.PollWindow();
    input.PollGame();
}

void PreDraw()
{
    render.predrawinit();
    
    for (auto& player : players)
        render.PreDraw(player);

    for (auto& item : items)
        render.PreDraw(item);
}

void Draw()
{
    for (auto& player : players)
        render.Draw(player);

    for (auto& item : items)
        render.Draw(item);
    
    render.drawcleanup();
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
        render.objectcleanup(player);

    for (auto& item : items)
        render.objectcleanup(item);
 
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
