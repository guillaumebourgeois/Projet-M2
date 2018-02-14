/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

using namespace std;

class Card
{
public:
	//static int currentId;
	
	int idCard;
	string name;

	__int8* colors;
	//int* types;
	//int* capacities;
	//int* manaCostes;
	//int edition;
	//int popularity;

	//string text;

	//float power;
	//float toughness;

	Card();
	Card(int, string, __int8[]);
	~Card();
};

