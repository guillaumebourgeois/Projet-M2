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
	bitset<5> nbCommonsBits = c1.colors & c2.colors;

	int nbColorc1 = c1.colors.count();
	int nbColorc2 = c2.colors.count();
	int commons = nbCommonsBits.count();

	if (commons == 0)
		return 0;
	else if (nbColorc1 == 0 || nbColorc2 == 0)
		return 3;
	else
		return (NB_COLORS - (max(nbColorc1, nbColorc2) - commons));
}

void Graph::createEdges(vector<Card> Cards)
{
	bitset<5> nbCommonsBits;
	int nbColorc1, nbColorc2, commons;

	int n = this->nbCards;
	cout << n << endl;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (i != j)
			{
				// COLORS
				nbCommonsBits = Cards[i].colors & Cards[j].colors;

				nbColorc1 = Cards[i].colors.count();
				nbColorc2 = Cards[j].colors.count();

				commons = nbCommonsBits.count();

				if (commons == 0)
					this->Edges[i*nbCards + j].colorValue = 0;
				else if (nbColorc1 == 0 || nbColorc2 == 0)
					this->Edges[i*nbCards + j].colorValue = 3;
				else
					this->Edges[i*nbCards + j].colorValue = (NB_COLORS - (max(nbColorc1, nbColorc2) - commons));

				//this->Edges[i*nbCards + j].colorValue = this->matchingColors(Cards[i], Cards[j]);

				// TYPES etc


				// TOTAL
				this->Edges[i*nbCards + j].totalValue = this->Edges[i*nbCards + j].colorValue * COEF_COLOR;
			}
		}
	}
}

void Graph::printGraph()
{
	for (int i = 0; i < this->Edges.size(); ++i) {
		//cout << "Carte 1 : " << this->edges[i].idCard1 << " ; Carte 2 : " << this->edges[i].idCard2 << " ; Valeur : " << this->edges[i].colorValue << endl;
		if (this->Edges[i].colorValue != 0 && this->Edges[i].colorValue != -1)
			cout << (int)this->Edges[i].colorValue << " ";
		//cout << unsigned(this->Edges[i].totalValue) << " ";
	}

	//cout << "nbCards : " << this->nbCards << endl;
	cout << "Total : " << (int)this->Edges.size() << " liens." << endl;
}

Graph::~Graph()
{
}