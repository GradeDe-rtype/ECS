/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** ComponentMapper.cpp
*/

#include "ComponentManager.hpp"
#include "Components.hpp"

namespace ECS
{
    ComponentsManager::ComponentsManager()
    {
        RegisterComponent<Components::PositionsComponents>();
        RegisterComponent<Components::SpriteComponents>();
		RegisterComponent<Components::TransformComponents>();
    }
}
