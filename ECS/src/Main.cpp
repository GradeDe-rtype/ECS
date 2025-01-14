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

    App::Application myApp{
        {
            sf::Vector2u(1920, 1080),
            "Hunter",
            0,
            32
        }
    };
    ECS::ECS::GetInstance().App = &myApp;

    myApp.run();
    ECS::ECS::Shutdown();
    return 0;
}
