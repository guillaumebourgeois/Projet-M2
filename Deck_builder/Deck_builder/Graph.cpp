/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

using namespace std;

Graph::Graph()
{
}

Graph::Graph(int nbCards)
{
	this->nbCards = nbCards;
	this->Edges.resize(nbCards*nbCards);
}

void Graph::addEdge(Edge e)
{
	this->Edges.push_back(e);
}

__int8 Graph::matchingColors(Card c1, Card c2)
{
	__int8 nbCommons = 0;
	__int8 nbColorc1 = 0;
	__int8 nbColorc2 = 0;

	for (int i = 0; i < NB_COLORS; ++i) {
		if (c1.colors[i] == 1 && c1.colors[i] == c2.colors[i]) {
			++nbCommons;
			++nbColorc1;
			++nbColorc2;
		}
		if (c1.colors[i] == 1) {
			++nbColorc1;
		}
		if (c2.colors[i] == 1) {
			++nbColorc2;
		}
	}
	if (nbCommons == 0) {
		return 0;
	}
	else {
		return (5 - (max(nbColorc1, nbColorc2) - nbCommons));
	}
}

void Graph::printGraph()
{
	for (int i = 0; i < this->Edges.size(); ++i) {
		//cout << "Carte 1 : " << this->edges[i].idCard1 << " ; Carte 2 : " << this->edges[i].idCard2 << " ; Valeur : " << this->edges[i].colorValue << endl;
		//if (this->Edges[i].colorValue != 0)
			//cout << unsigned(this->Edges[i].colorValue) << " ";
		//cout << unsigned(this->Edges[i].totalValue) << " ";
	}
	//cout << "Total : " << this->Edges.size() << " liens." << endl;
}

Graph::~Graph()
{
}