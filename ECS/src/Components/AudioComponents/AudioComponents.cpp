/*
** EPITECH PROJECT, 2024
** GE [WSL: Ubuntu]
** File description:
** AudioComponents.cpp
*/

#include "AudioComponents.hpp"

namespace ECS::Components
{
    void AudioComponents::AddToEntity(Entity &entity, va_list args, ...)
    {
        va_start(args, args);
        char *path = va_arg(args, char *);
        va_end(args);

        if (!p_alreadyLoaded.contains(path)) {
            sf::SoundBuffer buffer;
            buffer.loadFromFile(path);
            p_alreadyLoaded.emplace(path, std::make_pair(buffer, 1));
        } else {
            p_alreadyLoaded[path].second++;
        }
        sf::Sound sound;
        sound.setBuffer(p_alreadyLoaded[path].first);
        m_audio.push_back(sound);
        p_audioPaths.push_back(path);
        IdToIndex_p[entity.id] = m_audio.size() - 1;
        entity.componentsName.insert(typeid(AudioComponents).name());
    }

    void AudioComponents::RemoveFromEntity(Entity &entity)
    {
        if (p_alreadyLoaded[p_audioPaths[IdToIndex_p[entity.id]]].second == 1) {
            p_alreadyLoaded.erase(p_audioPaths[IdToIndex_p[entity.id]]);
        } else {
            p_alreadyLoaded[p_audioPaths[IdToIndex_p[entity.id]]].second--;
        }
        m_audio.erase(m_audio.begin() + IdToIndex_p[entity.id]);
        p_audioPaths.erase(p_audioPaths.begin() + IdToIndex_p[entity.id]);
        IdToIndex_p.erase(entity.id);
        entity.componentsName.erase(typeid(AudioComponents).name());
    }
}
