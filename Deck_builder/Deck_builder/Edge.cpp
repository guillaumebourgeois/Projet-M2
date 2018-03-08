/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

using namespace std;

Edge::Edge()
{
	this->colorValue = -1;
	//this->typeValue = 0;
	//this->capacityValue = 0;
	this->totalValue = 0;
}

Edge::Edge(__int8 color /*, int type, int capacity, int manacost, int edition, int popularity */) /*: idEdge(currentId++)*/
{
	this->colorValue = color;
	/*this->typeValue = type;
	this->capacityValue = capacity;
	this->manacostValue = manacost;
	this->editionValue = edition;
	this->popularityValue = popularity;*/
	this->totalValue = color /* + type + capacity + manacost + edition + popularity */;
}

Edge::~Edge()
{
}
