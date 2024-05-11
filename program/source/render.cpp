#include "rename.hpp"

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

        sdl::gl_swap_window(platform::window.application);
    }

    void Render::pre_draw_init()
    {
        gl::enable(GL_DEPTH_TEST);
        gl::disable(GL_CULL_FACE);
        gl::enable(GL_MULTISAMPLE);
        gl::enable(GL_BLEND);
        gl::blend_func(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        gl::viewport(0, 0, platform::window.width, platform::window.height);

        gl::clear_color(0.2f, 0.2f, 0.2f, 1.0f);
        gl::clear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    }

    void Render::vertex_cleanup()
    {
        gl::bind_vertex_array(0);
        gl::disable_vertex_attrib_array(0);
        gl::disable_vertex_attrib_array(1);
        gl::disable_vertex_attrib_array(2);
        gl::bind_buffer(GL_ARRAY_BUFFER, 0);
        gl::bind_buffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        gl::bind_texture(GL_TEXTURE_2D, 0);
    }

    void Render::draw_cleanup()
    {
        gl::bind_vertex_array(0);
        gl::use_program(0);
        gl::bind_texture(GL_TEXTURE_2D, 0);
    }
}
