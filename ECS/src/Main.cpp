/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Main.cpp
*/

#include "Application/Application.hpp"
#include "ECS/ECS.hpp"
#include "ComponentManager/ComponentManager.hpp"

int main(int argc, char *argv[])
{
    ECS::ECS::Init(ECS::ECS::RunningState::DEBUG);

    ECS::ECS::GetInstance().App = std::make_unique<App::Application>(App::Application::AppSettings
        {
            sf::Vector2u(1280, 720),
            "Hunter",
            0,
            32
        }
    );

    ECS::ECS::GetInstance().App->run();
    ECS::ECS::Shutdown();
    return 0;
}
