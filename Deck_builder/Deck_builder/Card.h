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
	int multivereid;
	std::string name;

	std::bitset<NB_COLORS> colors{ 0b00000 };
	__int8 manaCost;
	std::vector<__int16> blocs;
	std::vector<__int16> editions;
	std::vector<__int8>  types;
	std::vector<__int16> subtypes;
	std::vector<__int8>  capacities;

	Card();
	Card(int, std::string);
	Card(int, std::string, std::string, __int8);
	~Card();
};