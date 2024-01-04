#include "Input.hpp"

Input input;

void Input::pollEvents()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            window.handleQuit();

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window.handleResize();
            }
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                window.handleQuit();
            }

            if (keyState[SDL_SCANCODE_F11])
            {
                window.handleFullscreen(); // Borderless fullscreen toggle
            }
        }
    }
}

void Input::pollKeys()
{
    keyState = SDL_GetKeyboardState(nullptr);

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

    auto player1 = getGameObjectByName("Player 1");
    if (player1)
    {
        if (keyState[SDL_SCANCODE_W])
            player1->moveUp(0.005f);
        if (keyState[SDL_SCANCODE_S])
            player1->moveDown(0.005f);
        if (keyState[SDL_SCANCODE_A])
            player1->moveLeft(0.005f);
        if (keyState[SDL_SCANCODE_D])
            player1->moveRight(0.005f);
        if (keyState[SDL_SCANCODE_Z])
            player1->moveForward(0.005f);
        if (keyState[SDL_SCANCODE_X])
            player1->moveBackward(0.005f);    
        
        if (keyState[SDL_SCANCODE_E])
            player1->rotateXPos(0.5);
        if (keyState[SDL_SCANCODE_Q])
            player1->rotateXNeg(0.5);
        if (keyState[SDL_SCANCODE_T])
            player1->rotateYPos(0.5);
        if (keyState[SDL_SCANCODE_R])
            player1->rotateYNeg(0.5);
        if (keyState[SDL_SCANCODE_F])
            player1->rotateZPos(0.5);
        if (keyState[SDL_SCANCODE_G])
            player1->rotateZNeg(0.5);
    
        if (keyState[SDL_SCANCODE_E])
            player1->rotateXPos(0.5);
        if (keyState[SDL_SCANCODE_Q])
            player1->rotateXNeg(0.5);
        if (keyState[SDL_SCANCODE_T])
            player1->rotateYPos(0.5);
        if (keyState[SDL_SCANCODE_R])
            player1->rotateYNeg(0.5);
        if (keyState[SDL_SCANCODE_F])
            player1->rotateZPos(0.5);
        if (keyState[SDL_SCANCODE_G])
            player1->rotateZNeg(0.5);

        if (keyState[SDL_SCANCODE_C])
            player1->scaleUp(0.005f);
        if (keyState[SDL_SCANCODE_V])
            player1->scaleDown(0.005f);

        if (keyState[SDL_SCANCODE_SPACE])
            player1->reset();
    }
    
    auto player2 = getGameObjectByName("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_U])
            player2->moveUp(0.005f);
        if (keyState[SDL_SCANCODE_J])
            player2->moveDown(0.005f);
        if (keyState[SDL_SCANCODE_H])
            player2->moveLeft(0.005f);
        if (keyState[SDL_SCANCODE_K])
            player2->moveRight(0.005f);
        if (keyState[SDL_SCANCODE_B])
            player2->moveForward(0.005f);
        if (keyState[SDL_SCANCODE_N])
            player2->moveBackward(0.005f);

        if (keyState[SDL_SCANCODE_SPACE])
            player2->reset();
    }
}
