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
	int i, j, tmp;

	string colorValues;

	string query;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *cards_query;
		sql::ResultSet *editions_query;
		sql::ResultSet *types_query;
		sql::ResultSet *subtypes_query;
		sql::ResultSet *supertypes_query;
		sql::ResultSet *capacities_query;
		//sql::ResultSet *res;

		cout << "Connection to MySQL Database..." << endl;
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(HOST, USER, PASS);
		/* Connect to the MySQL database */
		con->setSchema(DB);

		stmt = con->createStatement();

		// Récupération des cartes
		cards_query = stmt->executeQuery(
			"SELECT * FROM mag_card AS card "
			"LEFT JOIN mag_cardtypeli		AS ctypeli			ON card.car_id		= ctypeli.ctyl_card "
			"LEFT JOIN mag_cardtype			AS ctype			ON ctype.cty_id		= ctypeli.ctyl_type "
			"LEFT JOIN mag_cardsupertypeli	AS csupertypeli		ON card.car_id		= csupertypeli.csul_card "
			"LEFT JOIN mag_cardsupertype	AS cstype			ON cstype.csu_id	= csupertypeli.csul_supertype "
			"WHERE NOT (cstype.csu_name <=> 'Basic' AND ctype.cty_name <=> 'Land') "
			"GROUP BY card.car_id "
			"LIMIT " NB_CARDS
		);

		while (cards_query->next()) {
			Cards.push_back(
				Card(
					cards_query->getInt("car_id"),
					cards_query->getString("car_colors"),
					cards_query->getString("car_name"),
					cards_query->getInt("car_convertedmanacost")
				)
			);

			//cout << cards_query->getInt("car_id") << " ";
			Ids.insert(bimap_type::value_type(nbCards, cards_query->getInt("car_id")));

			++nbCards;
		}
		
		// Récupération des blocs et éditions
		editions_query = stmt->executeQuery(
			"SELECT * FROM mag_setcard AS setc "
			"LEFT JOIN mag_set as edition ON setc.sca_set = edition.set_id "
			"WHERE setc.sca_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (editions_query->next())
		{
			Cards.at(Ids.right.at(editions_query->getInt("sca_card"))).blocs.push_back(editions_query->getInt("set_block"));
			Cards.at(Ids.right.at(editions_query->getInt("sca_card"))).editions.push_back(editions_query->getInt("sca_set"));
		}

		// Récupération des types
		types_query = stmt->executeQuery(
			"SELECT * FROM mag_cardtypeli AS ctype "
			"WHERE ctype.ctyl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli		ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype		ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli	ON card.car_id		= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype		ON cstype.csu_id	= csupertypeli.csul_supertype "
				"WHERE (ctype.cty_name <=> 'Land' OR cstype.csu_name <=> 'Basic') "
				"GROUP BY card.car_id)"
		);
		while (types_query->next())
			Cards.at(Ids.right.at(types_query->getInt("ctyl_card"))).types.push_back(types_query->getInt("ctyl_type"));

		// Récupération des sous-types
		subtypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsubtypeli AS csubtype "
			"WHERE csubtype.cstl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (types_query->next())
			Cards.at(Ids.right.at(subtypes_query->getInt("cstl_card"))).subtypes.push_back(subtypes_query->getInt("cstl_type"));

		// Récupération des super-types
		supertypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsupertypeli AS csuptype "
			"WHERE csuptype.csul_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		); 

		// Récupération des capacités
		capacities_query = stmt->executeQuery(
			"SELECT * FROM mag_cardcapacityli AS capacity "
			"WHERE capacity.ccal_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (types_query->next())
			Cards.at(Ids.right.at(capacities_query->getInt("ccal_card"))).capacities.push_back(capacities_query->getInt("ccal_capacity"));

		//delete res;
		delete cards_query;
		delete editions_query;
		delete types_query;
		delete subtypes_query;
		delete supertypes_query;
		delete capacities_query;

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
	cout << "Creation du graphe..." << endl;

	Graph graph(nbCards);
	graph.createEdges(Cards);
	
	//graph.printGraph();

	/*idsPool = readFile();

	cout << "Lecture de fichier : " << endl;
	for (i = 0; i < idsPool.size(); ++i)
		cout << idsPool[i] << endl;

	writeFile(idsPool);*/
	
	int end;
	cout << "Done, end to return" << endl;
	cin >> end;

	return EXIT_SUCCESS;
}