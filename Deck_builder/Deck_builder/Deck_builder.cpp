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
		sql::ResultSet *cards_query;
		sql::ResultSet *editions_query;
		sql::ResultSet *types_query;
		sql::ResultSet *subtypes_query;
		sql::ResultSet *supertypes_query;

		cout << "Connection to MySQL Database..." << endl;
		/* Create a connection */
		driver = get_driver_instance();
		con = driver->connect(HOST, USER, PASS);
		/* Connect to the MySQL database */
		con->setSchema(DB);

		stmt = con->createStatement();

		//res = stmt->executeQuery("SELECT * FROM mag_card LIMIT " NB_CARDS);
		cards_query = stmt->executeQuery(
			"SELECT * FROM mag_card AS card "
			"LEFT JOIN mag_cardtypeli		AS ctypeli			ON card.car_id		= ctypeli.ctyl_card "
			"LEFT JOIN mag_cardtype			AS ctype			ON ctype.cty_id		= ctypeli.ctyl_type "
			"LEFT JOIN mag_cardsupertypeli	AS csupertypeli		ON card.car_id		= csupertypeli.csul_card "
			"LEFT JOIN mag_cardsupertype	AS cstype			ON cstype.csu_id	= csupertypeli.csul_supertype "
			"WHERE NOT (ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic') GROUP BY card.car_id "
			"LIMIT " NB_CARDS
		);
		editions_query = stmt->executeQuery(
			"SELECT * FROM mag_setcard AS setc "
			"LEFT JOIN mag_set as edition ON setc.sca_set = edition.set_id "
			"WHERE setc.sca_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
		);
		types_query = stmt->executeQuery(
			"SELECT * FROM mag_cardtypeli AS ctype "
			"WHERE ctype.ctyl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
		);
		subtypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsubtypeli AS csubtype "
			"WHERE csubtype.cstl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
		);
		supertypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsupertypeli AS csuptype "
			"WHERE csuptype.csul_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli AS ctypeli ON card.car_id = ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype AS ctype ON ctype.cty_id = ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli AS csupertypeli ON card.car_id = csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id = csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
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
			//cout << res->getInt("car_id") << " " << res->getInt("sca_set") << " " << res->getInt("cty_id") << endl;
			//cout << res->getInt("cst_id") << endl;
			Ids.insert(bimap_type::value_type(nbCards, res->getInt("car_id")));

			//cout << Ids.left.at(nbCards) << " " << Ids.right.at(res->getInt("car_id")) << endl;

			++nbCards;
		}

		int tmp;
		res = stmt->executeQuery(
			"SELECT cstl_card, cstl_subtype FROM mag_cardsubtypeli ");

		/*while (res->next()) {
			tmp = res->getInt("cstl_card");
			cout << tmp << " ";
			if (tmp != NULL)
				tmp = Ids.right.at(tmp);
			cout << tmp << endl;
			//Cards.at(res->getInt("cstl_card")).subtypes.push_back(res->getInt("cstl_subtype"));
		}*/

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
	
	for (i = 0; i < Cards.size(); ++i)
	{
		for (j = 0; j < Cards[i].subtypes.size(); ++j)
			cout << Cards[i].subtypes[j] << " ";
		cout << endl;
	}

	// Creation du graphe et des arêtes
	
	Graph graph(nbCards);
	graph.createEdges(Cards);
	
	//graph.printGraph();

	/*idsPool = readFile();

	cout << "Lecture de fichier : " << endl;
	for (i = 0; i < idsPool.size(); ++i)
		cout << idsPool[i] << endl;

	writeFile(idsPool);
	*/
	int end;
	cout << "Done, end to return" << endl;
	cin >> end;

	return EXIT_SUCCESS;
}