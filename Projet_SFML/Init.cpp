#include "Init.h"
#include "AssetsModule/AssetManager.h"
#include "Assets.h"

void LoadSprite(sf::Sprite& _spr, sf::Texture& _tex, bool _isCentered)
{
    _spr.setTexture(_tex);
    if (_isCentered)
    {
        sf::Vector2u localOriginU = _tex.getSize();
        sf::Vector2f localOriginF = { (float)localOriginU.x / 2.f, (float)localOriginU.y / 2.f };
        _spr.setOrigin(localOriginF);
    }
}

void InitControls(Controls& _controls)
{
    _controls.moveUp = sf::Keyboard::Z;
    _controls.moveDown = sf::Keyboard::S;
    _controls.moveLeft = sf::Keyboard::Q;
    _controls.moveRight = sf::Keyboard::D;
}

void InitPlayer(Player& _player)
{
    _player = Player(500.f, 500.f, 200.f);
}

void Init(GameData& _gd)
{
    _gd.window.create(sf::VideoMode(SWIDTH, SHEIGHT), "SFML works!");
    _gd.window.setFramerateLimit(60);

	AssetManager::CreateAssetContainer<Sound>();
	AssetManager::CreateAssetContainer<Texture>();

    _gd.testTextureID = AssetManager::RegisterAsset(new Texture("../Ressources/Images/Link/droite1.png"), true);

    _gd.sprites.sprTest.setPosition({ SWIDTH / 2, SHEIGHT / 2 });

    _gd.textures.tex.loadFromFile("../Ressources/Images/Link/Bas1.png");
    LoadSprite(_gd.sprites.spr, _gd.textures.tex, true);


    InitPlayer(_gd.player);
    InitControls(_gd.controls);
    string perso = "Darin/";
    LoadAnim("../Ressources/Images/" + perso, _gd);
    _gd.player.SetPersoDef(&_gd.persoDef);


}