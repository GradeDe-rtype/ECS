/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "SpriteComponents.hpp"
#include "ECS/ECS.hpp"

namespace ECS::Components
{
    void SpriteComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        std::string path(va_arg(args, char *));

        if (!_alreadyLoaded.contains(path)) {
            m_texture.emplace_back(sf::Texture(), m_vertexArray.size());
            if (!m_texture.back().first.loadFromFile(path))
                throw std::runtime_error("Failed to load texture: " + path);
            m_vertexArray.emplace_back(sf::PrimitiveType::Quads, 4);
            _alreadyLoaded.emplace(path, m_texture.size() - 1);
            IdToIndex_p[entity.id] = m_texture.size() - 1;
        } else {
			auto& vertexArray = m_vertexArray[m_texture[_alreadyLoaded[path]].second];

            IdToIndex_p[entity.id] = _alreadyLoaded[path];
            vertexArray.resize(vertexArray.getVertexCount() + 4);
        }

        entity.componentsName.insert(typeid(SpriteComponents).name());
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::SPRITE]->AddEntity(entity);
    }

    void SpriteComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];
        auto& vertexArray = m_vertexArray[m_texture[index].second];

        vertexArray.resize(vertexArray.getVertexCount() - 4);
        entity.componentsName.erase(typeid(SpriteComponents).name());
        IdToIndex_p.erase(index);
    }
}
