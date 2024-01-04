#include "Util.hpp"
#include "Input.hpp"

void InitializeProgram()
{
    util.sdlinit();
    window.init();
    util.gladinit();
}

void VertexSpecification()
{
    GameObjectPtr player = std::make_shared<GameObject>("Player 1");
    player->SpecifyVertices(
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
    game_objects.push_back(player);

    player = std::make_shared<GameObject>("Player 2");
    player->SpecifyVertices(
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
    game_objects.push_back(player);

    util.vertexcleanup();
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
{
    for(auto& game_object : game_objects)
    {
        if (game_object->getName() == "Player 1")
            game_object->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
        else if (game_object->getName() == "Player 2")
            game_object->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader2.glsl");
        else
            game_object->setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
    }
}

void InitializeGame()
{
    camera.init();
    
    for(auto& game_object : game_objects)
    {
        if (game_object->getName() == "Player 1")
            game_object->init(-1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f);
        else if (game_object->getName() == "Player 2")
            game_object->init(1.5f, -0.2f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f);
        else
            game_object->init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f);
    }
}

void Input()
{
    input.PollEvents();
    input.PollKeys();
}

void PreDraw()
{
    util.predrawinit();
    
    for (auto& game_object : game_objects)
        game_object->PreDraw();
}

void Draw()
{
    for (auto& game_object : game_objects)
        game_object->Draw();
    
    util.drawcleanup();
}

void MainLoop()
{
    while (!window.getQuit())
    {
        Input();
        
        PreDraw();
        Draw();

        SDL_GL_SwapWindow(window.getWindow()); // Swaps the front and back buffers, presenting the rendered image to the screen
    }
}

void CleanUp()
{
    for (auto& game_object : game_objects)
        game_object->cleanup();
 
    util.sdlcleanup();
}

int main(int argc, char* argv[])
{
    InitializeProgram();
    VertexSpecification();
    CreateGraphicsPipeline();
    InitializeGame();

    MainLoop();

    CleanUp();

    return 0;
}
