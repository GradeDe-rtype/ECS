/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "Components.hpp"
#include "ECS/Entity.h"
#include "ECS/ECS.hpp"
#include "ComponentManager.hpp"
#include <fstream>

namespace ECS::Components
{
    void PositionsComponents::applyRotationToQuad(auto& array, const glm::quat& rotation, const sf::Vector2f& center, float deltaTime)
    {
        const float angle = glm::angle(rotation);
        const glm::vec3 axis = glm::axis(rotation);
        const float newAngle = angle * deltaTime;
        const glm::quat updatedQuat = glm::angleAxis(newAngle, axis);
        glm::mat4 rotationMatrix = glm::toMat4(updatedQuat);

        for (int i = 0; i < 4; ++i) {
            sf::Vector2f pos = array[i];
            glm::vec4 relativePos(pos.x - center.x, pos.y - center.y, 0.0f, 1.0f);

            glm::vec4 rotatedPos = rotationMatrix * relativePos;

            array[i] = sf::Vector2f(rotatedPos.x + center.x, rotatedPos.y + center.y);
        }
    }

    void PositionsComponents::applyScaleToArray(auto& array, glm::vec2& scale, sf::Vector2f& center) 
    {
        auto& pos = array[0];

        for (auto &vertex: array) {
            vertex.x = center.x + (vertex.x - center.x) * scale.x;
            vertex.y = center.y + (vertex.y - center.y) * scale.y;
        }
    }

    void PositionsComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        sf::Vector2f pos(va_arg(args, double), va_arg(args, double));
        double degree = va_arg(args, double);
        auto axis = glm::vec3(0.0f, 0.0f, 1.0f);

        m_transforms.emplace_back(glm::angleAxis(glm::radians(static_cast<float>(degree)), axis));
        m_sizes.emplace_back(va_arg(args, double), va_arg(args, double));

        sf::Vector2f center(pos.x + m_sizes.back().x / 2, pos.y + m_sizes.back().y / 2);
        std::array<sf::Vector2f, 4> array = {
            pos,
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y),
            sf::Vector2f(pos.x + m_sizes.back().x, pos.y + m_sizes.back().y),
            sf::Vector2f(pos.x, pos.y + m_sizes.back().y)
        };
        m_scales.emplace_back(
            va_arg(args, double),
            va_arg(args, double)
        );
        applyScaleToArray(array, m_scales.back(), center);
        applyRotationToQuad(array, m_transforms.back(), center);

        m_positions.push_back(array);
        va_end(args);

        IdToIndex_p[entity.id] = m_positions.size() - 1;
        entity.componentsName.insert(typeid(PositionsComponents).name());
    }

    void PositionsComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        std::swap(m_positions[index], m_positions.back());
        std::swap(m_sizes[index], m_sizes.back());
        std::swap(m_transforms[index], m_transforms.back());
        m_positions.pop_back();
        m_sizes.pop_back();
        m_transforms.pop_back();
        entity.componentsName.erase(typeid(PositionsComponents).name());
        IdToIndex_p.erase(index);
    }

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

    void TransformComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        m_positions.emplace_back(
            va_arg(args, double),
            va_arg(args, double)
        );
        if (m_positions.back().x != 0 || m_positions.back().y != 0)
            (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::MOVEMENT]->AddEntity(entity);
        double degree = va_arg(args, double);
		if (degree != 0.0)
			(*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::ROTATION]->AddEntity(entity);
        glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
        m_transforms.emplace_back(glm::angleAxis(glm::radians(static_cast<float>(degree)), axis));
        m_scales.emplace_back(
            va_arg(args, double),
            va_arg(args, double)
        );

        va_end(args);
        IdToIndex_p[entity.id] = m_positions.size() - 1;
        entity.componentsName.insert(typeid(TransformComponents).name());

    }

    void TransformComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        std::swap(m_positions[index], m_positions.back());
        std::swap(m_scales[index], m_scales.back());
        std::swap(m_transforms[index], m_transforms.back());
        m_positions.pop_back();
        m_scales.pop_back();
        m_transforms.pop_back();
        entity.componentsName.erase(typeid(TransformComponents).name());
        IdToIndex_p.erase(index);
    }

    void ScriptComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        std::string path(va_arg(args, char *));
        lua_State *L = ECS::ECS::GetInstance().getLuaLState();
        luaL_loadfile(L, path.c_str());
        lua_getglobal(L, "Update");

        if (lua_isfunction(L, -1)) {
            int ref = luaL_ref(L, LUA_REGISTRYINDEX);
            m_scripts.emplace_back(ref);
            IdToIndex_p[entity.id] = m_scripts.size() - 1;
        } else {
            throw std::runtime_error("Failed to load script: " + path + " (Update function not found)");
        }
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::SCRIPT]->AddEntity(entity);
        entity.componentsName.insert(typeid(ScriptComponents).name());
    }

    void ScriptComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];
        lua_State *L = ECS::ECS::GetInstance().getLuaLState();
        
        luaL_unref(L, LUA_REGISTRYINDEX, m_scripts[index]);
        m_scripts.erase(m_scripts.begin() + index);
        entity.componentsName.erase(typeid(ScriptComponents).name());
        IdToIndex_p.erase(index);
    }

    int ScriptComponents::move(lua_State *L)
    {
        try {
            if (!ECS::GetInstance().getComponentsMapper()->HasComponent<Components::TransformComponents>(ECS::GetInstance().getEntity(lua_tonumber(L, 1)))) {
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::TransformComponents, double, double, double, double>(
                    ECS::GetInstance().getEntity(lua_tonumber(L, 1)),
                    ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>(),
                    0.0,
                    0.0,
                    0.0,
                    0.0
                );
            }
            TransformComponents &transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();
            transformComponent.m_positions[lua_tonumber(L, 1)] = glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
        } catch (const ECS::ECSError &e) {
            std::cerr << e.what() << std::endl;
        }
        return 0;
    }

    int ScriptComponents::rotate(lua_State *L)
    {
        try {
            if (!ECS::GetInstance().getComponentsMapper()->HasComponent<Components::TransformComponents>(ECS::GetInstance().getEntity(lua_tonumber(L, 1)))) {
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::TransformComponents, double, double, double, double>(
                    ECS::GetInstance().getEntity(lua_tonumber(L, 1)),
                    ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>(),
                    0.0,
                    0.0,
                    0.0,
                    0.0
                );
            }
            TransformComponents &transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();
            const glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
            transformComponent.m_transforms[lua_tonumber(L, 1)] = glm::angleAxis(glm::radians(static_cast<float>(lua_tonumber(L, 2))), axis);
        } catch (const ECS::ECSError &e) {
            std::cerr << e.what() << std::endl;
        }
        return 0;
    }

    int ScriptComponents::place(lua_State *L)
    {
        try {
            if (!ECS::GetInstance().getComponentsMapper()->HasComponent<Components::PositionsComponents>(ECS::GetInstance().getEntity(lua_tonumber(L, 1)))) {
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::PositionsComponents, double, double, double, double, double>(
                    ECS::GetInstance().getEntity(lua_tonumber(L, 1)),
                    ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>(),
                    0.0,
                    0.0,
                    0.0,
                    0.0,
                    0.0
                );
            }
            PositionsComponents &PositionsComponents = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
            glm::vec2 size = PositionsComponents.m_sizes[lua_tonumber(L, 1)];
            sf::Vector2f pos(lua_tonumber(L, 2), lua_tonumber(L, 3));

            std::array<sf::Vector2f, 4> array = {
                pos,
                sf::Vector2f(pos.x + size.x, pos.y),
                sf::Vector2f(pos.x + size.x, pos.y + size.y),
                sf::Vector2f(pos.x, pos.y + size.y)
            };
            PositionsComponents.m_positions[lua_tonumber(L, 1)] = array;
        } catch (const ECS::ECSError &e) {
            std::cerr << e.what() << std::endl;
        }
        return 0;
    }

    int ScriptComponents::setRotation(lua_State *L)
    {
        try {
            int entityId = lua_tonumber(L, 1);
            if (!ECS::GetInstance().getComponentsMapper()->HasComponent<Components::PositionsComponents>(ECS::GetInstance().getEntity(entityId))) {
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::PositionsComponents, double, double, double, double, double>(
                    ECS::GetInstance().getEntity(entityId),
                    ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>(),
                    0.0,
                    0.0,
                    0.0,
                    0.0,
                    0.0
                );
            }
            PositionsComponents &PositionsComponents = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
            glm::vec2 size = PositionsComponents.m_sizes[entityId];
            sf::Vector2f pos = PositionsComponents.m_positions[entityId][0];
            sf::Vector2f center(pos.x + size.x / 2, pos.y + size.y / 2);
            const glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);

            PositionsComponents.m_transforms[entityId] = glm::angleAxis(glm::radians(static_cast<float>(lua_tonumber(L, 2))), axis);
            PositionsComponents::applyRotationToQuad(PositionsComponents.m_positions[entityId], PositionsComponents.m_transforms[entityId], center);
        } catch (const ECS::ECSError &e) {
            std::cerr << e.what() << std::endl;
        }
        return 0;
    }

    void ColliderComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        static std::size_t id = 0;

        va_start(args, args);
        float top = va_arg(args, double);
        float bottom = va_arg(args, double);
        float left = va_arg(args, double);
        float right = va_arg(args, double);
        va_end(args);

        m_colliders.emplace_back(entity, Hitbox{top, bottom, left, right});
        IdToIndex_p[entity.id] = m_colliders.size() - 1;
        entity.componentsName.insert(typeid(ColliderComponents).name());
        std::string path = "collisionScript" + std::to_string(id) + ".lua";
        std::ofstream file(path);
        file << "function onCollision(entity1, entity2) end";
        file.close();
        m_index[entity.id] = id;
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::COLLISION]->AddEntity(entity);
        id++;
    }

    void ColliderComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        m_colliders.erase(m_colliders.begin() + index);
        entity.componentsName.erase(typeid(ColliderComponents).name());
        IdToIndex_p.erase(index);
    }
}
