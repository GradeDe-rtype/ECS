/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#pragma once

#include <cstdarg>
#include <vector>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class PositionsComponents: public AComponent {
        public:
            PositionsComponents() = default;
            ~PositionsComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
            static void applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center, float deltaTime = 1);
        public:
            std::vector<std::array<sf::Vector2f, 4>> m_positions;
            std::vector<float> m_scales;
            std::vector<glm::quat> m_transforms;
            std::vector<glm::vec2> m_sizes;
    };

    class SpriteComponents: public AComponent {
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

    class TransformComponents: public AComponent {
        public:
            TransformComponents() = default;
            ~TransformComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
        public:
            std::vector<glm::vec2> m_positions;
            std::vector<double> m_scales;
            std::vector<glm::quat> m_transforms;
    };

	class ScriptComponents : public AComponent {
	    public:
	    	ScriptComponents() = default;
	    	~ScriptComponents() override = default;

	    	void AddToEntity(Entity& entity, va_list args, ...) override;
	    	void RemoveFromEntity(Entity& entity) override;
	    public:
	    	std::vector<std::function<void(Entity& entity)>> m_scripts;
	};

} // namespace ECS::Components
