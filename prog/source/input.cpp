#include "input.hpp"
#include "window.hpp"
#include "render.hpp"
#include "camera.hpp"
#include "player.hpp"
#include "item.hpp"

namespace cse
{
    Input input;

    void Input::read()
    {
        while (SDL_PollEvent(&event) != 0)
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    window.should_quit = true;
                    break;

                case SDL_KEYDOWN:
                    if (key_state[SDL_SCANCODE_ESCAPE])
                        window.should_quit = true;
                    if (key_state[SDL_SCANCODE_F11])
                        window.handle_fullscreen();
                    break;
            }
        }

        if (key_state[SDL_SCANCODE_H])
            camera.move_right(0.001f);
        if (key_state[SDL_SCANCODE_F])
            camera.move_left(0.001f);
        if (key_state[SDL_SCANCODE_T])
            camera.move_up(0.001f);
        if (key_state[SDL_SCANCODE_G])
            camera.move_down(0.001f);
        if (key_state[SDL_SCANCODE_Y])
            camera.move_forward(0.001f);
        if (key_state[SDL_SCANCODE_R])
            camera.move_backward(0.001f);

        if (key_state[SDL_SCANCODE_SPACE])
            camera.reset_orientation();

        // Tests for adding and removing objects dynamically
        if (key_state[SDL_SCANCODE_9])
        {
            render.add_dynamic_object<Item>("Item 1", "assets/redhood.png", "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl", { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f });
        }
        auto item_1 = render.get_object_by_name<Item>("Item 1");
        if (item_1)
        {
            if (key_state[SDL_SCANCODE_0])
                render.remove_object(item_1);
        }

        if (key_state[SDL_SCANCODE_7])
        {
            render.add_dynamic_object<Item>("Item 2", "assets/lamp.png", "prog/shader/vertex_shader.glsl", "prog/shader/fragment_shader.glsl", { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.f, 1.0f, 1.0f, 1.0f });
        }
        auto item_2 = render.get_object_by_name<Item>("Item 2");
        if (item_2)
        {
            if (key_state[SDL_SCANCODE_8])
                render.remove_object(item_2);
        }

        auto player_1 = render.get_object_by_name<Player>("Player 1");
        if (player_1)
        {
            if (key_state[SDL_SCANCODE_D])
                player_1->move_right();
            if (key_state[SDL_SCANCODE_A])
                player_1->move_left();
            if (key_state[SDL_SCANCODE_W])
                player_1->move_up();
            if (key_state[SDL_SCANCODE_S])
                player_1->move_down();
            if (key_state[SDL_SCANCODE_E])
                player_1->move_forward();
            if (key_state[SDL_SCANCODE_Q])
                player_1->move_backward();    

            if (key_state[SDL_SCANCODE_SPACE])
                player_1->reset_position();
        }
        
        auto player_2 = render.get_object_by_name<Player>("Player 2");
        if (player_2)
        {
            if (key_state[SDL_SCANCODE_L])
                player_2->move_right();
            if (key_state[SDL_SCANCODE_J])
                player_2->move_left();
            if (key_state[SDL_SCANCODE_I])
                player_2->move_up();
            if (key_state[SDL_SCANCODE_K])
                player_2->move_down();
            if (key_state[SDL_SCANCODE_O])
                player_2->move_forward();
            if (key_state[SDL_SCANCODE_U])
                player_2->move_backward();

            if (key_state[SDL_SCANCODE_SPACE])
                player_2->reset_position();
        }
    }
}
