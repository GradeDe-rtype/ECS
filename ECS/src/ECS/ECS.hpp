/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** ECS.hpp
*/

#pragma once

#include <cassert>
#include <vector>
#include <string>
#include <memory>
#include <lua.hpp>

#include "ECS/Entity.h"
#include "Application/Application.hpp"
#include "Systems/Systems.hpp"

namespace ECS
{
    class ComponentsManager;

    class ECS {
        public:
            class ECSError : public std::exception {
                public:
                    explicit ECSError(std::string msg);
                    [[nodiscard]] const char *what() const noexcept override;
                private:
                    std::string p_msg;
            };

            enum class RunningState {
                RELEASE,
                DEBUG
            };

            ECS(const ECS &) = delete;
            ECS &operator = (const ECS &) = delete;

            static void Init(RunningState state = RunningState::RELEASE);
            static void Shutdown();
            static ECS &GetInstance();

            std::size_t AddEntity();
            void RemoveEntity(std::size_t id);
            [[nodiscard]] bool HasEntity(const Entity& entity) const;
            [[nodiscard]] Entity &getEntity(std::size_t id);
            [[nodiscard]] std::shared_ptr<ComponentsManager> getComponentsMapper();
            [[nodiscard]] std::shared_ptr<SystemsManager> getSystemsManager();
            [[nodiscard]] lua_State *getLuaLState();
            [[nodiscard]] sf::Font &getBasicFont();
            [[nodiscard]] std::size_t getFpsTextId();
            [[maybe_unused]] void RemoveEntity(const Entity &entity);
            [[maybe_unused]] void PrintEntities() const; // * Use for debug
        public:
            std::unique_ptr<App::Application> App;
            const RunningState runningState;
        private:
            ECS(RunningState state);
            ~ECS();

            void initFpsText();
        private:
            std::size_t p_fpsTextId;
            sf::Font p_basicFont;
            std::vector<Entity> p_entities;
            std::shared_ptr<SystemsManager> p_systemsManager;
            std::shared_ptr<ComponentsManager> p_componentsMapper;
            lua_State *p_luaState;
    };
} // namespace ECS
