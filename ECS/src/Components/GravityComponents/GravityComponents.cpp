/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** GravityComponents.cpp
*/

#include "GravityComponents.hpp"
#include "ECS/ECS.hpp"

namespace ECS::Components {

    void GravityComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        double gravity = va_arg(args, double);
        va_end(args);

        m_gravity.push_back(gravity);
        IdToIndex_p[entity.id] = m_gravity.size() - 1;
        entity.componentsName.insert(typeid(GravityComponents).name());
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::GRAVITY]->AddEntity(entity);

    }

    void GravityComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        m_gravity.erase(m_gravity.begin() + index);
        IdToIndex_p.erase(entity.id);
        entity.componentsName.erase(typeid(GravityComponents).name());
    }
}
