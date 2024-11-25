/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_COLOR_SFML_HPP_
    #define GRADE_DE_COLOR_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"

    /*  ---- CLASS ---- */
namespace gd
{
    class Color
    {
        public:
            Color(int r, int g, int b, int a = 255);
            ~Color() = default;

            int r;
            int g;
            int b;
            int a;

            static const gd::Color Black;
            static const gd::Color White;
            static const gd::Color Red;
            static const gd::Color Green;
            static const gd::Color Blue;
            static const gd::Color Yellow;
            static const gd::Color Magenta;
            static const gd::Color Cyan;
            static const gd::Color Transparent;
    };
}

#endif /* !GRADE_DE_COLOR_SFML_HPP_ */
