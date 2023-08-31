#ifndef DEFINITIONS__H
#define DEFINITIONS__H

#include "Headers.h"
#include "Player.h"

#define SWIDTH 1024
#define SHEIGHT 768

#define Randf (float)(rand() % (RAND_MAX + 1)) / (float)RAND_MAX

typedef unsigned long Bits;

struct Textures
{
	sf::Texture tex;
};

struct Sprites
{
	sf::Sprite spr;

    sf::Sprite sprTest;
};

struct Controls
{
    sf::Keyboard::Key moveUp;
    sf::Keyboard::Key moveDown;
    sf::Keyboard::Key moveLeft;
    sf::Keyboard::Key moveRight;
};

struct GameData
{
    sf::RenderWindow window;
    sf::Clock frameClock;

    Textures textures;
    Sprites sprites;

    PersoDef persoDef;

    Player player;

    Controls controls;

    float dt;
};



#endif