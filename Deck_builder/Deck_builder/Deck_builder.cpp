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

#define NB_CARDS "20000"

/* COLORS */
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2
#define COLOR_U 3
#define COLOR_W 4

using namespace std;

int main()
{
	cout << "Magic project" << endl;
	cout << endl;

	typedef boost::bimap<int, int> bimap_type;
	bimap_type ids;

	vector<Card> Cards;

	int nbCards = 0;
	int size;
	int i, j;

	__int8 colorValue;
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
		res = stmt->executeQuery("SELECT * FROM mag_card AS card LEFT JOIN mag_cardtypeli AS cardtypelink ON card.car_id = cardtypelink.ctyl_card LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = cardtypelink.ctyl_type LEFT JOIN mag_cardsupertypeli AS cardsupertypelink ON card.car_id = cardsupertypelink.csul_card LEFT JOIN mag_cardsupertype AS cstype ON cstype.csu_id = cardsupertypelink.csul_supertype WHERE NOT (ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic') GROUP BY card.car_id");
		
		while (res->next()) {
			Cards.push_back(Card(res->getInt("car_id"), res->getString("car_name"), res->getString("car_colors"), res->getInt("cty_id"), res->getInt("car_convertedmanacost")));

			ids.insert(bimap_type::value_type(nbCards, res->getInt("car_id")));

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
	
	// Creation du graph
	
	Graph graph(nbCards);
	
	for (i = 0; i < nbCards; ++i) {
		for (j = 0; j < nbCards; ++j) {
			if (i != j) {
				colorValue = graph.matchingColors(Cards[i], Cards[j]);
				graph.Edges[i*nbCards + j].colorValue = colorValue;
			}
		}
	}
	/*
	graph.printGraph();
	cout << "nbCards : " << nbCards << endl;*/

	int tmp;
	cout << "Done, end to return" << endl;
	cin >> tmp;

	return EXIT_SUCCESS;
}