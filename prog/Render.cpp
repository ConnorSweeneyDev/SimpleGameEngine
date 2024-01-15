#include "Render.hpp"

Render render;

void Render::DefineVertices()
{ 
    PlayerPtr player;

    player = std::make_shared<Player>("Player 1");
    player->SpecifyVertices(
                                 {
                                     // Vertex 0
                                     -0.4f, -0.5f, 0.0f, // Bottom left vertex position
                                     1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                                     // Vertex 1
                                     0.4f, -0.5f, 0.0f,  // Bottom right vertex position
                                     0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                                     // Vertex 2
                                     -0.4f, 0.5f, 0.0f,  // Top left vertex position
                                     0.0f, 0.0f, 1.0f,   // Top left vertex color
                                     // Vertex 3
                                     0.4f, 0.5f, 0.0f,   // Top right vertex position
                                     1.0f, 0.0f, 0.0f    // Top right vertex color
                                 },
                                 {
                                     0, 1, 2, // first triangle
                                     3, 2, 1  // second triangle
                                 }
                                );
    players.push_back(player);

    player = std::make_shared<Player>("Player 2");
    player->SpecifyVertices(
                                 {
                                     // Vertex 0
                                     -0.4f, -0.5f, 0.0f, // Bottom left vertex position
                                     1.0f, 0.0f, 0.0f,   // Bottom left vertex color
                                     // Vertex 1
                                     0.4f, -0.5f, 0.0f,  // Bottom right vertex position
                                     0.0f, 1.0f, 0.0f,   // Bottom right vertex color
                                     // Vertex 2
                                     -0.4f, 0.5f, 0.0f,  // Top left vertex position
                                     0.0f, 0.0f, 1.0f,   // Top left vertex color
                                     // Vertex 3
                                     0.4f, 0.5f, 0.0f,   // Top right vertex position
                                     1.0f, 0.0f, 0.0f    // Top right vertex color
                                 },
                                 {
                                     0, 1, 2, // first triangle
                                     3, 2, 1  // second triangle
                                 }
                                );
    players.push_back(player);    
}

void Render::predrawinit()
{
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(
               0,
               0,
               window.getWidth(),
               window.getHeight()
              );
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Render::vertexcleanup()
{
    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
void Render::drawcleanup()
{
    glBindVertexArray(0);
    glUseProgram(0);
}
