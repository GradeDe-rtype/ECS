/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** AComponent.cpp
*/

#pragma once

#include <map>

#include "IComponent.hpp"

namespace ECS
{
    class AComponent: public IComponent {
        public:
            std::map<std::size_t, std::size_t> IdToIndex_p;
    };
}
