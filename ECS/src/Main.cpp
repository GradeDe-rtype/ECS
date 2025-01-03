/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Main.cpp
*/

#include "Application/Application.hpp"
#include "ECS/ECS.hpp"
#include "ComponentManager/Components.hpp"
#include "ComponentManager/ComponentManager.hpp"

int main(int argc, char *argv[])
{
    ECS::ECS::Init();
    char name[] = "assets/snook.jpg";

    for (int i = 0; i < 20; i++) {
        ECS::ECS::GetInstance().AddEntity();
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::PositionsComponents, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(i),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::PositionsComponents>(),
            100.0 + i * 5,
            0.0,
            45.0,
            584.0,
            879.0
        );
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::SpriteComponents, char*>(
            ECS::ECS::GetInstance().getEntity(i),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::SpriteComponents>(),
            name
        );
        ECS::ECS::GetInstance().getComponentsMapper()->AddComponent<ECS::Components::TransformComponents, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(i),
            ECS::ECS::GetInstance().getComponentsMapper()->GetComponent<ECS::Components::TransformComponents>(),
            0.0,
            70.0,
            -20.0,
            0.0
        );
    }

    App::Application myApp{
        {
            sf::Vector2u(1200, 800),
            "ECS Test",
            0,
            32
        }
    };
    ECS::ECS::GetInstance().App = &myApp;

    myApp.run();
    ECS::ECS::Shutdown();
    return 0;
}
