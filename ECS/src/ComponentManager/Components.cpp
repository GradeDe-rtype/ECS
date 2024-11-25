/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "Components.hpp"
#include "ECS/Entity.h"
#include "ECS/ECS.hpp"

#include <typeinfo>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/gtx/quaternion.hpp>

namespace ECS::Components
{
    void PositionsComponents::applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center)
    {
        glm::mat4 rotationMatrix = glm::toMat4(rotation);

        for (int i = 0; i < 4; ++i) {
            sf::Vector2f pos = array[i];
            glm::vec4 relativePos(pos.x - center.x, pos.y - center.y, 0.0f, 1.0f);

            glm::vec4 rotatedPos = rotationMatrix * relativePos;

            array[i] = sf::Vector2f(rotatedPos.x + center.x, rotatedPos.y + center.y);
        }
    }

    void PositionsComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        sf::Vector2f pos(va_arg(args, double), va_arg(args, double));
        double degree = va_arg(args, double);
        auto axis = glm::vec3(0.0f, 0.0f, 1.0f);

        m_transforms.emplace_back(glm::angleAxis(glm::radians(static_cast<float>(degree)), axis));
        m_sizes.emplace_back(va_arg(args, double), va_arg(args, double));

        sf::Vector2f center(pos.x + m_sizes.back().x / 2, pos.y + m_sizes.back().y / 2);
        std::array<sf::Vector2f, 4> array = {
            pos,
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y),
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y + m_sizes.back().y),
            sf::Vector2f(pos.x, pos.y + m_sizes.back().y)
        };
        applyRotationToQuad(array, m_transforms.back(), center);

        m_positions.push_back(array);
        va_end(args);

        IdToIndex_p[entity.id] = m_positions.size() - 1;
        entity.componentsName.insert(typeid(PositionsComponents).name());
    }

    void PositionsComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        std::swap(m_positions[index], m_positions.back());
        m_positions.pop_back();
        entity.componentsName.erase(typeid(PositionsComponents).name());
        IdToIndex_p.erase(index);
    }

    void SpriteComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        std::string path(va_arg(args, char *));

        if (!_alreadyLoaded.contains(path)) {
            m_texture.emplace_back(sf::Texture(), m_vertexArray.size());
            m_texture.back().first.loadFromFile(path);
            m_vertexArray.emplace_back(sf::Quads, 4);
            _alreadyLoaded.emplace(path, m_texture.size() - 1);
            IdToIndex_p[entity.id] = m_texture.size() - 1;
        } else {
			auto& vertexArray = m_vertexArray[m_texture[_alreadyLoaded[path]].second];

            IdToIndex_p[entity.id] = _alreadyLoaded[path];
            vertexArray.resize(vertexArray.getVertexCount() + 4);
        }

        entity.componentsName.insert(typeid(SpriteComponents).name());
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::SPRITE]->AddEntity(entity);
    }

    void SpriteComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        entity.componentsName.erase(typeid(PositionsComponents).name());
        IdToIndex_p.erase(index);
    }

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
        auto axis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_transforms.emplace_back(glm::angleAxis(glm::radians(static_cast<float>(degree)), axis));
        m_scales.emplace_back(va_arg(args, double));

        va_end(args);
        IdToIndex_p[entity.id] = m_positions.size() - 1;
        entity.componentsName.insert(typeid(TransformComponents).name());

    }

    void TransformComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        std::swap(m_positions[index], m_positions.back());
        std::swap(m_scales[index], m_scales.back());
        std::swap(m_transforms[index], m_transforms.back());
        m_positions.pop_back();
        m_scales.pop_back();
        m_transforms.pop_back();
        entity.componentsName.erase(typeid(TransformComponents).name());
        IdToIndex_p.erase(index);
    }
}
