/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "Systems.hpp"
#include "ComponentManager/ComponentManager.hpp"
#include "ComponentManager/Components.hpp"
#include "ECS/ECS.hpp"
#include <iostream>

namespace ECS {
    SystemsManager::SystemsManager()
    {
        _systems[(std::size_t)SystemType::POSITION] = nullptr;
		_systems[(std::size_t)SystemType::MOVEMENT] = std::make_unique<MoveSystem>();
		_systems[(std::size_t)SystemType::ROTATION] = std::make_unique<RotateSystem>();
        _systems[(std::size_t)SystemType::SPRITE] = std::make_unique<DrawSystem>();
    }

    void SystemsManager::Update(float deltaTime)
    {
        std::size_t i = 0;

        for (auto &system : _systems) {
            if (system)
                system->Update(deltaTime);
            i++;
        }
    }

    std::unique_ptr<ASystems> &SystemsManager::operator[](SystemsManager::SystemType type)
    {
        return _systems[(std::size_t)type];
    }

    void DrawSystem::Update(float deltaTime)
    {
        auto &spriteComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::SpriteComponents>();
        auto &positionComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
        std::vector<std::size_t> oldValues(spriteComponent.m_vertexArray.size(), 0);

        for (auto &entity : _entities) {
            if (ECS::GetInstance().getComponentsMapper()->HasComponent<Components::SpriteComponents>(entity)) {
                auto& [texture, vertexArrayIndex] = spriteComponent.m_texture[spriteComponent.IdToIndex_p[entity.id]];
                auto& position = positionComponent.m_positions[positionComponent.IdToIndex_p[entity.id]];
                sf::VertexArray& vertexArray = spriteComponent.m_vertexArray[vertexArrayIndex];

                float texWidth = static_cast<float>(positionComponent.m_sizes[positionComponent.IdToIndex_p[entity.id]].x);
                float texHeight = static_cast<float>(positionComponent.m_sizes[positionComponent.IdToIndex_p[entity.id]].y);

                for (int i = 0; i < 4; i++)
                    vertexArray[oldValues[vertexArrayIndex] * 4 + i].position = position[i];

                vertexArray[oldValues[vertexArrayIndex] * 4].texCoords = sf::Vector2f(0.0f, 0.0f);
                vertexArray[oldValues[vertexArrayIndex] * 4 + 1].texCoords = sf::Vector2f(texWidth, 0.0f);
                vertexArray[oldValues[vertexArrayIndex] * 4 + 2].texCoords = sf::Vector2f(texWidth, texHeight);
                vertexArray[oldValues[vertexArrayIndex] * 4 + 3].texCoords = sf::Vector2f(0.0f, texHeight);
                oldValues[vertexArrayIndex]++;
            }
        }
        for (auto& [texture, index] : spriteComponent.m_texture)
            ECS::GetInstance().App->getWindow().draw(spriteComponent.m_vertexArray[index], &texture);
    }

    void MoveSystem::Update(float deltaTime)
    {
		auto &positionComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
		auto &transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();
        
        for (auto &entity : _entities) {
			if (ECS::GetInstance().getComponentsMapper()->HasComponent<Components::PositionsComponents>(entity)) {
				auto &position = positionComponent.m_positions[positionComponent.IdToIndex_p[entity.id]];
				auto &vector = transformComponent.m_positions[transformComponent.IdToIndex_p[entity.id]];

				for (int i = 0; i < 4; i++) {
					position[i].x += vector.x * deltaTime;
					position[i].y += vector.y * deltaTime;
				}
			}
		}
    }

    void RotateSystem::Update(float deltaTime)
    {
        auto& positionComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
		auto& transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();

        for (auto& entity : _entities) {
            if (ECS::GetInstance().getComponentsMapper()->HasComponent<Components::PositionsComponents>(entity)) {
                auto &position = positionComponent.m_positions[positionComponent.IdToIndex_p[entity.id]];
				auto &size = positionComponent.m_sizes[positionComponent.IdToIndex_p[entity.id]];
                sf::Vector2f center(0.0f, 0.0f);
                for (int i = 0; i < 4; ++i) {
                    center.x += position[i].x;
                    center.y += position[i].y;
                }
                center.x /= 4.0f;
                center.y /= 4.0f;

				Components::PositionsComponents::applyRotationToQuad(position, transformComponent.m_transforms[transformComponent.IdToIndex_p[entity.id]], center, deltaTime);
            }
        }
    }

} // ECS
