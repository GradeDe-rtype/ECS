/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Event.hpp"


namespace gd
{
    void Event::handleEvent(sf::Event &event)
    {
        _event = event;
        _resetValues();

        switch (_event.type) {
            case sf::Event::Closed:
                _close = true;
                break;
            case sf::Event::KeyPressed:
                _keyPressed = true;
                _setKey(_event.key.code);
                break;
            case sf::Event::MouseButtonPressed:
                _mouseButtonPressed = true;
                _mousePosition = gd::Vector2<int>(_event.mouseButton.x, _event.mouseButton.y);
                break;
            default:
                break;
        }
    }

    void Event::clear()
    {
        _resetValues();
    }


    bool Event::close() const
    {
        return _close;
    }

    bool Event::keyPressed() const
    {
        return _keyPressed;
    }

    gd::KeyBoard::Key Event::key() const
    {
        return _key;
    }

    bool Event::mouseButtonPressed() const
    {
        return _mouseButtonPressed;
    }

    gd::Vector2<int> Event::mousePosition() const
    {
        return _mousePosition;
    }


    void Event::_resetValues()
    {
        _close = false;
        _keyPressed = false;
        _key = gd::KeyBoard::Unknown;
        _mouseButtonPressed = false;
        _mousePosition = gd::Vector2<int>(-1, -1);
    }

    void Event::_setKey(sf::Keyboard::Key key)
    {
        _key = (static_cast<gd::KeyBoard::Key>(key) != gd::KeyBoard::Unknown) ?
            static_cast<gd::KeyBoard::Key>(key) : gd::KeyBoard::Unknown;
    }
}

