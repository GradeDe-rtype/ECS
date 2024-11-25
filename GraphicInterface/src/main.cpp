/*
    Authors:
    >> Nathan TIROLF - { nathan.tirolf@epitech.eu }

    („• ֊ •„)❤  <  Have a good day !
    --U-----U------------------------
*/

/*  ---- INCLUDES ---- */
#include "RType.hpp"

float speed = 10;

/*  ---- FUNCTION ---- */
void handleEvent(gd::Window &window, gd::Event &event, gd::Shape &shape)
{
    if (event.close()) window.close();
    if (event.keyPressed()) {
        if (event.key() == gd::KeyBoard::Key::Escape) window.close();
        if (event.key() == gd::KeyBoard::Key::Up) shape.move({0, -speed});
        if (event.key() == gd::KeyBoard::Key::Down) shape.move({0, speed});
        if (event.key() == gd::KeyBoard::Key::Left) shape.move({-speed, 0});
        if (event.key() == gd::KeyBoard::Key::Right) shape.move({speed, 0});
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    gd::Window window;
    window.create(800, 600, "R-Type");
    gd::Event event;
    gd::Time time;

    gd::Shape shape({{0, 0}, {40, 0}, {40, 40}, {0, 40}});
    shape.setFillColor(gd::Color::White);
    gd::Texture texture;
    try {
        texture.loadFromFile("assets/corgi.png");
    } catch (gd::Error &error) {
        try {
            texture.loadFromFile("../assets/corgi.png");
        } catch (gd::Error &error) {
            gd::Error::read(error);
        }
    }
    shape.setTexture(texture);
    shape.setPosition({ (float)(window.getWidth() / 2 - shape.getSize().x / 2), (float)(window.getHeight() / 2 - shape.getSize().y / 2) });

    while (window.isOpen()) {
        if (time.getElapsedTime() < gd::FrameRate::get().fps()) continue;
        time.reset();
        window.pollEvent(event);
        handleEvent(window, event, shape);
        window.clear(gd::Color::Black);

        shape.draw(window);
        window.display();
    }
    window.close();
}
