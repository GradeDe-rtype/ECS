/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_FRAMERATE_SFML_HPP_
    #define GRADE_DE_FRAMERATE_SFML_HPP_

    /*  ---- INCLUDES ---- */

    /*  ---- CLASS ---- */
namespace gd
{
    class FrameRate
    {
        public:
            ~FrameRate() = default;

            static FrameRate &get();
            int fps() const;

            void setFrameRate(int frameRate);
            int getFrameRate() const;

        private:
            FrameRate() = default;
            int _frameRate = 24;
            static FrameRate &_instance;
    };
}

#endif /* !GRADE_DE_FRAMERATE_SFML_HPP_ */
