/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

class Card
{
	public:
		int idCard;
		std::string name;

		std::bitset<NB_COLORS> colors {0b00000};
		__int16 subtype;
		__int8 type;
		__int8 manaCost;
		__int8 capacity;
		int edition;
		//int popularity;

		Card();
		Card(int, std::string);
		Card(int, std::string, std::string);
		Card(int, std::string, std::string, __int16);
		Card(int, std::string, std::string, __int16, __int8);
		Card(int, std::string, std::string, __int16, __int8, __int8);
		Card(int, std::string, std::string, __int16, __int8, __int8, int);
		~Card();
};

