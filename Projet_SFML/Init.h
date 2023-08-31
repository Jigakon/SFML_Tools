#ifndef INIT__H
#define INIT__H

#include "Definitions.h"
#include "AnimationReader.h"
#include "AssetManager.h"
#include <unordered_map>

void Init(GameData& _gd);

class Texture : public Asset
{
public:
    sf::Texture* m_Data;

    Texture(const char* path) : Asset(path) { m_Data = new sf::Texture(); }

    bool LoadData() override 
    { 
        m_IsLoaded = m_Data->loadFromFile(m_Path);
        return m_IsLoaded; 
    }
    bool UnloadData() override { return false; }
    void* GetData() override { return (void*)m_Data; }
};

#endif // !INIT__H