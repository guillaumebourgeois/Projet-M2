/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

int Card::currentId = 1;

Card::Card() : idCard(currentId++)
{

}

Card::Card(string name, int colors[]) : idCard(currentId++)
{
	this->name = name;
	this->colors = new int[5];
	this->colors = colors;
}

Card::~Card()
{

}
