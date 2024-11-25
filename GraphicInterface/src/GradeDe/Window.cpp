/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "GradeDe/Window.hpp"


namespace gd
{
    Window::~Window()
    {
        close();
    }


    void Window::create()
    {
        _videoMode = sf::VideoMode::getDesktopMode();
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = "GradeDe";
        _create(_fullScreenVideoMode, _title, sf::Style::Fullscreen);
    }

    void Window::create(int width, int height)
    {
        _videoMode = sf::VideoMode(width, height);
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = "GradeDe";
        _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
    }

    void Window::create(int width, int height, const std::string &title)
    {
        _videoMode = sf::VideoMode(width, height);
        _fullScreenVideoMode = sf::VideoMode(sf::VideoMode::getDesktopMode());
        _title = title;
        _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
    }


    void Window::close()
    {
        if (!_isOpen) return;
        _window.close();
        _isOpen = false;
    }

    bool Window::isOpen() const
    {
        return _isOpen;
    }


    void Window::setWidth(int width)
    {
        close();
        create(width, _videoMode.height, _title);
    }

    void Window::setHeight(int height)
    {
        close();
        create(_videoMode.width, height, _title);
    }

    void Window::setDimensions(int width, int height)
    {
        close();
        create(width, height, _title);
    }

    void Window::setDimensions(const gd::Vector2<int> &dimensions)
    {
        close();
        create(dimensions.x, dimensions.y, _title);
    }

    void Window::setTitle(const std::string &title)
    {
        _window.setTitle(title);
    }

    void Window::setFullscreen(bool fullscreen)
    {
        close();
        if (fullscreen) {
            _create(_fullScreenVideoMode, _title, sf::Style::Fullscreen);
        } else {
            _create(_videoMode, _title, sf::Style::Close | sf::Style::Titlebar);
        }
        _fullscreen = fullscreen;
    }

    bool Window::isFullscreen() const
    {
        return _fullscreen;
    }


    void Window::pollEvent(gd::Event &event)
    {
        sf::Event sfEvent;
        while (_window.pollEvent(sfEvent))
            event.handleEvent(sfEvent);
    }


    void Window::clear(gd::Color color)
    {
        _window.clear(sf::Color(color.r, color.g, color.b, color.a));
    }

    void Window::display()
    {
        _window.display();
    }


    void Window::_create(sf::VideoMode &videoMode, const std::string &title, sf::Uint32 style)
    {
        _window.create(videoMode, title, style);
        _isOpen = true;
    }


    int Window::getWidth() const
    {
        return _fullscreen ? (int)_fullScreenVideoMode.width : (int)_videoMode.width;
    }

    int Window::getHeight() const
    {
        return _fullscreen ? (int)_fullScreenVideoMode.height : (int)_videoMode.height;
    }

    gd::Vector2<int> Window::getDimensions() const
    {
        return {getWidth(), getHeight()};
    }

    std::string Window::getTitle() const
    {
        return _title;
    }

    void *Window::getWindow()
    {
        return &_window;
    }
}

