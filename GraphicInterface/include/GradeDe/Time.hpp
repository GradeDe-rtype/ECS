/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_TIME_SFML_HPP_
    #define GRADE_DE_TIME_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"


    /*  ---- CLASS ---- */
namespace gd
{
    class Time
    {
        public:
            Time() = default;
            ~Time() = default;

            void reset();
            int getElapsedTime();

        private:
            sf::Clock _clock;
            sf::Time _time;
    };
}

#endif /* !GRADE_DE_TIME_SFML_HPP_ */
