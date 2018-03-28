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
	vector<int> ids2;

	int res;

	OPENFILENAME ofn;
	TCHAR tmp[1024];
	tmp[0] = '\0';

	ZeroMemory(&ofn, sizeof(OPENFILENAMEW));

	ofn.lStructSize = sizeof(OPENFILENAMEW);
	ofn.lpstrFile = tmp;
	ofn.nMaxFile = 1024;
	ofn.lpstrTitle = _T("Deck Builder");
	ofn.lpstrFilter = _T("(*.txt)\0*.TXT\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER; // | OFN_ALLOWMULTISELECT  ;

	res = GetOpenFileName(&ofn);

	if (ofn.lpstrFile != nullptr)
	{
		ifstream file(ofn.lpstrFile, ios::in);

		if (file)
		{
			while (file >> res)
				ids.push_back(res);

			file.close();

			try {
				sql::Driver *driver;
				sql::Connection *con;
				sql::Statement *stmt;
				sql::PreparedStatement *pstmt;
				sql::ResultSet *res;

				driver = get_driver_instance();
				con = driver->connect(HOST, USER, PASS);

				con->setSchema(DB);

				stmt = con->createStatement();

				// IDS 
				for (int i = 0; i < ids.size(); ++i)
				{
					pstmt = con->prepareStatement("SELECT sca_card, sca_multiverseid FROM mag_setcard WHERE sca_multiverseid IN (?)");

					pstmt->setInt(1, ids[i]);
					pstmt->executeUpdate();

					res = pstmt->executeQuery();
					res->next();

					ids2.push_back(res->getInt("sca_card"));
				}

				delete res;

				delete pstmt;
				delete stmt;
				delete con;
			}
			catch (sql::SQLException &e) {
				qDebug() << "# ERR: SQLException in " << __FILE__;
				qDebug() << "(" << __FUNCTION__ << ") on line " << __LINE__;

				qDebug() << "# ERR: " << e.what();
				qDebug() << " (MySQL error code: " << e.getErrorCode();
			}
		}
		else
			qDebug() << "Erreur lors de l'ouverture du fichier";
	}
	
	return ids2;
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
	ofn.lpstrFilter = _T("(*.txt)\0*.TXT\0");
	ofn.Flags = OFN_LONGNAMES | OFN_EXPLORER; // | OFN_ALLOWMULTISELECT  ;

	res = GetSaveFileName(&ofn);
	if (ofn.lpstrFile != nullptr)
	{
		ofstream file(ofn.lpstrFile, ios::out | ios::trunc);

		if (file)
		{
			for (int i = 0; i < ids.size(); ++i)
				file << ids[i] << endl;

			file.close();
		}
		else
			qDebug() << "Erreur lors de l'ouverture du fichier !";
	}
}