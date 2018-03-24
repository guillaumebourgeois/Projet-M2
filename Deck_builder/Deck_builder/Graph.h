/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#pragma once

#include "Card.h"
#include "stdafx.h"

typedef boost::bimap<int, int> bimap_type;

class Graph
{
public:
	int nbCards;
	std::vector<Card> Cards;
	std::vector<__int8> Edges;

	bimap_type Ids;

	Graph();
	~Graph();

	void createCards();

	void createEdges(int, int, int, int, int);

	void printGraph();

	// Resolution algorithms 
	// M�thode de r�solution incluant un graph dynamique dont le sommet de recherche de base est unique
	Card* usingDynamicGraph(std::vector<Card> cards, std::vector<Card> allCards, std::vector<__int8> matrix, boost::bimap<int, int> ids);

	// M�thode de r�solution par les plus lourds voisins (le plus lourd)
	std::multimap<int, int> heavyNeighbour(std::vector<int> &idsPool);

	// M�thode de r�solution par calcul de distance entre chaque carte
	int* distanceSum(std::vector<int> cards);

	// M�thode de r�solution des k plus proches voisins
	std::multimap<int, int> closestNeighbours(std::vector<int>);

	void writeMatrix();
	void readMatrix();
};