#include "Input.hpp"

Input input;

void Input::PollWindow()
{
    while (SDL_PollEvent(&event) != 0)
    {
        switch (event.type)
        {
            case SDL_QUIT:
                window.HandleQuit();
                break;

            case SDL_KEYDOWN:
                if (keyState[SDL_SCANCODE_ESCAPE])
                    window.HandleQuit();
                if (keyState[SDL_SCANCODE_F11])
                    window.HandleFullscreen();
                break;
        }
    }
}

void Input::PollGame()
{
    if (keyState[SDL_SCANCODE_H])
        camera.MoveRight(0.001f);
    if (keyState[SDL_SCANCODE_F])
        camera.MoveLeft(0.001f);
    if (keyState[SDL_SCANCODE_T])
        camera.MoveUp(0.001f);
    if (keyState[SDL_SCANCODE_G])
        camera.MoveDown(0.001f);
    if (keyState[SDL_SCANCODE_Y])
        camera.MoveForward(0.001f);
    if (keyState[SDL_SCANCODE_R])
        camera.MoveBackward(0.001f);

    if (keyState[SDL_SCANCODE_UP])
        camera.RotateXPos(0.001f);
    if (keyState[SDL_SCANCODE_DOWN])
        camera.RotateXNeg(0.001f);
    if (keyState[SDL_SCANCODE_LEFT])
        camera.RotateYPos(0.001f);
    if (keyState[SDL_SCANCODE_RIGHT])
        camera.RotateYNeg(0.001f);
    if (keyState[SDL_SCANCODE_RSHIFT])
        camera.RotateZPos(0.001f);
    if (keyState[SDL_SCANCODE_RCTRL])
        camera.RotateZNeg(0.001f);

    if (keyState[SDL_SCANCODE_SPACE])
        camera.ResetPosition();

    // Placeholders for adding and removing objects dynamically
    if (keyState[SDL_SCANCODE_9])
    {
        render.AddObject<Item>("Item 1",
                               "prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl",
                               { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f });
    }
    auto item1 = system_util.getObjectByName<Item>("Item 1");
    if (item1)
    {
        if (keyState[SDL_SCANCODE_0])
            render.RemoveObject(item1);
    }

    auto player1 = system_util.getObjectByName<Player>("Player 1");
    if (player1)
    {
        if (keyState[SDL_SCANCODE_D])
            player1->MoveRight();
        if (keyState[SDL_SCANCODE_A])
            player1->MoveLeft();
        if (keyState[SDL_SCANCODE_W])
            player1->MoveUp();
        if (keyState[SDL_SCANCODE_S])
            player1->MoveDown();
        if (keyState[SDL_SCANCODE_E])
            player1->MoveForward();
        if (keyState[SDL_SCANCODE_Q])
            player1->MoveBackward();    

        if (keyState[SDL_SCANCODE_SPACE])
            player1->ResetPosition();
    }
    
    auto player2 = system_util.getObjectByName<Player>("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_L])
            player2->MoveRight();
        if (keyState[SDL_SCANCODE_J])
            player2->MoveLeft();
        if (keyState[SDL_SCANCODE_I])
            player2->MoveUp();
        if (keyState[SDL_SCANCODE_K])
            player2->MoveDown();
        if (keyState[SDL_SCANCODE_O])
            player2->MoveForward();
        if (keyState[SDL_SCANCODE_U])
            player2->MoveBackward();

        if (keyState[SDL_SCANCODE_SPACE])
            player2->ResetPosition();
    }
}
