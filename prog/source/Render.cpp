#include "render.hpp"
#include "window.hpp"
#include "item.hpp"
#include "player.hpp"

Render render;

void Render::SpecifyObjects()
{ 
    players.push_back(SpecifyObject<Player>("Player 1"));
    players.push_back(SpecifyObject<Player>("Player 2"));

    items.push_back(SpecifyObject<Item>("Background 1"));
    items.push_back(SpecifyObject<Item>("Background 2"));
    items.push_back(SpecifyObject<Item>("Background 3"));
    items.push_back(SpecifyObject<Item>("Shop"));
    items.push_back(SpecifyObject<Item>("Floor"));
}

void Render::PreDrawObjects()
{
    for (auto& player : players)
        PreDraw(player);

    for (auto& item : items)
        PreDraw(item);
}

void Render::DrawObjects()
{
    for (auto& player : players)
        Draw(player);

    for (auto& item : items)
        Draw(item);
}

void Render::CleanupObjects()
{
    for (auto& player : players)
        objectcleanup(player);
    players.clear();

    for (auto& item : items)
        objectcleanup(item);
    items.clear();
}

void Render::predrawinit()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glViewport(0, 0, window.getWidth(), window.getHeight());

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Render::vertexcleanup()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Render::drawcleanup()
{
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}
