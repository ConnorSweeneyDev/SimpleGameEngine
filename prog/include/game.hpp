#pragma once

class Game
{
    public:
        void initialize_camera();
        void initialize_players();
        void initialize_items();

        void specify_game_state();
};
extern Game game;
