/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic cards
***/

#pragma once

#include "stdafx.h"

using namespace std;

vector<int> readFile()
{
	vector<int> ids;
	int res;

	OPENFILENAME ofn;
	TCHAR tmp[1024];
	tmp[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Deck Builder");
	//ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Textes (*.txt)\0*.TXT\0");
	ofn.lpstrFilter = _T("(*.txt)\0*.TXT\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER; // | OFN_ALLOWMULTISELECT  ;

	res = GetOpenFileName(&ofn);
	//int res = GetSaveFileName(&ofn); 
	//printf("Code de sortie : %d\n", res);
	//convert_multiple(ofn.lpstrFile);

	if (ofn.lpstrFile != nullptr)
	{
		_tprintf(_T("Ouverture du fichier : %s\n"), ofn.lpstrFile);

		ifstream file(ofn.lpstrFile, ios::in);

		if (file)
		{
			while (file >> res)
				ids.push_back(res);

			file.close();
		}
		else
			cout << "Erreur lors de l'ouverture du fichier" << endl;
	}

	return ids;
}

void writeFile(vector<int> ids)
{
	int res;

	OPENFILENAME ofn;
	TCHAR tmp[1024];
	tmp[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Deck Builder");
	//ofn.lpstrFilter = _T("Tous (*.*)\0*.*\0Textes (*.txt)\0*.TXT\0");
	ofn.lpstrFilter = _T("(*.txt)\0*.TXT\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER; // | OFN_ALLOWMULTISELECT  ;

											  //res = GetOpenFileName(&ofn);
	res = GetSaveFileName(&ofn);
	//printf("Code de sortie : %d\n", res);
	//convert_multiple(ofn.lpstrFile);

	if (ofn.lpstrFile != nullptr)
	{
		_tprintf(_T("Enregistrement dans le fichier fichier : %s\n"), ofn.lpstrFile);

		ofstream file(ofn.lpstrFile, ios::out | ios::trunc);

		if (file)
		{
			for (int i = 0; i < ids.size(); ++i)
				file << ids[i] << endl;

			file.close();
		}
		else
			cerr << "Erreur lors de l'ouverture du fichier !" << endl;
	}
}

Card* usingDynamicGraph(std::vector<Card> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids)
{

}

Card* heavyNeighbour(std::vector<Card> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids)
{

}

int* distanceSum(std::vector<int> cards, std::vector<Card> allCards, std::vector<Edge> matrix, boost::bimap<int, int> ids)
{
	std::map<int, int> tmp;
	std::map<int, int> res;
	int *selectedCards = (int*)malloc(10 * sizeof(int));
	int *max = (int*)calloc(10, sizeof(int));

	for (int i : cards) {
		for (Card j : allCards) {
			if (tmp[j.idCard]) {
				tmp[j.idCard] += matrix[ids.left.at(i) * allCards.size() + ids.left.at(j.idCard)].totalValue;
			} else {
				tmp[j.idCard] = matrix[ids.left.at(i) * allCards.size() + ids.left.at(j.idCard)].totalValue;
			}
		}
	}

	for (auto it : res) {
		for (int i = 0; i < 10; i++) {
			if (max[i] < it.second) {
				max[i] = it.second;
				res[i] = it.first;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		selectedCards[i] = res[i];
	}

	free(max);
	tmp.clear();
	res.clear();
	return selectedCards;
}