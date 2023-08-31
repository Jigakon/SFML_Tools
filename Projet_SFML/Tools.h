#ifndef TOOLS__H
#define TOOLS__H

#include "Definitions.h"

sf::Sprite LoadSprite(string _path);
void BlitSprite(sf::Sprite _sprite, sf::Vector2f _pos, sf::Window& _window);

#endif // !TOOLS__H