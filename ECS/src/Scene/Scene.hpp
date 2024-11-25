/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Scene.hpp
*/

#pragma once

#include <cassert>
#include <cstddef>

namespace ECS
{
    class Scene {
        public:
            enum class PreExistingEntity: std::size_t {
                Camera = 0,
                NbPreExistingEntities
            };

            Scene() = default;
            ~Scene() = default;
            /*void AddEntity();
            void RemoveEntity();*/
    };
}
