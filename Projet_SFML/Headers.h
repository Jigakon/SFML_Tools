#ifndef HEADERS__H
#define HEADERS__H

// SFML Libraries
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Network.hpp>
#include <SFML/Audio.hpp>

// classic Libraries
#include <stdio.h>
#include <tchar.h>
#include <time.h>
#include <windows.h>
#include <math.h>
#include <iostream>
#include <string>

using namespace std;

enum Dir
{
	DIR_HAUT,
	DIR_BAS,
	DIR_DROITE,
	DIR_GAUCHE
};

enum NameAnim
{
	MARCHE_HAUT,
	MARCHE_BAS,
	MARCHE_GAUCHE,
	MARCHE_DROIT,
	IDLE_HAUT,
	IDLE_BAS,
	IDLE_GAUCHE,
	IDLE_DROIT,
	TOTAL_ANIM
};

typedef struct SEQUENCE Sequence;
struct SEQUENCE
{
	int start;
	int end;
	float totalTime;
};

typedef struct PERSODEF PersoDef;
struct PERSODEF
{
	sf::Sprite* timeLine;
	sf::Texture* timeLineTex;
	int size;
	Sequence sequences[TOTAL_ANIM];
};

#endif // !HEADERS__H