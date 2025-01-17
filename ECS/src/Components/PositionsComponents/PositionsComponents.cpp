/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "PositionsComponents.hpp"

namespace ECS::Components
{
    void PositionsComponents::applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center, float deltaTime)
    {
        const float angle = glm::angle(rotation);
        const glm::vec3 axis = glm::axis(rotation);
        const float newAngle = angle * deltaTime;
        const glm::quat updatedQuat = glm::angleAxis(newAngle, axis);
        glm::mat4 rotationMatrix = glm::toMat4(updatedQuat);

        for (int i = 0; i < 4; ++i) {
            sf::Vector2f pos = array[i];
            glm::vec4 relativePos(pos.x - center.x, pos.y - center.y, 0.0f, 1.0f);

            glm::vec4 rotatedPos = rotationMatrix * relativePos;

            array[i] = sf::Vector2f(rotatedPos.x + center.x, rotatedPos.y + center.y);
        }
    }

    void PositionsComponents::applyScaleToArray(auto& array, glm::vec2& scale) 
    {
        for (auto &vertex: array) {
            vertex.x *= scale.x;
            vertex.y *= scale.y;
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
        m_scales.emplace_back(
            va_arg(args, double),
            va_arg(args, double)
        );

        sf::Vector2f center(pos.x + m_sizes.back().x / 2, pos.y + m_sizes.back().y / 2);
        std::array<sf::Vector2f, 4> array = {
            pos,
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y),
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y + m_sizes.back().y),
            sf::Vector2f(pos.x, pos.y + m_sizes.back().y)
        };
        applyScaleToArray(array, m_scales.back());
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
        std::swap(m_sizes[index], m_sizes.back());
        std::swap(m_transforms[index], m_transforms.back());
        m_positions.pop_back();
        m_sizes.pop_back();
        m_transforms.pop_back();
        entity.componentsName.erase(typeid(PositionsComponents).name());
        IdToIndex_p.erase(index);
    }
}
