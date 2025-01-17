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
#include <typeinfo>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <glm/gtc/constants.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>
#include <lua.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class PositionsComponents final: public AComponent {
        public:
            PositionsComponents() = default;
            ~PositionsComponents() override = default;

            void AddToEntity(Entity &entity, va_list args, ...) override;
            void RemoveFromEntity(Entity &entity) override;
            
            static void applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center, float deltaTime = 1);
            static void applyScaleToArray(auto& array, glm::vec2& scale);
        public:
            std::vector<std::array<sf::Vector2f, 4>> m_positions;
            std::vector<glm::vec2> m_scales;
            std::vector<glm::quat> m_transforms;
            std::vector<glm::vec2> m_sizes;
    };

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

	class ScriptComponents final: public AComponent {
	    public:
	    	ScriptComponents() = default;
	    	~ScriptComponents() override = default;

	    	void AddToEntity(Entity& entity, va_list args, ...) override;
	    	void RemoveFromEntity(Entity& entity) override;
        
            static int move(lua_State *L);
            static int rotate(lua_State *L);
            static int setRotation(lua_State *L);
            static int place(lua_State *L);
            static int getPosition(lua_State *L);
        public:
            std::vector<int> m_scripts;
    };

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
} // namespace ECS::Components
