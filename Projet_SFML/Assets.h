#pragma once

#include <SFML/Graphics.hpp>

#include "AssetsModule/AssetsBody.h"

class Texture : public Asset<sf::Texture>
{
public:
    Texture(const char* path) : Asset<sf::Texture>(path) {}

    bool LoadData() override {
        m_Data = new sf::Texture();
        return m_Data->loadFromFile(m_Path);
    }
    bool UnloadData() override {
        if (m_Data == nullptr)
            return false;
        delete m_Data;
        m_Data = nullptr;
        return true;
    }
};

class Sound : public Asset<sf::Sound>
{
public:
	Sound(const char* path) : Asset<sf::Sound>(path) {}

	bool LoadData() override {
		return false;
	}
	bool UnloadData() override {
		return false;
	}
};