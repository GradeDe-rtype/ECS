/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#pragma once

#include <cstdarg>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class TransformComponents final: public AComponent {
        public:
            TransformComponents() = default;
            ~TransformComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<glm::vec2> m_positions;
            std::vector<glm::quat> m_transforms;
    };
}
