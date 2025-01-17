/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** Components.hpp
*/

#pragma once

#include <cstdarg>
#include <vector>
#include <lua.hpp>

#include "AComponent.hpp"

namespace ECS::Components
{
    class ScriptComponents final: public AComponent {
	    public:
	    	ScriptComponents() = default;
	    	~ScriptComponents() override = default;

	    	void AddToEntity(Entity& entity, va_list args, ...) override;
	    	void RemoveFromEntity(Entity& entity) override;
        
            static int move(lua_State *L);
            static int rotate(lua_State *L);
            static int setRotation(lua_State *L);
            static int place(lua_State *L);
            static int getPosition(lua_State *L);
        public:
            std::vector<int> m_scripts;
    };
}
