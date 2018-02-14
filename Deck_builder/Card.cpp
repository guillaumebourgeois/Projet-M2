/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "stdafx.h"
#include "Card.h"


Card::Card()
{
}

Card::Card(int idCard, string name, int colors[])
{
	this->idCard = idCard;
	this->name = name;
	this->colors = new int[5];
	this->colors = colors;
}

Card::~Card()
{
}
