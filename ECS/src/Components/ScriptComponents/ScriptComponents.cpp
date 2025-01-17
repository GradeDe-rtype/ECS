/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#include "ScriptComponents.hpp"
#include "ECS/ECS.hpp"
#include "../../ComponentManager/ComponentManager.hpp"
#include "../PositionsComponents/PositionsComponents.hpp"
#include "../TransformComponents/TransformComponents.hpp"

namespace ECS::Components
{
    void ScriptComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        std::string path(va_arg(args, char *));
        lua_State *L = ECS::ECS::GetInstance().getLuaLState();
        luaL_dofile(L, path.c_str());
        lua_getglobal(L, "Update");

        if (lua_isfunction(L, -1)) {
            int ref = luaL_ref(L, LUA_REGISTRYINDEX);
            m_scripts.emplace_back(ref);
            IdToIndex_p[entity.id] = m_scripts.size() - 1;
        } else {
            throw std::runtime_error("Failed to load script: " + path + " (Update function not found)");
        }
        entity.componentsName.insert(typeid(ScriptComponents).name());
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::SCRIPT]->AddEntity(entity);
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
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::TransformComponents, double, double, double>(
                    ECS::GetInstance().getEntity(lua_tonumber(L, 1)),
                    0.0,
                    0.0,
                    0.0
                );
            }
            TransformComponents &transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();
            glm::vec2 speed = transformComponent.m_positions[transformComponent.IdToIndex_p[lua_tonumber(L, 1)]];
            if ((speed.x == 0 && speed.y == 0) && (lua_tonumber(L, 2) != 0 || lua_tonumber(L, 3) != 0))
                (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::MOVEMENT]->AddEntity(ECS::GetInstance().getEntity(lua_tonumber(L, 1)));
            else if ((speed.x != 0 || speed.y != 0) && (lua_tonumber(L, 2) == 0 && lua_tonumber(L, 3) == 0))
                (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::MOVEMENT]->RemoveEntity(ECS::GetInstance().getEntity(lua_tonumber(L, 1)));
            transformComponent.m_positions[transformComponent.IdToIndex_p[lua_tonumber(L, 1)]] = glm::vec2(lua_tonumber(L, 2), lua_tonumber(L, 3));
        } catch (const ECS::ECSError &e) {
            std::cerr << e.what() << std::endl;
        }
        return 0;
    }

    int ScriptComponents::rotate(lua_State *L)
    {
        try {
            if (!ECS::GetInstance().getComponentsMapper()->HasComponent<Components::TransformComponents>(ECS::GetInstance().getEntity(lua_tonumber(L, 1)))) {
                ECS::GetInstance().getComponentsMapper()->AddComponent<Components::TransformComponents, double, double, double>(
                    ECS::GetInstance().getEntity(lua_tonumber(L, 1)),
                    0.0,
                    0.0,
                    0.0
                );
            }
            TransformComponents &transformComponent = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::TransformComponents>();
            double angle = glm::angle(transformComponent.m_transforms[transformComponent.IdToIndex_p[lua_tonumber(L, 1)]]);
            if (lua_tonumber(L, 2) != 0 && angle == 0)
                (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::ROTATION]->AddEntity(ECS::GetInstance().getEntity(lua_tonumber(L, 1)));
            else if (angle != 0 && lua_tonumber(L, 2) == 0)
                (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::ROTATION]->RemoveEntity(ECS::GetInstance().getEntity(lua_tonumber(L, 1)));
            const glm::vec3 axis = glm::vec3(0.0f, 0.0f, 1.0f);
            transformComponent.m_transforms[transformComponent.IdToIndex_p[lua_tonumber(L, 1)]] = glm::angleAxis(glm::radians(static_cast<float>(lua_tonumber(L, 2))), axis);
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
            sf::Vector2f center(pos.x + size.x / 2, pos.y + size.y / 2);

            PositionsComponents::applyScaleToArray(array, PositionsComponents.m_scales[lua_tonumber(L, 1)]);
            PositionsComponents::applyRotationToQuad(array, PositionsComponents.m_transforms[lua_tonumber(L, 1)], center);
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

    int ScriptComponents::getPosition(lua_State *L)
    {
        int entityID = luaL_checkinteger(L, 1);
        Components::PositionsComponents &position = ECS::GetInstance().getComponentsMapper()->GetComponent<Components::PositionsComponents>();
        glm::vec2 size = position.m_sizes[entityID];
        auto& pos = position.m_positions[entityID][0];

        lua_pushnumber(L, pos.x + size.x / 2);
        lua_pushnumber(L, pos.y + size.y / 2);

        return 2;
    }
}
