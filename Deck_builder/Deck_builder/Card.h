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
		int idCard;
		string name;

		__int8* colors;
		__int8 type;
		__int8 manaCost;
		__int8 capacity;
		int edition;
		//int popularity;

		//float power;
		//float toughness;

		Card();
		Card(int, string);
		Card(int, string, string);
		Card(int, string, string, __int8);
		Card(int, string, string, __int8, __int8);
		~Card();
};

