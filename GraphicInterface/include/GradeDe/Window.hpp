/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

#ifndef GRADE_DE_WINDOW_SFML_HPP_
    #define GRADE_DE_WINDOW_SFML_HPP_

    /*  ---- INCLUDES ---- */
    #include "GradeDe/Includes.hpp"
    #include "GradeDe/Event.hpp"
    #include "GradeDe/Color.hpp"
    #include "GradeDe/Vector.hpp"


    /*  ---- CLASS ---- */
namespace gd
{
    class Window
    {
        public:
            Window() = default;
            ~Window();

            void create();
            void create(int width, int height);
            void create(int width, int height, const std::string &title);

            void close();
            bool isOpen() const;

            void setWidth(int width);
            void setHeight(int height);
            void setDimensions(int width, int height);
            void setDimensions(const gd::Vector2<int> &dimensions);
            void setTitle(const std::string &title);
            void setFullscreen(bool fullscreen);
            bool isFullscreen() const;

            void pollEvent(gd::Event &event);

            void clear(gd::Color color = gd::Color::Black);

            void display();

            int getWidth() const;
            int getHeight() const;
            gd::Vector2<int> getDimensions() const;
            std::string getTitle() const;
            void *getWindow();

        private:
            sf::RenderWindow _window;
            sf::VideoMode _videoMode;
            sf::VideoMode _fullScreenVideoMode;
            std::string _title;
            bool _isOpen = false;
            bool _fullscreen = false;

            void _create(sf::VideoMode &videoMode, const std::string &title, sf::Uint32 style);
    };
}

#endif /* !GRADE_DE_WINDOW_SFML_HPP_ */
