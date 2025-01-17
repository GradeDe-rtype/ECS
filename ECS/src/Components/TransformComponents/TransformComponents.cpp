/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** TransformComponents.cpp
*/

#include "TransformComponents.hpp"
#include "ECS/ECS.hpp"

namespace ECS::Components
{
    void TransformComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        m_positions.emplace_back(
            va_arg(args, double),
            va_arg(args, double)
        );
        if (m_positions.back().x != 0 || m_positions.back().y != 0)
            (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::MOVEMENT]->AddEntity(entity);
        double degree = va_arg(args, double);
		if (degree != 0.0)
			(*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::ROTATION]->AddEntity(entity);
        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_transforms.emplace_back(glm::angleAxis(glm::radians(static_cast<float>(degree)), axis));

        va_end(args);
        IdToIndex_p[entity.id] = m_positions.size() - 1;
        entity.componentsName.insert(typeid(TransformComponents).name());

    }

    void TransformComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        std::swap(m_positions[index], m_positions.back());
        std::swap(m_transforms[index], m_transforms.back());
        m_positions.pop_back();
        m_transforms.pop_back();
        entity.componentsName.erase(typeid(TransformComponents).name());
        IdToIndex_p.erase(index);
    }
}
