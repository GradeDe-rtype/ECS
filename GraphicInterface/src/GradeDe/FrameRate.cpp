/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/FrameRate.hpp"


namespace gd
{
    FrameRate &FrameRate::get()
    {
        static FrameRate instance;
        return instance;
    }

    int FrameRate::fps() const
    {
        return 1000 / _frameRate;
    }

    void FrameRate::setFrameRate(int frameRate)
    {
        if (frameRate < 1) frameRate = 1;
        _frameRate = frameRate;
    }

    int FrameRate::getFrameRate() const
    {
        return _frameRate;
    }
}
