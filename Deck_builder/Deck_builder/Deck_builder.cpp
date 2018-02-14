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
#define DB "magic"

#define NB_CARDS 5000

/* COLORS */
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2
#define COLOR_U 3
#define COLOR_W 4

using namespace std;

__int8 matchingColors(Card c1, Card c2)
{
	__int8 nbCommons = 0;
	__int8 nbColorc1 = 0;
	__int8 nbColorc2 = 0;
	
	for (int i = 0; i < 5; ++i) {
		if (c1.colors[i] == 1 && c1.colors[i] == c2.colors[i]) {
			++nbCommons;
			++nbColorc1;
			++nbColorc2;
		}
		if (c1.colors[i] == 1) {
			++nbColorc1;
		}
		if (c2.colors[i] == 1) {
			++nbColorc2;
		}
	}
	if (nbCommons == 0) {
		return 0;
	}
	else {
		return (5 - (max(nbColorc1, nbColorc2) - nbCommons));
	}
}

int main()
{
	cout << "Magic project" << endl;
	cout << endl;

	map<int, Card> Cards;
	map<int, Card>::iterator it, it2;

	Edge edgeTmp;
	int valueTmp;
	int cpt1, cpt2;

	string colorsString;
	char* colors;

	string query;

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
		//query = "SELECT * FROM mag_card " + to_string(NB_CARDS);
		//res = stmt->executeQuery(query);
		res = stmt->executeQuery("SELECT * FROM mag_card LIMIT 15000");

		while (res->next()) {
			colors = new __int8[5];
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

			Cards.insert(pair<int, Card>(res->getInt("car_id"), Card(res->getInt("car_id"), res->getString("car_name"), colors)));
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

	cpt1 = 0;
	cpt2 = 0;
	// Creation du graph
	Graph graph(Cards.size());
	for (it = Cards.begin(); it != Cards.end(); ++it) {
		for (it2 = Cards.begin(); it2 != Cards.end(); ++it2) {
			if (valueTmp = matchingColors(it->second, it2->second)) {
				edgeTmp.idEdge = cpt1;
				edgeTmp.idCard1 = it->second.idCard;
				edgeTmp.idCard2 = it2->second.idCard;
				edgeTmp.colorValue = valueTmp;

				graph.addEdge(edgeTmp);
				//cout << valueTmp << " ";
				++cpt1;
			}
			else
				++cpt2;
		}
	}

	//cout << "cpt2 : " << cpt2 << endl;
	//cout << "cpt1 : " << cpt1 << endl;
	//graph.printGraph();

	cout << "Size : " << graph.edges.size() << endl;

	cout << "Done." << endl;

	int tmp;
	cout << "'end' to return" << endl;
	cin >> tmp;

	return EXIT_SUCCESS;
}