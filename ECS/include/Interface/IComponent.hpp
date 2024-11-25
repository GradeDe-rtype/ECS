/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** IComponent.hpp
*/

#pragma once

#include "ECS/Entity.h"
#include <cstdarg>

namespace ECS
{
    class IComponent {
        public:
            virtual ~IComponent() = default;
            virtual void AddToEntity(Entity &entity, va_list args, ...) = 0;
            virtual void RemoveFromEntity(Entity &entity) = 0;
    };
}
