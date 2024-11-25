/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Color.hpp"


namespace gd
{
    gd::Color::Color(int r, int g, int b, int a)
        : r(r), g(g), b(b), a(a)
    {
    }

    const gd::Color gd::Color::Black = gd::Color(0, 0, 0);
    const gd::Color gd::Color::White = gd::Color(255, 255, 255);
    const gd::Color gd::Color::Red = gd::Color(255, 0, 0);
    const gd::Color gd::Color::Green = gd::Color(0, 255, 0);
    const gd::Color gd::Color::Blue = gd::Color(0, 0, 255);
    const gd::Color gd::Color::Yellow = gd::Color(255, 255, 0);
    const gd::Color gd::Color::Magenta = gd::Color(255, 0, 255);
    const gd::Color gd::Color::Cyan = gd::Color(0, 255, 255);
    const gd::Color gd::Color::Transparent = gd::Color(0, 0, 0, 0);
}
