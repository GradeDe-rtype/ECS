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
		RegisterComponent<Components::ScriptComponents>();
		RegisterComponent<Components::ColliderComponents>();
        RegisterComponent<Components::TextComponents>();
    }

    void ComponentsManager::RemoveAllComponents(Entity& entity)
    {
        assert(ECS::GetInstance().HasEntity(entity));

        for (auto &i: entity.componentsName)
			p_registeredComponents[i]->RemoveFromEntity(entity);
    }
}
