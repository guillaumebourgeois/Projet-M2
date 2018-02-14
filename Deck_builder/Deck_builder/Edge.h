/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

using namespace std;

class Edge
{
public:
	//static int currentId;
	int idEdge;
	int idCard1;
	int idCard2;
	
	__int8 colorValue;
	//int typeValue;
	//int capacityValue;
	//int manacostValue;
	//int editionValue;
	//int popularityValue;
	__int8 totalValue;

	Edge();
	Edge(Card*, Card*, __int8 /*, int, int, int, int, int */);
	~Edge();
};



