/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

int Edge::currentId = 1;

Edge::Edge() : idEdge(currentId++)
{
}

Edge::Edge(Card* c1, Card* c2, int color /*, int type, int capacity, int manacost, int edition, int popularity */) : idEdge(currentId++)
{
	this->idCard1 = c1->idCard;
	this->idCard2 = c2->idCard;
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
