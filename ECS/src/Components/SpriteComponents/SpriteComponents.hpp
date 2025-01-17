/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#pragma once

#include <cstdarg>
#include <vector>
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

#include "AComponent.hpp"

namespace ECS::Components
{
    class SpriteComponents final: public AComponent {
        public:
            SpriteComponents() = default;
            ~SpriteComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<sf::VertexArray> m_vertexArray;
            std::vector<std::pair<sf::Texture, std::size_t>> m_texture;
        private:
            std::unordered_map<std::string, std::size_t> _alreadyLoaded;
    };
}
