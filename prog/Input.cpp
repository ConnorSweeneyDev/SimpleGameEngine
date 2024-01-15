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

    auto player1 = getPlayerByName("Player 1");
    if (player1)
    {
        if (keyState[SDL_SCANCODE_W])
            player1->MoveUp();
        if (keyState[SDL_SCANCODE_S])
            player1->MoveDown();
        if (keyState[SDL_SCANCODE_A])
            player1->MoveLeft();
        if (keyState[SDL_SCANCODE_D])
            player1->MoveRight();
        if (keyState[SDL_SCANCODE_Z])
            player1->MoveForward();
        if (keyState[SDL_SCANCODE_X])
            player1->MoveBackward();    

        if (keyState[SDL_SCANCODE_SPACE])
            player1->ResetPosition();
    }
    
    auto player2 = getPlayerByName("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_U])
            player2->MoveUp();
        if (keyState[SDL_SCANCODE_J])
            player2->MoveDown();
        if (keyState[SDL_SCANCODE_H])
            player2->MoveLeft();
        if (keyState[SDL_SCANCODE_K])
            player2->MoveRight();
        if (keyState[SDL_SCANCODE_B])
            player2->MoveForward();
        if (keyState[SDL_SCANCODE_N])
            player2->MoveBackward();
        
        if (keyState[SDL_SCANCODE_SPACE])
            player2->ResetPosition();
    }
}
