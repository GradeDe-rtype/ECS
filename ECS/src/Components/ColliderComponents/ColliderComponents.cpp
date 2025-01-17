/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** ColliderComponents.cpp
*/

#include "ColliderComponents.hpp"
#include "ECS/ECS.hpp"

namespace ECS::Components
{
    void ColliderComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        static std::size_t id = 0;

        va_start(args, args);
        float top = va_arg(args, double);
        float left = va_arg(args, double);
        float bottom = va_arg(args, double);
        float right = va_arg(args, double);
        char *name = va_arg(args, char *);
        va_end(args);

        m_colliders.emplace_back(entity, Hitbox{top, bottom, left, right});
        IdToIndex_p[entity.id] = m_colliders.size() - 1;
        entity.componentsName.insert(typeid(ColliderComponents).name());
        m_scripts[entity.id] = name;
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::COLLISION]->AddEntity(entity);
        id++;
    }

    void ColliderComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        m_colliders.erase(m_colliders.begin() + index);
        entity.componentsName.erase(typeid(ColliderComponents).name());
        IdToIndex_p.erase(index);
    }
}
