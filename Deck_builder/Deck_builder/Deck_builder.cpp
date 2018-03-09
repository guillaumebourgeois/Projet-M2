/***
Bellamy Lola & Bourgeois-Ducournau Guillaume
M2 DAR - 2017/2018
Projet - Magic
***/

#include "stdafx.h"

using namespace std;

int main()
{
	cout << "Magic project" << endl;
	cout << endl;

	typedef boost::bimap<int, int> bimap_type;
	bimap_type Ids;

	vector<Card> Cards;
	vector<int> idsPool;

	int nbCards = 0;
	int i, j;

	string colorValues;

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

		//res = stmt->executeQuery("SELECT * FROM mag_card LIMIT " NB_CARDS);
		res = stmt->executeQuery(
			"SELECT * "
			"FROM mag_card AS card " 
			"LEFT JOIN mag_cardtypeli AS cardtypelink ON card.car_id = cardtypelink.ctyl_card "
			"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = cardtypelink.ctyl_type "
			"LEFT JOIN mag_cardsupertypeli AS cardsupertypelink ON card.car_id = cardsupertypelink.csul_card "
			"LEFT JOIN mag_cardsupertype AS cstype ON cstype.csu_id = cardsupertypelink.csul_supertype "
			"LEFT JOIN mag_setcard AS edition ON edition.sca_card = card.car_id "
			"WHERE NOT (ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic') GROUP BY card.car_id "
			"LIMIT " NB_CARDS
		);
		while (res->next()) {
			Cards.push_back(
				Card(
					res->getInt("car_id"), 
					res->getString("car_name"), 
					res->getString("car_colors"), 
					res->getInt("cty_id"), 
					res->getInt("car_convertedmanacost"),
					res->getInt("sca_set")
				)
			);

			Ids.insert(bimap_type::value_type(nbCards, res->getInt("car_id")));

			++nbCards;
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
	
	// Creation du graphe et des arêtes
	
	Graph graph(nbCards);
	graph.createEdges(Cards);
	
	//graph.printGraph();

	idsPool = readFile();

	cout << "Lecture de fichier : " << endl;
	for (i = 0; i < idsPool.size(); ++i)
		cout << idsPool[i] << endl;

	writeFile(idsPool);

	int end;
	cout << "Done, end to return" << endl;
	cin >> end;

	return EXIT_SUCCESS;
}