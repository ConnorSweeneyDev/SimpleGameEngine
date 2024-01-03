#include "Util.hpp"
#include "GameObject.hpp"

void InitializeProgram()
{
    util.sdlinit();
    window.init();
    util.gladinit();
}

void VertexSpecification()
{
    player1.specifyVertices(
                            {
                                // Vertex 0
                                -0.5f, -0.5f, 0.0f, // Bottom left vertex position
                                1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                                // Vertex 1
                                0.5f, -0.5f, 0.0f,  // Bottom right vertex position
                                0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                                // Vertex 2
                                -0.5f, 0.5f, 0.0f,  // Top left vertex position
                                0.0f, 0.0f, 1.0f,   // Top left vertex color
                                // Vertex 3
                                0.5f, 0.5f, 0.0f,   // Top right vertex position
                                1.0f, 0.0f, 0.0f    // Top right vertex color
                            },
                            {
                                0, 1, 2, // first triangle
                                3, 2, 1  // second triangle
                            }
                           );

    player2.specifyVertices(
                            {
                                // Vertex 0
                                -0.1f, -0.1f, 0.0f, // Bottom left vertex position
                                1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                                // Vertex 1
                                0.1f, -0.1f, 0.0f,  // Bottom right vertex position
                                0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                                // Vertex 2
                                -0.1f, 0.1f, 0.0f,  // Top left vertex position
                                0.0f, 0.0f, 1.0f,   // Top left vertex color
                                // Vertex 3
                                0.1f, 0.1f, 0.0f,   // Top right vertex position
                                1.0f, 0.0f, 0.0f    // Top right vertex color
                            },
                            {
                                0, 1, 2, // first triangle
                                3, 2, 1  // second triangle
                            }
                           );

    util.vertexcleanup();
}

void CreateGraphicsPipeline() // At minimum, a graphics pipeline consists of a vertex shader and a fragment shader
{
    player1.setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl");
    player2.setShaderProgram("prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader2.glsl");
}

void InitializeGame()
{
    camera.init();
    
    player1.init(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
    player2.init(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
}

void Input()
{
    SDL_Event e;
    const Uint8* keyState = SDL_GetKeyboardState(nullptr);

    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
            window.handleQuit();

        if (e.type == SDL_WINDOWEVENT)
        {
            if (e.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window.handleResize();
            }
        }
        
        if (e.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                window.handleQuit();
            }

            if (keyState[SDL_SCANCODE_L])
            {
                window.handleFullscreen(); // Borderless fullscreen
            }
        }
    }

    if (keyState[SDL_SCANCODE_UP])
        camera.moveUp(0.005f);
    if (keyState[SDL_SCANCODE_DOWN])
        camera.moveDown(0.005f);
    if (keyState[SDL_SCANCODE_LEFT])
        camera.moveLeft(0.005f);
    if (keyState[SDL_SCANCODE_RIGHT])
        camera.moveRight(0.005f);
    if (keyState[SDL_SCANCODE_RSHIFT])
        camera.moveForward(0.005f);
    if (keyState[SDL_SCANCODE_RCTRL])
        camera.moveBackward(0.005f);

    if (keyState[SDL_SCANCODE_W])
        player1.moveUp(0.005f);
    if (keyState[SDL_SCANCODE_S])
        player1.moveDown(0.005f);
    if (keyState[SDL_SCANCODE_A])
        player1.moveLeft(0.005f);
    if (keyState[SDL_SCANCODE_D])
        player1.moveRight(0.005f);
    if (keyState[SDL_SCANCODE_Z])
        player1.moveForward(0.005f);
    if (keyState[SDL_SCANCODE_X])
        player1.moveBackward(0.005f);

    if (keyState[SDL_SCANCODE_E])
        player1.rotateXPos(0.5);
    if (keyState[SDL_SCANCODE_Q])
        player1.rotateXNeg(0.5);
    if (keyState[SDL_SCANCODE_T])
        player1.rotateYPos(0.5);
    if (keyState[SDL_SCANCODE_R])
        player1.rotateYNeg(0.5);
    if (keyState[SDL_SCANCODE_F])
        player1.rotateZPos(0.5);
    if (keyState[SDL_SCANCODE_G])
        player1.rotateZNeg(0.5);
    
    if (keyState[SDL_SCANCODE_C])
        player1.scaleUp(0.005f);
    if (keyState[SDL_SCANCODE_V])
        player1.scaleDown(0.005f);

    if (keyState[SDL_SCANCODE_SPACE])
    {
        camera.resetPosition();
        player1.reset();
    }

    if (keyState[SDL_SCANCODE_U])
        player2.moveUp(0.005f);
    if (keyState[SDL_SCANCODE_J])
        player2.moveDown(0.005f);
    if (keyState[SDL_SCANCODE_H])
        player2.moveLeft(0.005f);
    if (keyState[SDL_SCANCODE_K])
        player2.moveRight(0.005f);
}

void PreDraw()
{
    util.predrawinit();

    player1.preDraw();
    player2.preDraw();
}

void Draw()
{
    player1.draw();
    player2.draw();
    
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
    player1.cleanup();
    player2.cleanup();
 
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
