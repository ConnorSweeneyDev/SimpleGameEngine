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
                    window.HandleFullscreen(); // Custom borderless fullscreen to avoid tearing
                break;
        }
    }
}

void Input::PollGame()
{
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

    // Placeholders for adding and removing objects dynamically
    if (keyState[SDL_SCANCODE_9])
    {
        render.AddObject<Item>(
                               "Item 1",
                               "prog/shaders/vertexShader.glsl", "prog/shaders/fragmentShader.glsl",
                               { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f }
                              );
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
        if (keyState[SDL_SCANCODE_W])
            player1->MoveUp();
        if (keyState[SDL_SCANCODE_S])
            player1->MoveDown();
        if (keyState[SDL_SCANCODE_A])
            player1->MoveLeft();
        if (keyState[SDL_SCANCODE_D])
            player1->MoveRight();
        if (keyState[SDL_SCANCODE_E])
            player1->MoveForward();
        if (keyState[SDL_SCANCODE_Q])
            player1->MoveBackward();    

        if (keyState[SDL_SCANCODE_1])
            player1->RotateXNeg(0.1f);
        if (keyState[SDL_SCANCODE_Z])
            player1->RotateXPos(0.1f);
        if (keyState[SDL_SCANCODE_X])
            player1->RotateYNeg(0.1f);
        if (keyState[SDL_SCANCODE_C])
            player1->RotateYPos(0.1f);
        if (keyState[SDL_SCANCODE_V])
            player1->RotateZNeg(0.1f);
        if (keyState[SDL_SCANCODE_B])
            player1->RotateZPos(0.1f);

        if (keyState[SDL_SCANCODE_R])
            player1->ScaleXPos(0.001f);
        if (keyState[SDL_SCANCODE_F])
            player1->ScaleXNeg(0.001f);
        if (keyState[SDL_SCANCODE_T])
            player1->ScaleYPos(0.001f);
        if (keyState[SDL_SCANCODE_G])
            player1->ScaleYNeg(0.001f);
        if (keyState[SDL_SCANCODE_Y])
            player1->ScaleZPos(0.001f);
        if (keyState[SDL_SCANCODE_H])
            player1->ScaleZNeg(0.001f);

        if (keyState[SDL_SCANCODE_SPACE])
            player1->ResetPosition();
        if (keyState[SDL_SCANCODE_TAB])
            render.RemoveObject(player1);
    }
    
    auto player2 = system_util.getObjectByName<Player>("Player 2");
    if (player2)
    {
        if (keyState[SDL_SCANCODE_I])
            player2->MoveUp();
        if (keyState[SDL_SCANCODE_K])
            player2->MoveDown();
        if (keyState[SDL_SCANCODE_J])
            player2->MoveLeft();
        if (keyState[SDL_SCANCODE_L])
            player2->MoveRight();
        if (keyState[SDL_SCANCODE_O])
            player2->MoveForward();
        if (keyState[SDL_SCANCODE_U])
            player2->MoveBackward();
        
        if (keyState[SDL_SCANCODE_N])
            player2->RotateXNeg(0.1f);
        if (keyState[SDL_SCANCODE_M])
            player2->RotateXPos(0.1f);
        if (keyState[SDL_SCANCODE_COMMA])
            player2->RotateYNeg(0.1f);
        if (keyState[SDL_SCANCODE_PERIOD])
            player2->RotateYPos(0.1f);
        if (keyState[SDL_SCANCODE_SLASH])
            player2->RotateZNeg(0.1f);
        if (keyState[SDL_SCANCODE_2])
            player2->RotateZPos(0.1f);

        if (keyState[SDL_SCANCODE_P])
            player2->ScaleXPos(0.001f);
        if (keyState[SDL_SCANCODE_SEMICOLON])
            player2->ScaleXNeg(0.001f);
        if (keyState[SDL_SCANCODE_LEFTBRACKET])
            player2->ScaleYPos(0.001f);
        if (keyState[SDL_SCANCODE_APOSTROPHE])
            player2->ScaleYNeg(0.001f);
        if (keyState[SDL_SCANCODE_RIGHTBRACKET])
            player2->ScaleZPos(0.001f);
        if (keyState[SDL_SCANCODE_BACKSLASH])
            player2->ScaleZNeg(0.001f);
        
        if (keyState[SDL_SCANCODE_SPACE])
            player2->ResetPosition();
        if (keyState[SDL_SCANCODE_BACKSPACE])
            render.RemoveObject(player2);
    }
}
