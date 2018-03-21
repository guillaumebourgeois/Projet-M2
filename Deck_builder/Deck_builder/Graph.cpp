/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "Graph.h"

using namespace std;

Graph::Graph()
{
}

void Graph::createCards()
{
	int nbCards = 0;
	int id;
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
			this->Cards.push_back(
				Card(
					cards_query->getInt("car_id"),
					cards_query->getString("car_colors"),
					cards_query->getString("car_name"),
					cards_query->getInt("car_convertedmanacost")
				)
			);

			//cout << cards_query->getInt("car_id") << " ";
			this->Ids.insert(bimap_type::value_type(nbCards, cards_query->getInt("car_id")));

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
			id = this->Ids.right.at(editions_query->getInt("sca_card"));
			this->Cards.at(id).blocs.push_back(editions_query->getInt("set_block"));
			this->Cards.at(id).editions.push_back(editions_query->getInt("sca_set"));
			if (this->Cards.at(id).multivereid == -1)
				this->Cards.at(id).multivereid = editions_query->getInt("sca_multiverseid");
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
			this->Cards.at(this->Ids.right.at(types_query->getInt("ctyl_card"))).types.push_back(types_query->getInt("ctyl_type"));

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
			this->Cards.at(this->Ids.right.at(subtypes_query->getInt("cstl_card"))).subtypes.push_back(subtypes_query->getInt("cstl_subtype"));

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
			this->Cards.at(this->Ids.right.at(capacities_query->getInt("ccal_card"))).capacities.push_back(capacities_query->getInt("ccal_capacity"));

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
	}

	this->nbCards = nbCards;
	this->Edges.resize(nbCards*nbCards);
}

void Graph::createEdges(int colorCoef, int editionCoef, int typeCoef, int subtypeCoef, int capacityCoef)
{
	map<int, int> results;

	bitset<5> nbCommonsBits;
	int nbColorc1, nbColorc2, commons;
	int i, j, k, l;
	int colorValue, editionValue, typeValue, capacityValue, subtypeValue, totalValue;
	int maxTypeValue = 0, maxSubtypeValue = 0, maxCapacityValue = 0, maxTotalValue = 0;

	int n = this->nbCards;

	//cout << n << endl;

	for (i = 0; i < n; ++i) {
		for (j = 0; j < n; ++j) {
			if (i != j)
			{
				// COLORS
				nbCommonsBits = this->Cards[i].colors & this->Cards[j].colors;

				nbColorc1 = this->Cards[i].colors.count();
				nbColorc2 = this->Cards[j].colors.count();

				commons = nbCommonsBits.count();

				if (commons == 0)
					colorValue = 0;
				else if (nbColorc1 == 0 || nbColorc2 == 0)
					colorValue = 3;
				else
					colorValue = (NB_COLORS - (max(nbColorc1, nbColorc2) - commons));

				// EDITION
				editionValue = 0;
				k = 0;
				l = 0;
				while (editionValue == 0 && k < this->Cards[i].editions.size())
				{
					while (editionValue == 0 && l < this->Cards[j].editions.size())
					{
						if (this->Cards[i].editions[k] == this->Cards[j].editions[l])
							editionValue = 2;
						++l;
					}
					++k;
				}
				k = 0;
				l = 0;
				while (editionValue == 0 && k < this->Cards[i].blocs.size())
				{
					while (editionValue == 0 && l < this->Cards[j].blocs.size())
					{
						if (this->Cards[i].blocs[k] == this->Cards[j].blocs[l])
							editionValue = 1;
						++l;
					}
					++k;
				}

				// SUBTYPES
				subtypeValue = 0;
				for (k = 0; k < this->Cards[i].subtypes.size(); ++k)
				{
					for (l = 0; l < this->Cards[j].subtypes.size(); ++l)
					{
						if (this->Cards[i].subtypes[k] == this->Cards[j].subtypes[l])
							++subtypeValue;
					}
				}
				if (subtypeValue > maxSubtypeValue)
					maxSubtypeValue = subtypeValue;

				// TYPES
				typeValue = 0;
				for (k = 0; k < this->Cards[i].types.size(); ++k)
				{
					for (l = 0; l < this->Cards[j].types.size(); ++l)
					{
						if (this->Cards[i].types[k] == this->Cards[j].types[l])
							++typeValue;
					}
				}
				if (typeValue > maxTypeValue)
					maxTypeValue = typeValue;

				// CAPACITIES
				capacityValue = 0;
				for (k = 0; k < this->Cards[i].capacities.size(); ++k)
				{
					for (l = 0; l < this->Cards[j].capacities.size(); ++l)
					{
						if (this->Cards[i].capacities[k] == this->Cards[j].capacities[l])
							++capacityValue;
					}
				}
				if (capacityValue > maxCapacityValue)
					maxCapacityValue = capacityValue;

				// TOTAL
				/*totalValue =
					colorValue * COEF_COLOR +
					editionValue * COEF_EDITION +
					subtypeValue * COEF_SUBTYPE +
					typeValue * COEF_TYPE +
					capacityValue * COEF_CAPACITY;*/

				totalValue =
					colorValue		* colorCoef		+
					editionValue	* editionCoef	+
					typeValue		* typeCoef		+
					subtypeValue	* subtypeCoef	+
					capacityValue	* capacityCoef	;

				if (totalValue > maxTotalValue)
					maxTotalValue = totalValue;

				if (results.find(totalValue) == results.end())
					results.insert(pair<int, int>(totalValue, 1));
				else
					++results[totalValue];

				this->Edges[i*nbCards + j] = totalValue;
				//if (editionValue != 0)
				//cout << colorValue << " " << editionValue << "   " << (int)this->Edges[i*nbCards + j].totalValue << endl;
			}
		}
	}
	//cout << maxSubtypeValue << " " << maxTypeValue << " " << maxCapacityValue << endl;
	cout << endl << "Max total value : " << maxTotalValue << endl;
	map<int, int>::iterator it;
	for (it = results.begin(); it != results.end(); ++it)
		cout << it->first << " " << it->second << endl;
}

void Graph::printGraph()
{
	for (int i = 0; i < this->Edges.size(); ++i) {
		//cout << "Carte 1 : " << this->edges[i].idCard1 << " ; Carte 2 : " << this->edges[i].idCard2 << " ; Valeur : " << this->edges[i].colorValue << endl;
		//cout << unsigned(this->Edges[i].totalValue) << " ";
	}

	//cout << "nbCards : " << this->nbCards << endl;
	cout << "Total : " << (int)this->Edges.size() << " liens." << endl;
}

// Resolution algorithms 

Card* usingDynamicGraph(std::vector<Card> cards, std::vector<Card> allCards, std::vector<__int8> matrix, boost::bimap<int, int> ids)
{

}

vector<int> Graph::heavyNeighbour(vector<int> idsPool)
{
	int i, j, k;
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
		int nbCards = this->nbCards;
		idsPool[i] = this->Ids.left.at(idsPool[i]);

		// Remplissage des voisins de chaque carte du deck
		neighbors.insert(pair<int, multimap<int, int>>(idsPool[i], multimap<int, int>()));
		for (j = 0; j < nbCards; ++j)
		{
			if (idsPool[i] != j)
				neighbors[idsPool[i]].insert(pair<int, int>(this->Edges[idsPool[i] * nbCards + j], j));
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
		if (i >= neighbors.size() - 1)
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
					neighbors.at(idMax).insert(pair<int, int>(this->Edges[idMax * nbCards + j], j));
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
		//cout << endl << endl;
	}

	vector<int> deck;
	for (itneighbors = neighbors.begin(); itneighbors != neighbors.end(); ++itneighbors)
	{
		//cout << itneighbors->first << endl;
		deck.push_back(this->Ids.right.at(itneighbors->first));
	}

	//writeFile(deck);

	return deck;
}

int* Graph::distanceSum(std::vector<int> cards)
{
	std::map<int, int> tmp;
	std::map<int, int> res;
	int *selectedCards = (int*)malloc(10 * sizeof(int));
	int *max = (int*)calloc(10, sizeof(int));

	for (int i : cards) {
		for (Card j : this->Cards) {
			if (tmp[j.idCard]) {
				tmp[j.idCard] += this->Edges[this->Ids.left.at(i) * this->Cards.size() + this->Ids.left.at(j.idCard)];
			}
			else {
				tmp[j.idCard] = this->Edges[this->Ids.left.at(i) * this->Cards.size() + this->Ids.left.at(j.idCard)];
			}
		}
	}

	for (auto it : res) {
		for (int i = 0; i < 10; i++) {
			if (max[i] < it.second) {
				max[i] = it.second;
				res[i] = it.first;
			}
		}
	}

	for (int i = 0; i < 10; i++) {
		selectedCards[i] = res[i];
	}

	free(max);
	tmp.clear();
	res.clear();

	return selectedCards;
}



Graph::~Graph()
{
}