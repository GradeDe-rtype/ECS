/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Time.hpp"


namespace gd
{
    void Time::reset()
    {
        _clock.restart();
        _time = _clock.getElapsedTime();
    }

    int Time::getElapsedTime()
    {
        _time = _clock.getElapsedTime();
        int elapsedTime = _time.asMilliseconds();
        return elapsedTime;
    }
}
