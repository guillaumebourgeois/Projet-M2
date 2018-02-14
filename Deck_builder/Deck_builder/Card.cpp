/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

using namespace std;

//int Card::currentId = 1;

Card::Card() /*: idCard(currentId++)*/
{

}

Card::Card(int idCard, string name, __int8 colors[]) /*: idCard(currentId++)*/
{
	this->idCard = idCard;
	this->name = name;
	this->colors = new __int8[5];
	this->colors = colors;
}

Card::~Card()
{

}
