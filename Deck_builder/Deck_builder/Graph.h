/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

class Graph
{
	public:
		int nbCards;
		std::vector<Edge> Edges;

		Graph();
		Graph(int);
		~Graph();

		void addEdge(Edge);
		__int8 matchingColors(Card, Card);

		void createEdges(std::vector<Card>);

		void printGraph();
};

