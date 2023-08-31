#include "AnimationReader.h"

void LoadSprites(sf::Sprite& _spr, sf::Texture& _tex, bool _isCentered)
{
	_spr.setTexture(_tex);
	if (_isCentered)
	{
		sf::Vector2u localOriginU = _tex.getSize();
		sf::Vector2f localOriginF = { (float)localOriginU.x / 2.f, (float)localOriginU.y / 2.f };
		_spr.setOrigin(localOriginF);
	}
}

void LoadAnim(string _path, GameData& _gd)
{
	ifstream inFile(_path + "Def.txt");
	if (!inFile.is_open())
	{
		cout << "Erreur de fichier" << endl;
		cin.get(); // équivalent à getchar()
		exit(0);
	}
	else
	{
		string line;
		while (!inFile.eof())
		{
			inFile >> line;
			if (line == "SPRITES")
			{
				inFile >> _gd.persoDef.size;
				_gd.persoDef.timeLine = new sf::Sprite[_gd.persoDef.size];
				_gd.persoDef.timeLineTex = new sf::Texture[_gd.persoDef.size];
				for (int i = 0; i < _gd.persoDef.size; i++)
				{
					inFile >> line;
					_gd.persoDef.timeLineTex[i].loadFromFile(_path + line);
					LoadSprites(_gd.persoDef.timeLine[i], _gd.persoDef.timeLineTex[i], true);
				}
			}
			else if (line == "ANIM")
			{
				inFile >> line;
				if (line == "MARCHE_HAUT")
				{
					inFile >> _gd.persoDef.sequences[MARCHE_HAUT].start;
					inFile >> _gd.persoDef.sequences[MARCHE_HAUT].end;
					inFile >> _gd.persoDef.sequences[MARCHE_HAUT].totalTime;
				}
				else if (line == "MARCHE_BAS")
				{
					inFile >> _gd.persoDef.sequences[MARCHE_BAS].start;
					inFile >> _gd.persoDef.sequences[MARCHE_BAS].end;
					inFile >> _gd.persoDef.sequences[MARCHE_BAS].totalTime;
				}
				else if (line == "MARCHE_DROIT")
				{
					inFile >> _gd.persoDef.sequences[MARCHE_DROIT].start;
					inFile >> _gd.persoDef.sequences[MARCHE_DROIT].end;
					inFile >> _gd.persoDef.sequences[MARCHE_DROIT].totalTime;
				}
				else if (line == "MARCHE_GAUCHE")
				{
					inFile >> _gd.persoDef.sequences[MARCHE_GAUCHE].start;
					inFile >> _gd.persoDef.sequences[MARCHE_GAUCHE].end;
					inFile >> _gd.persoDef.sequences[MARCHE_GAUCHE].totalTime;
				}
				else if (line == "IDLE_HAUT")
				{
					inFile >> _gd.persoDef.sequences[IDLE_HAUT].start;
					inFile >> _gd.persoDef.sequences[IDLE_HAUT].end;
					inFile >> _gd.persoDef.sequences[IDLE_HAUT].totalTime;
				}
				else if (line == "IDLE_BAS")
				{
					inFile >> _gd.persoDef.sequences[IDLE_BAS].start;
					inFile >> _gd.persoDef.sequences[IDLE_BAS].end;
					inFile >> _gd.persoDef.sequences[IDLE_BAS].totalTime;
				}
				else if (line == "IDLE_DROIT")
				{
					inFile >> _gd.persoDef.sequences[IDLE_DROIT].start;
					inFile >> _gd.persoDef.sequences[IDLE_DROIT].end;
					inFile >> _gd.persoDef.sequences[IDLE_DROIT].totalTime;
				}
				else if (line == "IDLE_GAUCHE")
				{
					inFile >> _gd.persoDef.sequences[IDLE_GAUCHE].start;
					inFile >> _gd.persoDef.sequences[IDLE_GAUCHE].end;
					inFile >> _gd.persoDef.sequences[IDLE_GAUCHE].totalTime;
				}
			}
		}
	}

	inFile.close();
}