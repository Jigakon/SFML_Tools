#ifndef INIT__H
#define INIT__H

#include "Definitions.h"
#include "AnimationReader.h"
#include "AssetManager.h"
#include <unordered_map>

void Init(GameData& _gd);

class Texture : public Asset<sf::Texture>
{
public:
    Texture(const char* path) : Asset<sf::Texture>(path) {}

    bool LoadData() override { return m_Data->loadFromFile(m_Path); }
    bool UnloadData() override { return false; }
};

#endif // !INIT__H