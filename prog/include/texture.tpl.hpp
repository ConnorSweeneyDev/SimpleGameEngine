#pragma once

#include <iostream>

#include <glad/glad.h>
#include "stb_image.h"

#include "texture.hpp"

template <typename Type> void Texture::specify_texture(std::shared_ptr<Type>& object)
{
    if (object->name == "Player 1")
        object->texture_path = "assets/redhood.png";
    else if (object->name == "Player 2")
        object->texture_path = "assets/redhood.png";

    else if (object->name == "Background 1")
        object->texture_path = "assets/background1.png";
    else if (object->name == "Background 2")
        object->texture_path = "assets/background2.png";
    else if (object->name == "Background 3")
        object->texture_path = "assets/background3.png";
    else if (object->name == "Shop")
        object->texture_path = "assets/shop.png";
    else if (object->name == "Floor")
        object->texture_path = "assets/leaffloor.png";

    else
        object->texture_path = "assets/empty.png";
}

template <typename Type> void Texture::assign_texture_to_object(std::shared_ptr<Type>& object)
{
    specify_texture(object);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* image_data = stbi_load(object->texture_path.c_str(), &object->texture_width, &object->texture_height, &object->texture_channels, 0);
    if (!image_data)
    {
        std::cout << "Failed to load " << object->texture_path << "!" << std::endl;
        return;
    }

    if (object->name == "Player 1" || object->name == "Player 2")
    {
        int offset = 0;
        int section_width = 50;
        int section_height = 50;
        unsigned char* source_image_data = image_data + (section_width * offset) * 4;
        unsigned char* destination_image_data = new unsigned char[section_width * section_height * 4];

        for (int y = 0; y < section_height; ++y)
        {
            for (int x = 0; x < section_width; ++x)
            {
                int source_index = (y * object->texture_width + x) * 4;
                int destination_index = (y * section_width + x) * 4;

                destination_image_data[destination_index] = source_image_data[source_index];
                destination_image_data[destination_index + 1] = source_image_data[source_index + 1];
                destination_image_data[destination_index + 2] = source_image_data[source_index + 2];
                destination_image_data[destination_index + 3] = source_image_data[source_index + 3];
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, section_width, section_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, destination_image_data);
        delete[] destination_image_data;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, object->texture_width, object->texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);
    }
    stbi_image_free(image_data);
}
