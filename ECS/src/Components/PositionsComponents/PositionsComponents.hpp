/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#pragma once

#include <array>
#include <cstdarg>
#include <vector>
#include <optional>
#include <glm/glm.hpp>
#include <SFML/Graphics.hpp>
#include <glm/gtc/constants.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{

    class PositionsComponents final: public AComponent {
        public:
            PositionsComponents() = default;
            ~PositionsComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
            
            static void applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center, float deltaTime = 1);
            static void applyScaleToArray(auto& array, glm::vec2& scale);
        public:
            std::vector<std::array<sf::Vector2f, 4>> m_positions;
            std::vector<glm::vec2> m_scales;
            std::vector<glm::quat> m_transforms;
            std::vector<glm::vec2> m_sizes;
    };
}
