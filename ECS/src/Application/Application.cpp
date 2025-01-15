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
            (char *)"assets/background.png"
        );
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(bgId),
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
            (char *)"assets/duck.png"
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(duckId),
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
            (char *)"src/script.lua"
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::ColliderComponents, double, double, double, double, char *> (
            ECS::ECS::GetInstance().getEntity(duckId),
            -200.0, //TODO @LO: this is moving
            -270.0,
            500.0 * 0.2,
            500.0 * 0.2,
            (char *)"src/script.lua"
        );
    }

    void Application::spawnHit(int x, int y)
    {
        if (!_hitterAlreadySpawn) {
            _hitId = ECS::ECS::GetInstance().AddEntity();
            ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double, double, double> (
                ECS::ECS::GetInstance().getEntity(_hitId),
                static_cast<double>(y),
                static_cast<double>(x),
                0.0,
                10.0,
                10.0,
                1.0,
                1.0
            );

            ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::ColliderComponents, double, double, double, double, char *> (
                ECS::ECS::GetInstance().getEntity(_hitId),
                static_cast<double>(y),
                static_cast<double>(x),
                10.0,
                10.0,
                nullptr
            );
            std::cout << "Hitter spawned !" << std::endl;
            _hitterAlreadySpawn = !_hitterAlreadySpawn;
        }
    }

    void Application::pollEvent()
    {
        sf::Event event;

        while (p_window.pollEvent(event)) {
            auto pos = sf::Mouse::getPosition();

            switch (event.type) {
                case sf::Event::Closed:
                    p_window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    spawnHit(pos.x, pos.y);
                    break;
                case sf::Event::MouseButtonReleased:
                    ECS::ECS::GetInstance().RemoveEntity(_hitId);
                    _hitterAlreadySpawn = !_hitterAlreadySpawn;
                    break;
                default:
                    break;
            }
        }
    }

    void Application::run()
    {
        sf::Clock p_clock;
        
        initBackground();
        initDuck();
        while (p_window.isOpen()) {
            p_window.clear();
            pollEvent();
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
