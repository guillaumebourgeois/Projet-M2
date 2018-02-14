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
	static int currentId;
	const int idCard;
	string name;

	int* colors;
	int* types;
	int* capacities;
	int* manaCostes;
	int edition;
	int popularity;

	string text;

	float power;
	float toughness;

	Card();
	Card(string, int[]);
	~Card();
};

