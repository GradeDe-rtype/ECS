/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#include "ASystems.hpp"
#include <iostream>

namespace ECS {
    void ASystems::AddEntity(Entity &entity)
    {
        _entities.push_back(entity);
    }

    void ASystems::RemoveEntity(Entity &entity)
    {
        auto it = std::find_if(_entities.begin(), _entities.end(), [&entity](const Entity &e) {
            return e.id == entity.id;
        });

        if (it != _entities.end()) {
            std::swap(_entities[entity.id], _entities.back());
            _entities.pop_back();
        } else {
            throw std::runtime_error("Entity not found");
        }
    }
}
