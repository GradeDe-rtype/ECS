/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.cpp
*/

#ifndef MYPROJECT_SYSTEMS_HPP
    #define MYPROJECT_SYSTEMS_HPP

    #include "ASystems.hpp"
    #include "Application/Application.hpp"

    #include <array>
    #include <memory>
    #include <SFML/Graphics.hpp>
    #define GLM_ENABLE_EXPERIMENTAL
    #include <glm/gtc/quaternion.hpp>
    #include <glm/gtc/constants.hpp>
    #include <glm/gtx/quaternion.hpp>
    

namespace ECS {

    class SystemsManager {
        public:
            enum class SystemType {
                POSITION,
				MOVEMENT,
				ROTATION,
                SPRITE,
                COUNT
            };
            SystemsManager();
            ~SystemsManager() = default;

            std::unique_ptr<ASystems> &operator[](SystemType type);
            void Update(float deltaTime);

        private:
            std::array<std::unique_ptr<ASystems>, (std::size_t)SystemType::COUNT> _systems;
    };

    class DrawSystem final : public ASystems {
        public:
            DrawSystem() = default;
            ~DrawSystem() final = default;
            void Update(float deltaTime) final;
    };  

	class MoveSystem final : public ASystems {
	    public:
		    MoveSystem() = default;
		    ~MoveSystem() final = default;
		    void Update(float deltaTime) final;
	};

	class RotateSystem final : public ASystems {
	    public:
	    	RotateSystem() = default;
	    	~RotateSystem() final = default;
	    	void Update(float deltaTime) final;
	};
} // ECS

#endif //MYPROJECT_SYSTEMS_HPP
