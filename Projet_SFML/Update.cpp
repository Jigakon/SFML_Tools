#include "Update.h"

#include "AssetsModule/AssetManager.h"
#include "Assets.h"

int IsGoingDir(sf::Keyboard::Key _key)
{
    return sf::Keyboard::isKeyPressed(_key);
}

void Update(GameData& _gd)
{
    sf::Time time = _gd.frameClock.restart();
    _gd.dt = time.asSeconds();

    sf::Event event;
    while (_gd.window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _gd.window.close();
        if (event.type == sf::Event::KeyPressed)
        {
            switch (event.key.code)
            {
            case sf::Keyboard::O: {

                AssetManager::LoadAsset<Texture>(_gd.testTextureID); 
                auto texture = AssetManager::GetAsset<Texture>(_gd.testTextureID);
                _gd.sprites.sprTest.setTexture(*texture->GetData());
                break;
            }
            case sf::Keyboard::P:
                AssetManager::UnloadAsset<Texture>(_gd.testTextureID);
                break;
            }
        }
    }
    sf::Vector2i d(IsGoingDir(_gd.controls.moveRight) - IsGoingDir(_gd.controls.moveLeft),
        IsGoingDir(_gd.controls.moveDown) - IsGoingDir(_gd.controls.moveUp));

    _gd.player.Move(d, _gd.dt);
    _gd.player.UpdateCurrentTimeAnim(_gd.dt);
}