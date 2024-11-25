/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_EVENT_SFML_HPP_
    #define GRADE_DE_EVENT_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"
    #include "GradeDe/KeyBoard.hpp"
    #include "GradeDe/Vector.hpp"


    /*  ---- CLASS ---- */
namespace gd
{
    class Event
    {
        public:
            Event() = default;
            ~Event() = default;

            void handleEvent(sf::Event &event);
            void clear();

            bool close() const;
            bool keyPressed() const;
            gd::KeyBoard::Key key() const;
            bool mouseButtonPressed() const;
            gd::Vector2<int> mousePosition() const;

        private:
            sf::Event _event;
            bool _close = false;
            bool _keyPressed = false;
            gd::KeyBoard::Key _key = gd::KeyBoard::Unknown;
            bool _mouseButtonPressed = false;
            gd::Vector2<int> _mousePosition = gd::Vector2<int>(0, 0);

            void _resetValues();
            void _setKey(sf::Keyboard::Key key);
    };
}

#endif /* !GRADE_DE_EVENT_SFML_HPP_ */
