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

	int nbCards = 0;
	int i, j, tmp;

	string colorValues;
	string query;

	vector<Card> Cards;
	vector<int> idsPool;
	idsPool = readFile();

	cout << "Lecture de fichier : " << endl;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		sql::Statement *stmt;
		sql::PreparedStatement *pstmt;
		sql::ResultSet *cards_query;
		sql::ResultSet *editions_query;
		sql::ResultSet *types_query;
		sql::ResultSet *subtypes_query;
		sql::ResultSet *supertypes_query;
		sql::ResultSet *capacities_query;
		sql::ResultSet *res;

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
		
		// BLOCS & EDITIONS
		editions_query = stmt->executeQuery(
			"SELECT * FROM mag_setcard AS setc "
			"LEFT JOIN mag_set as edition ON setc.sca_set = edition.set_id "
			"WHERE setc.sca_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli		ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype		ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli	ON card.car_id		= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype		ON cstype.csu_id	= csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (editions_query->next())
		{
			Cards.at(Ids.right.at(editions_query->getInt("sca_card"))).blocs.push_back(editions_query->getInt("set_block"));
			Cards.at(Ids.right.at(editions_query->getInt("sca_card"))).editions.push_back(editions_query->getInt("sca_set"));
		}

		// TYPES
		types_query = stmt->executeQuery(
			"SELECT * FROM mag_cardtypeli AS ctype "
			"WHERE ctype.ctyl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli		ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype		ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli	ON card.car_id		= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype		ON cstype.csu_id	= csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' OR cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (types_query->next())
			Cards.at(Ids.right.at(types_query->getInt("ctyl_card"))).types.push_back(types_query->getInt("ctyl_type"));

		// SUBTYPES
		subtypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsubtypeli AS csubtype "
			"WHERE csubtype.cstl_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli ON card.car_id	= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype ON cstype.csu_id		= csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (subtypes_query->next())
			Cards.at(Ids.right.at(subtypes_query->getInt("cstl_card"))).subtypes.push_back(subtypes_query->getInt("cstl_subtype"));

		// SUPERTYPES
		supertypes_query = stmt->executeQuery(
			"SELECT * FROM mag_cardsupertypeli AS csuptype "
			"WHERE csuptype.csul_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli		ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype		ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli	ON card.car_id		= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype		ON cstype.csu_id	= csupertypeli.csul_supertype "
				"WHERE ctype.cty_name <=> 'Land' AND cstype.csu_name <=> 'Basic' "
				"GROUP BY card.car_id)"
		); 

		// CAPACITIES
		capacities_query = stmt->executeQuery(
			"SELECT * FROM mag_cardcapacityli AS capacity "
			"WHERE capacity.ccal_card NOT IN "
				"(SELECT card.car_id FROM mag_card AS card "
				"LEFT JOIN mag_cardtypeli		AS ctypeli		ON card.car_id		= ctypeli.ctyl_card "
				"LEFT JOIN mag_cardtype			AS ctype		ON ctype.cty_id		= ctypeli.ctyl_type "
				"LEFT JOIN mag_cardsupertypeli	AS csupertypeli	ON card.car_id		= csupertypeli.csul_card "
				"LEFT JOIN mag_cardsupertype	AS cstype		ON cstype.csu_id	= csupertypeli.csul_supertype "
				"WHERE ctype.cty_name = 'Land' AND cstype.csu_name = 'Basic' "
				"GROUP BY card.car_id)"
		);
		while (capacities_query->next())
			Cards.at(Ids.right.at(capacities_query->getInt("ccal_card"))).capacities.push_back(capacities_query->getInt("ccal_capacity"));
		
		// IDS 
		pstmt = con->prepareStatement("SELECT sca_card, sca_multiverseid FROM mag_setcard WHERE sca_multiverseid IN (?)");
		for (i = 0; i < idsPool.size(); ++i) 
		{
			pstmt->setInt(1, idsPool[i]);
			pstmt->executeUpdate();
		}
		res = pstmt->executeQuery();

		idsPool.clear();
		while (res->next())
			idsPool.push_back(res->getInt("sca_card"));

		delete res;
		delete cards_query;
		delete editions_query;
		delete types_query;
		delete subtypes_query;
		delete supertypes_query;
		delete capacities_query;

		delete pstmt;
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

	cout << "Recherche des cartes les plus proches..." << endl;
	map<int, multimap<int, int>> neighbors;
	map<int, multimap<int, int>>::iterator itneighbors;
	map<int, multimap<int, int>>::iterator itneighbors1;
	map<int, multimap<int, int>>::iterator itneighbors2;

	multimap<int, int>::iterator itmm;

	map<int, int> proposals;
	map<int, int>::iterator itprop;

	int max;
	int idMax;
	
	for (i = 0; i < idsPool.size(); ++i)
	{
		idsPool[i] = Ids.left.at(idsPool[i]);

		// Remplissage des voisins de chaque carte du deck
		neighbors.insert(pair<int, multimap<int, int>>(idsPool[i], multimap<int, int>()));
		for (j = 0; j < nbCards; ++j)
		{
			if (idsPool[i] != j)
				neighbors[idsPool[i]].insert(pair<int, int>(graph.Edges[idsPool[i] * nbCards + j].totalValue, j));
		}

		for (itmm = neighbors[idsPool[i]].end(), j = 0; j < NB_NEIGHBORS; ++j, --itmm);
		neighbors[idsPool[i]].erase(neighbors[idsPool[i]].begin(), itmm);

		// Suppression des cartes déjà présentes dans le deck
		for (itmm = neighbors[idsPool[i]].begin(); itmm != neighbors[idsPool[i]].end(); ++itmm)
		{
			for (itneighbors = neighbors.begin(); itneighbors != neighbors.end(); ++itneighbors)
			{
				if (itmm->second == itneighbors->first)
					neighbors[idsPool[i]].erase(itmm);
			}
		}
	}

	for (i = neighbors.size(); i < DECKSIZE; ++i)
	{
		// REMPLISSAGE DES NB PROPOSITIONS
		proposals.clear();
		for (itneighbors = neighbors.begin(); itneighbors != neighbors.end(); ++itneighbors)
		{
			itmm = itneighbors->second.end();
			--itmm;
			// Recherche des voisins les plus proches en faisant la somme des poids
			for (j = 0; j < NB_PROPOSALS; ++j, --itmm)
			{
				if (proposals.find(itmm->second) == proposals.end())
					proposals.insert(pair<int, int>(itmm->second, itmm->first));
				else
					proposals.at(itmm->second) += itmm->first;
			}
		}

		// AJOUT D'UNE CARTE AU DECK
		if (i >= neighbors.size()-1)
		{
			// RECHERCHE DE LA CARTE LA PLUS PROCHE
			max = -1;
			for (itprop = proposals.begin(); itprop != proposals.end(); ++itprop)
			{
				if (itprop->second > max)
				{
					idMax = itprop->first;
					max = itprop->second;
				}
			}
			// AJOUT DE LA CARTE AU DECK ET REMPLISSAGE DE SES VOISINS
			neighbors.insert(pair<int, multimap<int, int>>(idMax, multimap<int, int>()));
			for (j = 0; j < nbCards; ++j)
			{
				if (idMax != j)
					neighbors.at(idMax).insert(pair<int, int>(graph.Edges[idMax * nbCards + j].totalValue, j));
			}

			for (itmm = neighbors[idMax].end(), j = 0; j < NB_NEIGHBORS; ++j, --itmm);
			neighbors[idMax].erase(neighbors[idMax].begin(), itmm);

			// Suppression des cartes déjà présentes dans le deck
			for (itneighbors1 = neighbors.begin(); itneighbors1 != neighbors.end(); ++itneighbors1)
			{
				for (itmm = itneighbors1->second.begin(); itmm != itneighbors1->second.end(); ++itmm)
				{
					for (itneighbors2 = neighbors.begin(); itneighbors2 != neighbors.end(); ++itneighbors2)
					{
						if (itmm->second == itneighbors2->first)
							itneighbors1->second.erase(itmm);
					}
				}
			}
		}
	}

	vector<int> deck; 
	for (itneighbors = neighbors.begin(); itneighbors != neighbors.end(); ++itneighbors)
	{
		//cout << itneighbors->first << endl;
		deck.push_back(Ids.right.at(itneighbors->first));
	}
	
	writeFile(deck);
	
	int end;
	cout << "Done, end to return" << endl;
	cin >> end;

	return EXIT_SUCCESS;
}