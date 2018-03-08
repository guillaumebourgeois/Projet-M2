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
	printf("Code de sortie : %d\n", res);
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

void writeFile()
{

}