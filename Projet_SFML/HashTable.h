#ifndef HASHTABLE__H
#define HASHTABLE__H

#include "Definitions.h"

#define TAILLE_CHAINE 20
#define TAILLE_TABLE 15

struct INFOS_JOUEUR
{
	string pseudo = "";
	string mdp = "";
	int level = 0;
	int pdv = 0;
	int x = 0;
	int y = 0;
};

typedef struct INFOS_JOUEUR Infos_Joueur;

Bits Hachage(string _tab);
int Place_Vide(int pos, Infos_Joueur _TabHach[TAILLE_TABLE]);
int Egalite(int pos, string chaine, Infos_Joueur _TabHach[TAILLE_TABLE]);
int Insertion(int pos, string chaine, Infos_Joueur _TabHach[TAILLE_TABLE]);
void Affiche_table(Infos_Joueur _TabHach[TAILLE_TABLE]);
void Init_Table(Infos_Joueur _Table_Hach[TAILLE_TABLE]);
int FindStr(string chaine, Infos_Joueur _TabHach[TAILLE_TABLE]);

void func()
{
	Bits cle = 0;
	string chaine_inseree = "Jacky";
	string chaine_cherchee = "Pascaline";
	string chaine_de_trop = "Martin";
	int iPos;
	Infos_Joueur Table_Hach[TAILLE_TABLE];
	Init_Table(Table_Hach);
	cle = Hachage(chaine_inseree) % TAILLE_TABLE;
	cout << "Cle pour la chaine '" << chaine_inseree << "' : " << cle << endl;
	if ((iPos = Insertion(cle, chaine_inseree, Table_Hach)) > 0)
		cout << "La chaine : " << chaine_inseree << " est inseree a la pos n : " << iPos << endl;
	else if (iPos == -1)
		cout << "Il n'y a plus de place disponible dans la table" << endl;

	if ((iPos = Insertion(cle, chaine_cherchee, Table_Hach)) > 0)
		cout << "La chaine : " << chaine_cherchee << " est inseree a la pos n : " << iPos << endl;
	else if (iPos == -1)
		cout << "Il n'y a plus de place disponible dans la table" << endl;

	if ((iPos = Insertion(cle, chaine_de_trop, Table_Hach)) > 0)
		cout << "La chaine : " << chaine_de_trop << " est inseree a la pos n : " << iPos << endl;
	else if (iPos == -1)
		cout << "Il n'y a plus de place disponible dans la table" << endl;

	Affiche_table(Table_Hach);
	if ((iPos = FindStr(chaine_cherchee, Table_Hach)) > 0)
		cout << chaine_cherchee << " est situe a l'indice : " << iPos << endl;
	else if (iPos == -1)
		cout << "La chaine recherchee ne se trouve pas dans la table" << endl;
	else
	{
		cout << "Une place vide a ete rencontree avant de trouver la chaine :" << endl;
		cout << "l'individu " << chaine_cherchee << " n'est pas enregistre dans la table" << endl;
	}
}

Bits Hachage(string _tab)
{
	Bits Resultat = 0;
	Bits Bits_hauts = 0xF8000000;
	Bits Retenue = 0xA8000000;
	int decal_droit = 27;
	int decal_gauche = 5;
	int size = _tab.length();

	for (int i = 0; i < size; i++)
	{
		Retenue = Resultat & Bits_hauts;

		Retenue = Retenue >> decal_droit;
		Resultat = Resultat << decal_gauche;

		Resultat = Resultat ^ Retenue;

		Resultat = Resultat ^ _tab[i];
	}
	return Resultat;
}

void Init_Table(Infos_Joueur _Table_Hach[TAILLE_TABLE])
{
	int indice = 0;
	string chaine[] = {
		"Pierre", "Thomas", "Fabrice", "Patrice", "Lucien", "Laurent", "Audrey",
		"Patricia", "Anna","Clothilde", "Jean", "Jacques","Cyril" };
	int realSize = sizeof(chaine) / sizeof(chaine[0]);
	for (int i = 0; i < realSize; i++)
	{
		indice = Hachage(chaine[i]) % TAILLE_TABLE;
		Insertion(indice, chaine[i], _Table_Hach);
	}
}

int Insertion(int pos, string chaine, Infos_Joueur _TabHach[TAILLE_TABLE])
{
	int success;
	int count = 0;
	while (!Place_Vide(pos, _TabHach) && count < TAILLE_TABLE)
	{
		count++;
		pos = (pos + 1) % TAILLE_TABLE;
	}
	if (count == TAILLE_TABLE)
	{
		success = -1;
	}
	else
	{
		success = pos;
		_TabHach[pos].pseudo = chaine;
	}
	return success;
}

int Place_Vide(int pos, Infos_Joueur _TabHach[TAILLE_TABLE])
{
	return (_TabHach[pos].pseudo == "");
}

int Egalite(int pos, string chaine, Infos_Joueur _TabHach[TAILLE_TABLE])
{
	return (_TabHach[pos].pseudo == chaine);
}

int FindStr(string chaine, Infos_Joueur _TabHach[TAILLE_TABLE])
{
	int count = 0;
	int pos = Hachage(chaine) % TAILLE_TABLE;
	while (count < TAILLE_CHAINE && !Egalite(pos, chaine, _TabHach))
	{
		count++;
		pos = (pos + 1) % TAILLE_TABLE;
	}
	return (count < TAILLE_CHAINE) ? pos : -1;
}

void Affiche_table(Infos_Joueur _TabHach[TAILLE_TABLE])
{
	for (int i = 0; i < TAILLE_TABLE; i++)
	{
		cout << i << " => " << _TabHach[i].pseudo << endl;
	}
}

#endif // !HASHTABLE__H