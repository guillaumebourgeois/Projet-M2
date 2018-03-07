/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

using namespace std;

class Graph
{
public:
	int nbCards;
	vector<Edge> Edges;

	Graph();
	Graph(int);
	~Graph();

	void addEdge(Edge);
	__int8 matchingColors(Card, Card);
	void printGraph();
};

