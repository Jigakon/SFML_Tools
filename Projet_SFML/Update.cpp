#include "Update.h"

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
    }
    sf::Vector2i d(IsGoingDir(_gd.controls.moveRight) - IsGoingDir(_gd.controls.moveLeft),
        IsGoingDir(_gd.controls.moveDown) - IsGoingDir(_gd.controls.moveUp));

    _gd.player.Move(d, _gd.dt);
    _gd.player.UpdateCurrentTimeAnim(_gd.dt);
}