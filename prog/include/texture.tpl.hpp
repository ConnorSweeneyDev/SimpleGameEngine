#pragma once

#include <iostream>

#include <glad/glad.h>
#include "stb_image.h"

#include "texture.hpp"

template <typename Type> void Texture::specify_texture(std::shared_ptr<Type>& object)
{
    if (object->name == "Player 1")
        object->texturePath = "assets/redhood.png";
    else if (object->name == "Player 2")
        object->texturePath = "assets/redhood.png";

    else if (object->name == "Background 1")
        object->texturePath = "assets/background1.png";
    else if (object->name == "Background 2")
        object->texturePath = "assets/background2.png";
    else if (object->name == "Background 3")
        object->texturePath = "assets/background3.png";
    else if (object->name == "Shop")
        object->texturePath = "assets/shop.png";
    else if (object->name == "Floor")
        object->texturePath = "assets/leaffloor.png";

    else
        object->texturePath = "assets/empty.png";
}

template <typename Type> void Texture::assign_texture_to_object(std::shared_ptr<Type>& object)
{
    specify_texture(object);

    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(object->texturePath.c_str(), &object->textureWidth, &object->textureHeight, &object->textureChannels, 0);
    if (!imageData)
    {
        std::cout << "Failed to load " << object->texturePath << "!" << std::endl;
        return;
    }

    if (object->name == "Player 1" || object->name == "Player 2")
    {
        int offset = 0;
        int sectionWidth = 50;
        int sectionHeight = 50;
        unsigned char* sourceImageData = imageData + (sectionWidth * offset) * 4;
        unsigned char* destinationImageData = new unsigned char[sectionWidth * sectionHeight * 4];

        for (int y = 0; y < sectionHeight; ++y) {
            for (int x = 0; x < sectionWidth; ++x) {
                int sourceIndex = (y * object->textureWidth + x) * 4;
                int destinationIndex = (y * sectionWidth + x) * 4;

                destinationImageData[destinationIndex] = sourceImageData[sourceIndex];
                destinationImageData[destinationIndex + 1] = sourceImageData[sourceIndex + 1];
                destinationImageData[destinationIndex + 2] = sourceImageData[sourceIndex + 2];
                destinationImageData[destinationIndex + 3] = sourceImageData[sourceIndex + 3];
            }
        }

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, sectionWidth, sectionHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, destinationImageData);
        delete[] destinationImageData;
    }
    else
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, object->textureWidth, object->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    }
    stbi_image_free(imageData);
}
