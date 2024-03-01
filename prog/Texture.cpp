#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture texture;

template <typename Type> void Texture::AssignTextureToObject(std::shared_ptr<Type>& object)
{
    if (object->name == "Player 1")
        object->texturePath = "assets/redhood.png";
    else if (object->name == "Player 2")
        object->texturePath = "assets/redhood.png";
    else if (object->name == "Floor")
        object->texturePath = "assets/oakfloor.png";
    else if (object->name == "Background 1")
        object->texturePath = "assets/background1.png";
    else if (object->name == "Background 2")
        object->texturePath = "assets/background2.png";
    else if (object->name == "Background 3")
        object->texturePath = "assets/background3.png";
    else
        object->texturePath = "assets/empty.png";

    stbi_set_flip_vertically_on_load(true);
    unsigned char* imageData = stbi_load(object->texturePath.c_str(), &object->textureWidth, &object->textureHeight, &object->textureChannels, 0);
    if (!imageData)
    {
        std::cout << "Failed to load " << object->texturePath << "!" << std::endl;
        return;
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, object->textureWidth, object->textureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData);
    stbi_image_free(imageData);
}
template void Texture::AssignTextureToObject<Player>(PlayerPtr& object);
template void Texture::AssignTextureToObject<Item>(ItemPtr& object);
