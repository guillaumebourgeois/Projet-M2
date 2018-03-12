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
Card* usingDynamicGraph(Card*, int, std::vector<Edge>); 

// Méthode de résolution par voisin le plus proche (le plus lourd)
Card* heavyNeighbour(Card*, int, std::vector<Edge>);

// Méthode de résolution par calcul de distance entre chaque carte
Card* distanceSum(Card*, int, std::vector<Edge>);