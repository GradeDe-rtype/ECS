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

            void AddEntity();
            void RemoveEntity(std::size_t id);
            [[nodiscard]] bool HasEntity(const Entity& entity) const;
            [[nodiscard]] Entity &getEntity(std::size_t id);
            [[nodiscard]] std::shared_ptr<ComponentsManager> getComponentsMapper();
            [[nodiscard]] std::shared_ptr<SystemsManager> getSystemsManager();
            [[maybe_unused]] void RemoveEntity(const Entity &entity);

            [[maybe_unused]] void PrintEntities() const; // * Use for debug
        public:
            App::Application *App = nullptr;
        private:
            ECS();
            ~ECS() = default;
        private:
            std::vector<Entity> p_entities;
            std::shared_ptr<SystemsManager> p_systemsManager;
            std::shared_ptr<ComponentsManager> p_componentsMapper;
    };
}
