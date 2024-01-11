#include "Input.hpp"

Input input;

void Input::PollWindow()
{
    while (SDL_PollEvent(&event) != 0)
    {
        if (event.type == SDL_QUIT)
            window.HandleQuit();

        if (event.type == SDL_WINDOWEVENT)
        {
            if (event.window.event == SDL_WINDOWEVENT_RESIZED)
            {
                window.HandleResize();
            }
        }

        if (event.type == SDL_KEYDOWN)
        {
            if (keyState[SDL_SCANCODE_ESCAPE])
            {
                window.HandleQuit();
            }

            if (keyState[SDL_SCANCODE_F11])
            {
                window.HandleFullscreen(); // Borderless fullscreen toggle
            }
        }
    }
}

void Input::PollGame()
{
    keyState = SDL_GetKeyboardState(nullptr);

    if (keyState[SDL_SCANCODE_UP])
        camera.MoveUp(0.001f);
    if (keyState[SDL_SCANCODE_DOWN])
        camera.MoveDown(0.001f);
    if (keyState[SDL_SCANCODE_LEFT])
        camera.MoveLeft(0.001f);
    if (keyState[SDL_SCANCODE_RIGHT])
        camera.MoveRight(0.001f);
    if (keyState[SDL_SCANCODE_RSHIFT])
        camera.MoveForward(0.001f);
    if (keyState[SDL_SCANCODE_RCTRL])
        camera.MoveBackward(0.001f);

    if (keyState[SDL_SCANCODE_SPACE])
        camera.ResetPosition();

    auto player1 = getGameObjectByName("Player 1");
    if (player1)
    {
        if (keyState[SDL_SCANCODE_W])
            player1->MoveUp(0.001f);
        if (keyState[SDL_SCANCODE_S])
            player1->MoveDown(0.001f);
        if (keyState[SDL_SCANCODE_A])
            player1->MoveLeft(0.001f);
        if (keyState[SDL_SCANCODE_D])
            player1->MoveRight(0.001f);
        if (keyState[SDL_SCANCODE_Z])
            player1->MoveForward(0.001f);
        if (keyState[SDL_SCANCODE_X])
            player1->MoveBackward(0.001f);    
        
        if (keyState[SDL_SCANCODE_E])
            player1->RotateXPos(0.1);
        if (keyState[SDL_SCANCODE_Q])
            player1->RotateXNeg(0.1);
        if (keyState[SDL_SCANCODE_T])
            player1->RotateYPos(0.1);
        if (keyState[SDL_SCANCODE_R])
            player1->RotateYNeg(0.1);
        if (keyState[SDL_SCANCODE_F])
            player1->RotateZPos(0.1);
        if (keyState[SDL_SCANCODE_G])
            player1->RotateZNeg(0.1);
    
        if (keyState[SDL_SCANCODE_C])
            player1->ScaleUp(0.001f);
        if (keyState[SDL_SCANCODE_V])
            player1->ScaleDown(0.001f);

        if (keyState[SDL_SCANCODE_SPACE])
            player1->ResetModel();
    }
    
    auto player2 = getGameObjectByName("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_U])
            player2->MoveUp(0.001f);
        if (keyState[SDL_SCANCODE_J])
            player2->MoveDown(0.001f);
        if (keyState[SDL_SCANCODE_H])
            player2->MoveLeft(0.001f);
        if (keyState[SDL_SCANCODE_K])
            player2->MoveRight(0.001f);
        if (keyState[SDL_SCANCODE_B])
            player2->MoveForward(0.001f);
        if (keyState[SDL_SCANCODE_N])
            player2->MoveBackward(0.001f);

        if (keyState[SDL_SCANCODE_I])
            player2->RotateXPos(0.1);
        if (keyState[SDL_SCANCODE_Y])
            player2->RotateXNeg(0.1);
        if (keyState[SDL_SCANCODE_P])
            player2->RotateYPos(0.1);
        if (keyState[SDL_SCANCODE_O])
            player2->RotateYNeg(0.1);
        if (keyState[SDL_SCANCODE_L])
            player2->RotateZPos(0.1);
        if (keyState[SDL_SCANCODE_SEMICOLON])
            player2->RotateZNeg(0.1);
    
        if (keyState[SDL_SCANCODE_M])
            player2->ScaleUp(0.001f);
        if (keyState[SDL_SCANCODE_COMMA])
            player2->ScaleDown(0.001f);
        
        if (keyState[SDL_SCANCODE_SPACE])
            player2->ResetModel();
    }
}
