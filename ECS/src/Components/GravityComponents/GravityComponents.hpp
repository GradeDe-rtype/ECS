/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** GravityComponents.hpp
*/

#pragma once

#include "AComponent.hpp"

#include <typeinfo>
#include <vector>

namespace ECS::Components {

    class GravityComponents : public AComponent {
        public:
            GravityComponents() = default;
            ~GravityComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<double> m_gravity;
    };
}
