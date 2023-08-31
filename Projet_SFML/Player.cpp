#include "Player.h"

sf::Vector2f Player::GetPos() const
{
	return pos;
}

float Player::GetSpeed() const
{
	return speed;
}

Dir Player::GetDir() const
{
	return dir;
}

float Player::GetCurrentTimeAnim() const
{
	return currentTimeAnim;
}

void Player::SetPos(float _x, float _y)
{
	pos.x = _x;
	pos.y = _y;
}

void Player::SetPos(sf::Vector2f _pos)
{
	pos = _pos;
}

void Player::SetSpeed(float _speed)
{
	speed = _speed;
}

void Player::SetPersoDef(PersoDef* _persoDef)
{
	persoDef = _persoDef;
}

void Player::Move(sf::Vector2i _d, float _dt)
{
	bool keyPressed = false;
	float norme = sqrtf((_d.x * _d.x) + (_d.y * _d.y));
	if (norme > 0)
	{
		sf::Vector2f tempPos = pos;
		tempPos.y += _d.y * speed / norme * _dt;
		tempPos.x += _d.x * speed / norme * _dt;
		pos = tempPos;
	}

	if (_d.y == -1)
	{
		keyPressed = true;
		dir = DIR_HAUT;
	}
	else if (_d.y == 1)
	{
		keyPressed = true;
		dir = DIR_BAS;
	}
	else if (_d.x == -1)
	{
		keyPressed = true;
		dir = DIR_GAUCHE;
	}
	else if (_d.x == 1)
	{
		keyPressed = true;
		dir = DIR_DROITE;
	}

	if (keyPressed)
	{
		switch (dir)
		{
		case DIR_HAUT:
			nameAnim = MARCHE_HAUT;
			break;
		case DIR_BAS:
			nameAnim = MARCHE_BAS;
			break;
		case DIR_DROITE:
			nameAnim = MARCHE_DROIT;
			break;
		case DIR_GAUCHE:
			nameAnim = MARCHE_GAUCHE;
			break;
		}
	}
	else
	{
		currentTimeAnim = 0.f;
		switch (dir)
		{
		case DIR_HAUT:
			nameAnim = IDLE_HAUT;
			break;
		case DIR_BAS:
			nameAnim = IDLE_BAS;
			break;
		case DIR_DROITE:
			nameAnim = IDLE_DROIT;
			break;
		case DIR_GAUCHE:
			nameAnim = IDLE_GAUCHE;
			break;
		}
	}
}

void Player::UpdateCurrentTimeAnim(float _dt)
{
	currentTimeAnim += _dt;
	while (currentTimeAnim >= persoDef->sequences[nameAnim].totalTime)
	{
		currentTimeAnim -= persoDef->sequences[nameAnim].totalTime;
	}
}

void Player::Draw(sf::RenderWindow& _window)
{
	int nbImages = persoDef->sequences[nameAnim].end
		- persoDef->sequences[nameAnim].start + 1;
	int imageCourante = nbImages * currentTimeAnim / persoDef->sequences[nameAnim].totalTime
		+ persoDef->sequences[nameAnim].start;

	persoDef->timeLine[imageCourante].setPosition(pos);
	_window.draw(persoDef->timeLine[imageCourante]);
}

Player::Player(float _x, float _y, float _speed)
{
	pos.x = _x;
	pos.y = _y;
	speed = _speed;
	dir = DIR_BAS;
	currentTimeAnim = 0.f;
}

Player::Player(sf::Vector2f _pos)
{
	pos = _pos;
	speed = 5.f;
	dir = DIR_BAS;
	currentTimeAnim = 0.f;
}

Player::Player()
{
	pos.x = 0.f;
	pos.y = 0.f;
	speed = 5.f;
	dir = DIR_BAS;
	currentTimeAnim = 0.f;


	persoDef = NULL;
	nameAnim = IDLE_BAS;
}