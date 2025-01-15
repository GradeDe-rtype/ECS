/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "ECS/ECS.hpp"
#include "ComponentManager/ComponentManager.hpp"
#include "ComponentManager/Components.hpp"

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
        p_window.setPosition(sf::Vector2i(0, 0));
        p_window.setFramerateLimit(settings.frameRateLimit);
    }

    Application::~Application()
    {
        if (p_window.isOpen())
            p_window.close();
    }

    void Application::initBackground() 
    {
        std::size_t bgId = ECS::ECS::GetInstance().AddEntity();

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::SpriteComponents, char *>(
            ECS::ECS::GetInstance().getEntity(bgId),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::SpriteComponents>(),
            (char *)"assets/background.png"
        );
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(bgId),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::PositionsComponents>(),
            0.0,
            0.0,
            0.0,
            1080.0,
            1920.0,
            1.0,
            1.0
        );
    }

    void Application::initDuck()
    {
        std::size_t duckId = ECS::ECS::GetInstance().AddEntity();

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::SpriteComponents, char *>(
            ECS::ECS::GetInstance().getEntity(duckId),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::SpriteComponents>(),
            (char *)"assets/duck.png"
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(duckId),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::PositionsComponents>(),
            -200.0,
            -270.0,
            0.0,
            500.0,
            500.0,
            0.2,
            0.2
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::ScriptComponents>(
            ECS::ECS::GetInstance().getEntity(duckId),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::ScriptComponents>(),
            (char *)"src/script.lua"
        );
    }

    void Application::run()
    {
        sf::Clock p_clock;
        sf::Event event;
        
        initBackground();
        initDuck();
        while (p_window.isOpen()) {
            p_window.clear();
            while (p_window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    p_window.close();
            }
			float deltaTime = p_clock.restart().asSeconds();
            ECS::ECS::GetInstance().getSystemsManager()->Update(deltaTime);
            p_window.display();
        }
    }

    sf::RenderWindow &Application::getWindow()
    {
        return p_window;
    }
}
