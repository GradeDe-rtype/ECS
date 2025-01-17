/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#pragma once

#include <cstdarg>
#include <vector>
#include <optional>
#include <string>
#include <unordered_map>
#include <SFML/Graphics.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class TextComponents final: public AComponent {
        public:
            TextComponents() = default;
            ~TextComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<sf::Text> m_texts;
        private:
            std::vector<std::optional<std::string>> p_fontsNames;
            std::unordered_map<std::string, std::pair<sf::Font, std::size_t>> p_alreadyLoaded;
    };
}
