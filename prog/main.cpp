#include "Render.hpp"
#include "Input.hpp"
#include "Game.hpp"

void InitializeProgram()
{
    util.sdlinit();
    window.init();
    util.gladinit();
}

void VertexSpecification()
{
    render.SpecifyObjects();
    render.vertexcleanup();
}

void CreateGraphicsPipeline()
{
    shader.AssignShadersToObjects();
}

void InitializeGame()
{
    game.InitializeGameObjects();
}

void Input()
{
    input.PollWindow();
    input.PollGame();
}

void PreDraw()
{
    render.predrawinit();
    render.PreDrawObjects();
}

void Draw()
{
    render.DrawObjects();
    render.drawcleanup();
}

void MainLoop()
{
    while (!window.getQuit())
    {
        time_util.UpdateDeltaTime();

        Input();
        
        PreDraw();
        Draw();

        SDL_GL_SwapWindow(window.getWindow());
    }
}

void CleanUpProgram()
{
    render.CleanupObjects();
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
