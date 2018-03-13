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

void Graph::createEdges(vector<Card> Cards)
{
	map<int, int> results;

	bitset<5> nbCommonsBits;
	int nbColorc1, nbColorc2, commons;
	int i, j, k, l;
	int colorValue, editionValue, typeValue, capacityValue, subtypeValue, totalValue;
	int maxTypeValue = 0, maxSubtypeValue = 0, maxCapacityValue = 0, maxTotalValue = 0;

	int n = this->nbCards;
	
	cout << n << endl;
	
	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (i != j)
			{
				// COLORS
				nbCommonsBits = Cards[i].colors & Cards[j].colors;

				nbColorc1 = Cards[i].colors.count();
				nbColorc2 = Cards[j].colors.count();

				commons = nbCommonsBits.count();

				if (commons == 0)
					colorValue = 0;
				else if (nbColorc1 == 0 || nbColorc2 == 0)
					colorValue = 3;
				else
					colorValue = (NB_COLORS - (max(nbColorc1, nbColorc2) - commons));

				// EDITION
				editionValue = 0;
				k = 0;
				l = 0;
				while (editionValue == 0 && k < Cards[i].editions.size())
				{
					while (editionValue == 0 && l < Cards[j].editions.size())
					{
						if (Cards[i].editions[k] == Cards[j].editions[l])
							editionValue = 2;
						++l;
					}
					++k;
				}
				k = 0;
				l = 0;
				while (editionValue == 0 && k < Cards[i].blocs.size())
				{
					while (editionValue == 0 && l < Cards[j].blocs.size())
					{
						if (Cards[i].blocs[k] == Cards[j].blocs[l])
							editionValue = 1;
						++l;
					}
					++k;
				}

				// SUBTYPES
				subtypeValue = 0;
				for (k = 0; k < Cards[i].subtypes.size(); ++k)
				{
					for (l = 0; l < Cards[j].subtypes.size(); ++l)
					{
						if (Cards[i].subtypes[k] == Cards[j].subtypes[l])
							++subtypeValue;
					}
				}
				if (subtypeValue > maxSubtypeValue)
					maxSubtypeValue = subtypeValue;

				// TYPES
				typeValue = 0;
				for (k = 0; k < Cards[i].types.size(); ++k)
				{
					for (l = 0; l < Cards[j].types.size(); ++l)
					{
						if (Cards[i].types[k] == Cards[j].types[l])
							++typeValue;
					}
				}
				if (typeValue > maxTypeValue)
					maxTypeValue = typeValue;
				
				// CAPACITIES
				capacityValue = 0;
				for (k = 0; k < Cards[i].capacities.size(); ++k)
				{
					for (l = 0; l < Cards[j].capacities.size(); ++l)
					{
						if (Cards[i].capacities[k] == Cards[j].capacities[l])
							++capacityValue;
					}
				}
				if (capacityValue > maxCapacityValue)
					maxCapacityValue = capacityValue;

				// TOTAL
				totalValue = 
					colorValue * COEF_COLOR + 
					editionValue * COEF_EDITION +
					subtypeValue * COEF_SUBTYPE +
					typeValue * COEF_TYPE +
					capacityValue * COEF_CAPACITY;

				if (totalValue > maxTotalValue)
					maxTotalValue = totalValue;

				if (results.find(totalValue) == results.end())
					results.insert(pair<int, int>(totalValue, 1));
				else
					++results[totalValue];

				this->Edges[i*nbCards + j].totalValue = totalValue;
				//if (editionValue != 0)
					//cout << colorValue << " " << editionValue << "   " << (int)this->Edges[i*nbCards + j].totalValue << endl;
			}
		}
	}
	//cout << maxSubtypeValue << " " << maxTypeValue << " " << maxCapacityValue << endl;
	cout << endl << "Max total value : " << maxTotalValue << endl;
	map<int, int>::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
		cout << it->first << " " << it->second << endl;
}

void Graph::printGraph()
{
	for (int i = 0; i < this->Edges.size(); ++i) {
		//cout << "Carte 1 : " << this->edges[i].idCard1 << " ; Carte 2 : " << this->edges[i].idCard2 << " ; Valeur : " << this->edges[i].colorValue << endl;
		//cout << unsigned(this->Edges[i].totalValue) << " ";
	}

	//cout << "nbCards : " << this->nbCards << endl;
	cout << "Total : " << (int)this->Edges.size() << " liens." << endl;
}

Graph::~Graph()
{
}