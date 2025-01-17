/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** TextComponents.cpp
*/

#include "TextComponents.hpp"
#include "ECS/ECS.hpp"

namespace ECS::Components
{
    void TextComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        std::string text(va_arg(args, char *));
        char *font = va_arg(args, char *);
        int size = va_arg(args, int);
        va_end(args);

        if (font == nullptr) {
            m_texts.emplace_back();
            p_fontsNames.emplace_back(std::nullopt);
            m_texts.back().setString(text);
            m_texts.back().setFont(ECS::ECS::GetInstance().getBasicFont());
        } else if (!p_alreadyLoaded.contains(font)) {
            p_alreadyLoaded.emplace(font, std::make_pair(sf::Font(), 1));
            p_alreadyLoaded[font].first.loadFromFile(font);
            m_texts.emplace_back();
            m_texts.back().setString(text);
            m_texts.back().setFont(p_alreadyLoaded[font].first);
            p_fontsNames.emplace_back(font);
        } else {
            m_texts.emplace_back();
            m_texts.back().setString(text);
            m_texts.back().setFont(p_alreadyLoaded[font].first);
            p_fontsNames.emplace_back(font);
            p_alreadyLoaded[font].second++;
        }
        m_texts.back().setCharacterSize(size);
        IdToIndex_p[entity.id] = m_texts.size() - 1;
        entity.componentsName.insert(typeid(TextComponents).name());
        (*ECS::ECS::GetInstance().getSystemsManager())[SystemsManager::SystemType::TEXT]->AddEntity(entity);
    }

    void TextComponents::RemoveFromEntity(Entity &entity)
    {
        std::size_t index = IdToIndex_p[entity.id];

        m_texts.erase(m_texts.begin() + index);
        if (std::optional<std::string> font = p_fontsNames[index]) {
            p_alreadyLoaded[*font].second--;
            if (p_alreadyLoaded[*font].second == 0)
                p_alreadyLoaded.erase(*font);
        }
        p_fontsNames.erase(p_fontsNames.begin() + index);
        entity.componentsName.erase(typeid(TextComponents).name());
        IdToIndex_p.erase(index);
    }
}
