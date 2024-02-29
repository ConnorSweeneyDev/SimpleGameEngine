#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture texture;

template <typename Type> void Texture::AssignTextureToObject(std::shared_ptr<Type>& object)
{
    stbi_set_flip_vertically_on_load(true);

    object->texturePath = "assets/" + object->name + ".png";
    if (!std::filesystem::exists(object->texturePath))
        object->texturePath = "assets/empty.png";

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
template <typename Type> float Texture::CalculateObjectWidth(std::shared_ptr<Type>& object) { return float(object->textureWidth) / float(object->textureHeight); }
template float Texture::CalculateObjectWidth<Player>(PlayerPtr& object);
template float Texture::CalculateObjectWidth<Item>(ItemPtr& object);
