/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#pragma once

#include <vector>
#include <unordered_map>

#include "AComponent.hpp"

namespace ECS::Components
{
    class ColliderComponents final: public AComponent {
        public:
            struct Hitbox {
                float top;
                float height;
                float left;
                float width;
            };

            ColliderComponents() = default;
            ~ColliderComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<std::pair<Entity, Hitbox>> m_colliders;
            std::unordered_map<std::size_t, char *> m_scripts;
    };
}
