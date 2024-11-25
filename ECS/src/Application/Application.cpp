/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "ECS/ECS.hpp"

namespace App {
    [[maybe_unused]] Application::Application(const AppSettings& settings)
    {
        p_window.create(
            sf::VideoMode(
                settings.windowSize.x,
                settings.windowSize.y,
                settings.bytePerPixel
            ),
            settings.windowTitle,
            sf::Style::Close
        );
        p_window.setFramerateLimit(settings.frameRateLimit);
    }

    Application::~Application()
    {
        if (p_window.isOpen())
            p_window.close();
    }

    void Application::run()
    {
        sf::Event event{};
        sf::Font font;

        font.loadFromFile("assets/coucou.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(10, 10);
        text.setString("FPS: 0");
        sf::Clock p_clock;

        while (p_window.isOpen()) {
            p_window.clear();
            while (p_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    p_window.close();
            }
            p_window.draw(text);
			float deltaTime = p_clock.restart().asSeconds();
            ECS::ECS::GetInstance().getSystemsManager()->Update(deltaTime);
            text.setString("FPS: " + std::to_string(1.0f / deltaTime));
            p_window.display();
        }
    }

    sf::RenderWindow &Application::getWindow()
    {
        return p_window;
    }
}
