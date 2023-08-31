#ifndef PLAYER__H
#define PLAYER__H

#include "Headers.h"

class Player
{
private:
	sf::Vector2f pos{};
	float speed;
	Dir dir;
	PersoDef* persoDef;
	NameAnim nameAnim;
	float currentTimeAnim;

public:
	sf::Vector2f GetPos() const;
	float GetSpeed() const;
	Dir GetDir() const;
	//NameAnim GetNameAnim() const;
	float GetCurrentTimeAnim() const;

	void SetPos(float _x, float _y);
	void SetPos(sf::Vector2f _pos);
	void SetSpeed(float _speed);
	void SetPersoDef(PersoDef* _persoDef);

	void Move(sf::Vector2i _d, float _dt);
	void UpdateCurrentTimeAnim(float _dt);
	void Draw(sf::RenderWindow& _window);

	Player(float _x, float _y, float _speed);
	Player(sf::Vector2f _pos);
	Player();
};

#endif // !PLAYER__H