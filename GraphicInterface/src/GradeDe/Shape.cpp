/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Shape.hpp"


namespace gd
{
    Shape::Shape(std::vector<gd::Vector2<float>> points)
        : _position({0, 0})
    {
        _points = points;
        _shape.setPointCount(points.size());
        for (size_t i = 0; i < points.size(); i++)
            _shape.setPoint(i, sf::Vector2f(points[i].x, points[i].y));
        _shape.setPosition(_position.x, _position.y);
    }

    Shape::~Shape()
    {
    }

    void Shape::setFillColor(gd::Color color)
    {
        _fillColor = color;
        _shape.setFillColor(sf::Color(color.r, color.g, color.b, color.a));
    }

    void Shape::setPosition(gd::Vector2<float> position)
    {
        _position = position;
        _shape.setPosition(position.x, position.y);
    }

    void Shape::setTexture(gd::Texture &texture)
    {
        _shape.setTexture((sf::Texture *)texture.getTexture());
    }

    void Shape::move(gd::Vector2<float> offset)
    {
        _position += offset;
        _shape.move(offset.x, offset.y);
    }


    gd::Color Shape::getFillColor() const
    {
        return _fillColor;
    }

    gd::Vector2<float> Shape::getPosition() const
    {
        return _position;
    }

    gd::Vector2<float> Shape::getSize() const
    {
        auto bounds = _shape.getGlobalBounds();
        return {bounds.width, bounds.height};
    }


    void Shape::draw(gd::Window &window)
    {
        sf::RenderWindow *win = (sf::RenderWindow *)window.getWindow();
        win->draw(_shape);
    }
}
