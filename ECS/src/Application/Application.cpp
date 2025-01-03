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
                sf::Vector2u(
                    settings.windowSize.x,
                    settings.windowSize.y
                ),
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
        sf::Font font("assets/coucou.ttf");

        sf::Text text(font, "FPS: 0", 24);
        text.setFillColor(sf::Color::Red);
        text.setPosition(sf::Vector2f(10, 10));
        sf::Clock p_clock;

        while (p_window.isOpen()) {
            p_window.clear();
            while (auto event = p_window.pollEvent()) {
                if (event->is<sf::Event::Closed>())
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
