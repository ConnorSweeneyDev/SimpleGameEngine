#include "render.hpp"
#include "window.hpp"
#include "item.hpp"
#include "player.hpp"

namespace cse::object
{
    Render render;

    void Render::specify()
    { 
        add<Player>("Player 1");
        add<Player>("Player 2");

        add<Item>("Background 1");
        add<Item>("Background 2");
        add<Item>("Background 3");
        add<Item>("Shop");
        add<Item>("Floor");
    }

    void Render::pre_draw()
    {
        for (auto& player : players)
            pre_draw_vertices(player);

        for (auto& item : items)
            pre_draw_vertices(item);
    }

    void Render::draw()
    {
        for (auto& player : players)
            draw_vertices(player);

        for (auto& item : items)
            draw_vertices(item);
    }

    void Render::cleanup_all()
    {
        for (auto& player : players)
            cleanup(player);
        players.clear();

        for (auto& item : items)
            cleanup(item);
        items.clear();
    }

    void Render::update()
    {
        pre_draw_init();
        pre_draw();
        draw();
        draw_cleanup();
        SDL_GL_SwapWindow(platform::window.application);
    }

    void Render::pre_draw_init()
    {
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_CULL_FACE);
        glEnable(GL_MULTISAMPLE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        glViewport(0, 0, platform::window.width, platform::window.height);

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void Render::vertex_cleanup()
    {
        glBindVertexArray(0);
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Render::draw_cleanup()
    {
        glBindVertexArray(0);
        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}
