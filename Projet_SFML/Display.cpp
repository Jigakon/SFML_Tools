#include "Display.h"

void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::RenderWindow& _window)
{
    _sprite.setPosition(_pos);
    _window.draw(_sprite);
}

void Display(GameData& _gd)
{
    _gd.window.clear();

    _gd.player.Draw(_gd.window);

    _gd.window.display();
}