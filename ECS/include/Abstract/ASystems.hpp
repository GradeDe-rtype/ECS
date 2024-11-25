/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#ifndef MYPROJECT_ASYSTEMS_HPP
    #define MYPROJECT_ASYSTEMS_HPP

    #include <vector>
    #include <cassert>
    #include <stdexcept>
    #include <algorithm>
    #include "ISystems.hpp"

namespace ECS {
    class ASystems : public ISystems {
        public:
            ASystems() = default;
            ~ASystems() override = default;
            void AddEntity(Entity &entity) override;
            void RemoveEntity(Entity &entity) override;
        protected:
            std::vector<Entity> _entities;
    };
}

#endif //MYPROJECT_ASYSTEMS_HPP
