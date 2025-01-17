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

            ECS(const ECS &) = delete;
            ECS &operator = (const ECS &) = delete;

            static void Init();
            static void Shutdown();
            static ECS &GetInstance();

            std::size_t AddEntity();
            void RemoveEntity(std::size_t id);
            [[nodiscard]] bool HasEntity(const Entity& entity) const;
            [[nodiscard]] Entity &getEntity(std::size_t id);
            [[nodiscard]] std::shared_ptr<ComponentsManager> getComponentsMapper();
            [[nodiscard]] std::shared_ptr<SystemsManager> getSystemsManager();
            [[nodiscard]] lua_State *getLuaLState();
            [[maybe_unused]] void RemoveEntity(const Entity &entity);

            [[maybe_unused]] void PrintEntities() const; // * Use for debug
        public:
            std::unique_ptr<App::Application> App;
        private:
            ECS();
            ~ECS();
        private:
            std::vector<Entity> p_entities;
            std::shared_ptr<SystemsManager> p_systemsManager;
            std::shared_ptr<ComponentsManager> p_componentsMapper;
            lua_State *p_luaState;
    };
} // namespace ECS
