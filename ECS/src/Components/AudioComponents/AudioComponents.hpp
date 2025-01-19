/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** AudioComponents.hpp
*/

#pragma once

#include <vector>
#include <unordered_map>
#include <SFML/Audio.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class AudioComponents final: public AComponent {
        public:
            AudioComponents() = default;
            ~AudioComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<sf::Sound> m_audio;
        private:
            std::vector<std::string> p_audioPaths;
            std::unordered_map<std::string, std::pair<sf::SoundBuffer, std::size_t>> p_alreadyLoaded;
    };
}
