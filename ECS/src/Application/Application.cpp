/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Application.cpp
*/

#include "Application.hpp"
#include "ECS/ECS.hpp"
#include "Components.h"
#include "ComponentManager/ComponentManager.hpp"
#include "Systems/Systems.hpp"

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
            0.0,
            0.0,
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
            0.0,
            0.0,
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

            ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::AudioComponents, char *>(
                ECS::ECS::GetInstance().getEntity(_hitId),
                (char *)"assets/shoot.ogg"
            );
            (*ECS::ECS::GetInstance().getSystemsManager())[ECS::SystemsManager::SystemType::AUDIO]->AddEntity(ECS::ECS::GetInstance().getEntity(_hitId));
            _hitterAlreadySpawn = !_hitterAlreadySpawn;
        }
    }

    void Application::launchSnook(sf::Event &event)
    {
        if (event.key.code != sf::Keyboard::Space)
                return;
        std::size_t snookId = ECS::ECS::GetInstance().AddEntity();
            
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::SpriteComponents, char *>(
        ECS::ECS::GetInstance().getEntity(snookId),
            (char *)"assets/snook.jpg"
        );
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double, double, double>(
        ECS::ECS::GetInstance().getEntity(snookId),
            2500.0,
            0.0,
            0.0,
            880.0,
            584.0,
            0.2,
            0.2
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::TransformComponents, double, double, double>(
            ECS::ECS::GetInstance().getEntity(snookId),
            -200.0,
            100.0,
            12.0
        );

        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::GravityComponents, double>(
            ECS::ECS::GetInstance().getEntity(snookId),
            36.0
        );
    }

    void Application::initHandledEvents()
    {
        ECS::ECS::GetInstance().AddEventCallBack([&](sf::Event &event) {
            spawnHit(event.mouseButton.x, event.mouseButton.y);
        }, sf::Event::MouseButtonPressed);
        ECS::ECS::GetInstance().AddEventCallBack([&](sf::Event &event) {
            ECS::ECS::GetInstance().RemoveEntity(_hitId);
            _hitterAlreadySpawn = !_hitterAlreadySpawn;
        }, sf::Event::MouseButtonReleased);
        ECS::ECS::GetInstance().AddEventCallBack([&](sf::Event &event) {
            p_window.close();
        }, sf::Event::Closed);
        ECS::ECS::GetInstance().AddEventCallBack([&](sf::Event &event) {
            launchSnook(event);
        }, sf::Event::KeyPressed);
    }

    void Application::run()
    {
        initBackground();
        initDuck();
        initHandledEvents();

        while (p_window.isOpen()) {
            ECS::ECS::GetInstance().getSystemsManager()->Update();
        }
    }

    sf::RenderWindow &Application::getWindow()
    {
        return p_window;
    }
}
