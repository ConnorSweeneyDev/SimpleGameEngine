#include "render.hpp"
#include "window.hpp"
#include "item.hpp"
#include "player.hpp"

Render render;

void Render::specify_objects()
{ 
    add_object<Player>("Player 1");
    add_object<Player>("Player 2");

    add_object<Item>("Background 1");
    add_object<Item>("Background 2");
    add_object<Item>("Background 3");
    add_object<Item>("Shop");
    add_object<Item>("Floor");
}

void Render::pre_draw_objects()
{
    for (auto& player : players)
        pre_draw(player);

    for (auto& item : items)
        pre_draw(item);
}

void Render::draw_objects()
{
    for (auto& player : players)
        draw(player);

    for (auto& item : items)
        draw(item);
}

void Render::cleanup_objects()
{
    for (auto& player : players)
        object_cleanup(player);
    players.clear();

    for (auto& item : items)
        object_cleanup(item);
    items.clear();
}

void Render::pre_draw_init()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, window.get_width(), window.get_height());

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
