/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Texture.hpp"


namespace gd
{
    void Texture::loadFromFile(const std::string &path)
    {
        std::ifstream file(path);
        if (!file.is_open())
            throw Error("Texture file not found \"" + path + "\"", "Texture::Texture");
        _texture.loadFromFile(path);
    }

    void *Texture::getTexture()
    {
        return &_texture;
    }
}
