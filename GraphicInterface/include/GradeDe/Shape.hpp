/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_SHAPE_SFML_HPP_
    #define GRADE_DE_SHAPE_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"
    #include "Color.hpp"
    #include "Texture.hpp"
    #include "Vector.hpp"
    #include "Window.hpp"

    /*  ---- CLASS ---- */
namespace gd
{
    class Shape
    {
        public:
            Shape(std::vector<gd::Vector2<float>> points);
            ~Shape();

            void setFillColor(gd::Color color);
            void setPosition(gd::Vector2<float> position);
            void setTexture(gd::Texture &texture);
            void move(gd::Vector2<float> offset);

            gd::Color getFillColor() const;
            gd::Vector2<float> getPosition() const;
            gd::Vector2<float> getSize() const;

            void draw(gd::Window &window);

        private:
            std::vector<gd::Vector2<float>> _points;
            gd::Color _fillColor = gd::Color::White;
            gd::Vector2<float> _position;
            sf::ConvexShape _shape;
    };
}

#endif /* !GRADE_DE_SHAPE_SFML_HPP_ */
