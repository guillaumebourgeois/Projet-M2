/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume 
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "stdafx.h"

#define HOST "localhost"
#define USER "root"
#define PASS "root"
#define DB "magic"

using namespace std;

int main()
{
	cout << "Magic Card project" << endl;
	cout << endl;

	map<int, Card> Cards;
	map<int, Card>::iterator it;
	Edge** Edges;

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
		res = stmt->executeQuery("SELECT * FROM mag_card LIMIT 10000");
		
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

	for (it = Cards.begin(); it != Cards.end(); ++it)
		cout << it->first << " " << it->second.name << " " << it->second.colors[0] << it->second.colors[1] << it->second.colors[2] << it->second.colors[3]
		<< it->second.colors[4] << endl;

	cout << "Done." << endl;

	int tmp;
	cout << "Press enter to return" << endl;
	cin >> tmp;

	return EXIT_SUCCESS;
}
