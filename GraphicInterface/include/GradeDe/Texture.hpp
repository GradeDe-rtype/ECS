/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_TEXTURE_SFML_HPP_
    #define GRADE_DE_TEXTURE_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"
    #include "GradeDe/Error.hpp"

    /*  ---- CLASS ---- */
namespace gd
{
    class Texture
    {
        public:
            Texture() = default;
            ~Texture() = default;

            void loadFromFile(const std::string &path);

            void *getTexture();

        private:
            sf::Texture _texture;
    };
}

#endif /* !GRADE_DE_TEXTURE_SFML_HPP_ */
