/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#pragma once

using namespace std;

class Card
{
	public:
		int idCard;
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
		Card(int, string, int[]);
		~Card();
};

