/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"


// File functions
std::vector<int> readFile();
void writeFile(std::vector<int>);

// Resolution algorithms 
// Méthode de résolution incluant un graph dynamique dont le sommet de recherche de base est unique
Card* usingDynamicGraph(std::vector<Card> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids);

// Méthode de résolution par voisin le plus proche (le plus lourd)
Card* heavyNeighbour(std::vector<Card> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids);

// Méthode de résolution par calcul de distance entre chaque carte
int* distanceSum(std::vector<int> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids);