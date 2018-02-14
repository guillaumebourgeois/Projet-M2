/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#include "stdafx.h"

Graph::Graph()
{
}

Graph::Graph(int size)
{
	this->adjacencyMatrix = (int**)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		this->adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
	}
}

Graph::Graph(int size, Edge* edges)
{
	this->adjacencyMatrix = (int**)malloc(size * sizeof(int));
	for (int i = 0; i < size; i++) {
		this->adjacencyMatrix[i] = (int*)malloc(size * sizeof(int));
	}

	for (int i = 0; i < (sizeof(edges) / sizeof(edges[0])); i++) {
		this->edges.push_back(edges[i]);
	}
}

Graph::~Graph()
{
}

void Graph::addEdge(Edge edge)
{
	this->edges.push_back(edge);
	//this->adjacencyMatrix[edge.idCard1][edge.idCard2] = edge.idEdge;
}

void Graph::printGraph()
{
	for (int i = 0; i < this->edges.size(); i++) {
		cout << "Carte 1 : " << this->edges[i].idCard1 << " ; Carte 2 : " << this->edges[i].idCard2 << " ; Valeur : " << this->edges[i].colorValue << endl;
	}

	cout << "Total : " << this->edges.size() << " liens." << endl;
}
