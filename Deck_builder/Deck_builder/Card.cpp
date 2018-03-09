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
		this->colors[0] = true;
	else
		this->colors[0] = false;

	if (colorsString.find("G") != -1)
		this->colors[1] = true;
	else
		this->colors[1] = false;

	if (colorsString.find("R") != -1)
		this->colors[2] = true;
	else
		this->colors[2] = false;
	
	if (colorsString.find("U") != -1)
		this->colors[3] = true;
	else
		this->colors[3] = false;
	
	if (colorsString.find("W") != -1)
		this->colors[4] = true;
	else
		this->colors[4] = false;
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

Card::Card(int idCard, string name, string colorsString, __int8 type, __int8 manaCost, int edition) : Card(idCard, name, colorsString, type, manaCost)
{
	this->edition = edition;
}

Card::~Card()
{
}
