/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** ECS.cpp
*/

#include "ECS.hpp"
#include "ComponentManager/ComponentManager.hpp"
#include "Components/Components.h"

#include <iostream>
#include <utility>

namespace ECS
{
    ECS::ECSError::ECSError(std::string msg) : p_msg(std::move(msg))
    {}

    const char* ECS::ECSError::what() const noexcept
    {
        return p_msg.c_str();
    }

    static ECS *s_Instance = nullptr;

    void ECS::Init(RunningState state)
    {
        assert(!s_Instance);

        s_Instance = new ECS(state);
        if (s_Instance->runningState == RunningState::DEBUG)
            s_Instance->initFpsText();
    }

    void ECS::Shutdown()
    {
        assert(s_Instance);

        delete s_Instance;
        s_Instance = nullptr;
    }

    ECS &ECS::GetInstance()
    {
        assert(s_Instance);

        return *s_Instance;
    }

    void ECS::initFpsText()
    {
        p_fpsTextId = ECS::ECS::GetInstance().AddEntity();
        p_componentsMapper->AddComponent<Components::PositionsComponents, double, double, double, double, double, double, double>(
            ECS::ECS::GetInstance().getEntity(p_fpsTextId),
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0,
            0.0
        );
        p_componentsMapper->AddComponent<Components::TextComponents, char *, char *>(
            ECS::ECS::GetInstance().getEntity(p_fpsTextId),
            (char *)"FPS: ",
            (char *)"assets/coucou.ttf",
            13
        );
    }

    std::size_t ECS::AddEntity()
    {
        static std::size_t id = 0;

        p_entities.push_back({
            .id=id,
            .componentsName={}
        });
        return id++;
    }

    void ECS::RemoveEntity(std::size_t id)
    {
        auto it = p_entities.begin();

        for (; it != p_entities.end(); ++it) {
            if (it->id == id)
                break;
        }
        if (it == p_entities.end())
            throw ECSError("Entity with ID = " + std::to_string(id) + " does not exist");
		p_componentsMapper->RemoveAllComponents(*it);
        p_entities.erase(it);
    }

    [[maybe_unused]] void ECS::RemoveEntity(const Entity &entity)
    {
        auto it = p_entities.begin();

        for (; it != p_entities.end(); ++it) {
            if (it->id == entity.id)
                break;
        }
        if (it == p_entities.end())
            throw ECSError("Entity with ID = " + std::to_string(entity.id) + " does not exist");
        p_componentsMapper->RemoveAllComponents(*it);
        p_entities.erase(it);
    }

    bool ECS::HasEntity(const Entity& entity) const
    {
        auto it = p_entities.begin();

        for (; it != p_entities.end(); ++it) {
            if (it->id == entity.id)
                break;
        }
        return it != p_entities.end();
    }

    [[maybe_unused]] void ECS::PrintEntities() const
    {
        for (const auto &entity : p_entities)
            std::cout << entity.id << std::endl;
    }

    void ECS::AddEventCallBack(std::function<void(sf::Event &)> callback, sf::Event::EventType eventType)
    {
        p_eventCallBacks[eventType] = callback;
    }

    std::optional<std::function<void(sf::Event &)>> ECS::getEventCallBacks(sf::Event::EventType eventType) const
    {
        if (p_eventCallBacks.contains(eventType))
            return p_eventCallBacks.at(eventType);
        return std::nullopt;
    }

    Entity &ECS::getEntity(std::size_t id)
    {
        for (auto &entity : p_entities) {
            if (entity.id == id)
                return entity;
        }
        throw ECSError("Entity with ID = " + std::to_string(id) + " does not exist");
    }

    std::shared_ptr<ComponentsManager> ECS::getComponentsMapper()
    {
        return p_componentsMapper;
    }

    std::shared_ptr<SystemsManager> ECS::getSystemsManager() {
        return p_systemsManager;
    }

    lua_State *ECS::getLuaLState()
    {
        return p_luaState;
    }

    sf::Font ECS::getBasicFont() const
    {
        return p_basicFont;
    }

    std::size_t ECS::getFpsTextId() const
    {
        return p_fpsTextId;
    }

    ECS::ECS(RunningState state) : runningState(state)
    {
        p_luaState = luaL_newstate();
        luaL_openlibs(p_luaState);
        lua_checkstack(p_luaState, 100);

        lua_register(p_luaState, "move", Components::ScriptComponents::move);
        lua_register(p_luaState, "rotate", Components::ScriptComponents::rotate);
        lua_register(p_luaState, "place", Components::ScriptComponents::place);
        lua_register(p_luaState, "setRotation", Components::ScriptComponents::setRotation);
        lua_register(p_luaState, "getPosition", Components::ScriptComponents::getPosition);
        p_componentsMapper = std::make_shared<ComponentsManager>();
        p_systemsManager = std::make_shared<SystemsManager>();
        p_basicFont.loadFromFile("assets/coucou.ttf");
    }

    ECS::~ECS()
    {
        lua_close(p_luaState);
    }
}
