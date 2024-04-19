#pragma once

class Game
{
    public:
        void initialize_camera();
        void initialize_players();
        void initialize_items();

        void object_init();
};
extern Game game;
