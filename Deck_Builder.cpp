/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic
***/

#include "stdafx.h"

/* DATABASE */
#define HOST "localhost"
#define USER "root"
#define PASS "root"
#define DB "magic_card"

/* COLORS */
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2
#define COLOR_U 3
#define COLOR_W 4

using namespace std;

int matchingColors(Card c1, Card c2)
{
	int cpt = 5;
	for (int i = 0; i < 5; i++) {
		if (c1.colors[i] != c2.colors[i]) {
			cpt--;
		}
	}
	return cpt;
}

int main()
{
	cout << "Magic project" << endl;
	cout << endl;

	int tmp;

	map<int, Card> Cards;
	map<int, Card>::iterator it, it2;
	Edge edgeTmp;
	int valueTmp;

	string colorsString;
	int* colors;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		cout << "Connection to MySQL Database..." << endl;
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(HOST, USER, PASS);
		/* Connect to the MySQL database */
		con->setSchema(DB);

		stmt = con->createStatement();
		res = stmt->executeQuery("SELECT * FROM mag_card LIMIT 200");

		while (res->next()) {
			colors = new int[5];
			colorsString = res->getString("car_colors");
			if (colorsString.find("B") != -1)
				colors[0] = 1;
			else
				colors[0] = 0;
			if (colorsString.find("G") != -1)
				colors[1] = 1;
			else
				colors[1] = 0;
			if (colorsString.find("R") != -1)
				colors[2] = 1;
			else
				colors[2] = 0;
			if (colorsString.find("U") != -1)
				colors[3] = 1;
			else
				colors[3] = 0;
			if (colorsString.find("W") != -1)
				colors[4] = 1;
			else
				colors[4] = 0;

			Cards.insert(pair<int, Card>(res->getInt("car_id"), Card(res->getString("car_name"), colors)));
		}

		delete res;
		delete stmt;
		delete con;
	}
	catch (sql::SQLException &e) {
		/*
		MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		return EXIT_FAILURE;
	}

	// Creation du graph
	Graph graph(Cards.size());
	for (it = Cards.begin(); it != Cards.end(); ++it) {
		for (it2 = Cards.begin(); it2 != Cards.end(); ++it2) {
			if (valueTmp = matchingColors(it->second, it2->second)) {
				edgeTmp.idCard1 = it->second.idCard;
				edgeTmp.idCard2 = it2->second.idCard;
				edgeTmp.colorValue = valueTmp;
				graph.addEdge(edgeTmp);
			}
		}
	}

	//graph.printGraph();

	cout << "Done." << endl;

	cout << "'end' to return" << endl;
	cin >> tmp;

	return EXIT_SUCCESS;
}
