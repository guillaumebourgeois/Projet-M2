/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

class Graph
{
public:
	vector<Edge> edges;
	int** adjacencyMatrix;

	Graph();
	Graph(int);
	Graph(int, Edge*);
	~Graph();

	void addEdge(Edge);
	void printGraph();
};

