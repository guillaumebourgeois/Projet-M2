/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

using namespace std;

Card::Card()
{
}

Card::Card(int idCard, string colorsString)
{
	this->idCard = idCard;

	if (colorsString.find("B") != -1)
		colors[0] = 1;
	else
		colors[0] = 0;
	if (colorsString.find("G") != -1)
		colors[1] = 1;
	else
		colors[1] = 0;
	if (colorsString.find("R") != -1)
		colors[2] = 1;
	else
		colors[2] = 0;
	if (colorsString.find("U") != -1)
		colors[3] = 1;
	else
		colors[3] = 0;
	if (colorsString.find("W") != -1)
		colors[4] = 1;
	else
		colors[4] = 0;
}

Card::Card(int idCard, string name, string colorsString) : Card(idCard, name)
{
	this->name = name;
}

Card::Card(int idCard, string name, string colorsString, __int8 type) : Card (idCard, name, colorsString)
{
	this->type = type;
}

Card::Card(int idCard, string name, string colorsString, __int8 type, __int8 manaCost) : Card(idCard, name, colorsString, type)
{
	this->manaCost = manaCost;
}

Card::~Card()
{
}
