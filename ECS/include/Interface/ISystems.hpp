//
// Created by Hardeol on 07/11/2024.
//

#ifndef MYPROJECT_ISYSTEMS_HPP
    #define MYPROJECT_ISYSTEMS_HPP

    #include "ECS/Entity.h"

namespace ECS {
    class ISystems {
        public:
            virtual ~ISystems() = default;
            virtual void AddEntity(Entity &entity) = 0;
            virtual void RemoveEntity(Entity &entity) = 0;
            virtual void Update(float deltaTime) = 0;
    };
} // ECS

#endif //MYPROJECT_ISYSTEMS_HPP
