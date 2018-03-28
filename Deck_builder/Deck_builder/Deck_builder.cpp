/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "Deck_builder.h"

using namespace std;

Deck_builder::Deck_builder(QWidget *parent)
	: QMainWindow(parent)
{
	int i, j, k, size;

	ui.setupUi(this);

	// Vectors of labels
	this->proposals.resize(NB_PROPOSALS);
	this->deck.resize(DECKSIZE);
	this->buttons.resize(NB_PROPOSALS);

	//this->nbCards = 0;

	// Config initialisation
	this->configOpened = false;
	this->deckOpened = false;

	this->colorCoef = 0;
	this->typeCoef = 0;
	this->subtypeCoef = 0;
	this->capacityCoef = 0;
	this->editionCoef = 0;
	this->influenceCoef = 0;

	this->algorithm = 0;

	this->spellsPart = 0;
	this->creaturesPart = 0;
	this->mana = 0;
	this->nbColors = 0;

	for (i = 0; i < NB_COLORS; ++i)
		this->colors[i] = 0;

	for (i = 0; i < 8; ++i)
		this->influence[i] = 0;

	// Connect buttons
	connect(ui.openConfigButton	, SIGNAL(clicked()), this, SLOT(handleOpenConfigButton()));
	connect(ui.initiateButton	, SIGNAL(clicked()), this, SLOT(handleInitiateButton()));
	connect(ui.openDeckButton	, SIGNAL(clicked()), this, SLOT(handleOpenDeckButton()));
	connect(ui.saveDeckButton	, SIGNAL(clicked()), this, SLOT(handleSaveDeckButton()));
	connect(ui.resetDeckButton	, SIGNAL(clicked()), this, SLOT(handleResetDeckButton()));
	connect(ui.resetGraphButton	, SIGNAL(clicked()), this, SLOT(handleResetGraphButton()));

	ui.initiateButton->setEnabled(false);
	ui.saveDeckButton->setEnabled(false);
	ui.openDeckButton->setEnabled(false);

	// Initiate proposals box, scroll area, widget, labels
	ui.proposalsBox->setFixedHeight(445);
	ui.proposalsBox->setFixedWidth(1720);
	ui.proposalsBox->move(QPoint(200, 0));

	ui.proposalsArea->setFixedHeight(405);
	ui.proposalsArea->setFixedWidth(1720);
	ui.proposalsArea->move(QPoint(0, 40));

	QWidget *proposalsWidget = new QWidget();
	proposalsWidget->setFixedHeight(380);
	proposalsWidget->setFixedWidth(NB_PROPOSALS * (MARGIN + WIDTHLABEL) + MARGIN);
	ui.proposalsArea->setWidget(proposalsWidget);

	for (i = 0; i < NB_PROPOSALS; ++i)
	{
		this->proposals[i] = new QLabel("proposalsLabel", proposalsWidget);
		this->proposals[i]->setFixedWidth(WIDTHLABEL);
		this->proposals[i]->setFixedHeight(HEIGHTLABEL);
		this->proposals[i]->move(QPoint(MARGIN + i * (MARGIN + WIDTHLABEL), MARGIN));

		this->proposals[i]->clear();

		this->buttons[i] = new AddButton(proposalsWidget);
		this->buttons[i]->move(QPoint(MARGIN + i * (MARGIN + WIDTHLABEL), MARGIN + HEIGHTLABEL + 10));
		this->buttons[i]->setEnabled(false);

		connect(this->buttons[i], SIGNAL(clicked()), &this->mapper, SLOT(map()));

		this->mapper.setMapping(this->buttons[i], i);
	}

	connect(&this->mapper, SIGNAL(mapped(int)), this, SLOT(handleAddButton(int)));

	// Initiate deck box, scroll area, widget, labels
	ui.deckBox->setFixedHeight(709);
	ui.deckBox->setFixedWidth(1720);
	ui.deckBox->move(QPoint(200, 445));

	ui.deckArea->setFixedHeight(569);
	ui.deckArea->setFixedWidth(1720);
	ui.deckArea->move(QPoint(0, 40));

	QWidget *deckWidget = new QWidget();
	deckWidget->setFixedWidth(1720);
	deckWidget->setFixedHeight((DECKSIZE/5) * (MARGIN + HEIGHTLABEL) + MARGIN);
	ui.deckArea->setWidget(deckWidget);

	for (k = 0, i = 0; i < DECKSIZE; ++k)
	{
		for (j = 0; j < 7 && i < this->deck.size(); ++j, ++i)
		{
			this->deck[i] = new QLabel("deckLabel", deckWidget);
			this->deck[i]->setFixedWidth(WIDTHLABEL);
			this->deck[i]->setFixedHeight(HEIGHTLABEL);
			this->deck[i]->move(QPoint(MARGIN +  j * (MARGIN + WIDTHLABEL), MARGIN + k * (MARGIN + HEIGHTLABEL)));

			this->deck[i]->clear();
		}
	}
}

void Deck_builder::setProposals()
{
	QString url;
	QPixmap image;

	int i, multiverseid, choice;

	multimap<int, int> proposals;
	multimap<int, int>::iterator itprop;

	switch (this->algorithm)
	{
		case 0:
			proposals = this->G.heavyNeighbour(this->idsPool, this->influence);
			break;
		case 1:
			proposals = this->G.closestNeighbours(this->idsPool);
			break;
		case 2:
			break;
		case 3:
			break;
	}

	for (i = 0, itprop = proposals.end(); i < NB_PROPOSALS && itprop != proposals.begin(); ++i)
	{
		do {
			--itprop;
			multiverseid = this->G.Cards[this->G.Ids.right.at(itprop->second)].multivereid;

			url = QString::number(multiverseid);
			url.push_front(R"(C:\Users\guill\Desktop\cards\)");
			url.push_back(".jpg");

			image.load(url);
			// Affichage de la carte 0 (chargement de l'image impossible)
			/*if (image.isNull())
			{
				url = QString(R"(C:\Users\guill\Desktop\cards\0.jpg)");
				image.load(url);
			}*/

			this->proposals[i]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));

			this->buttons[i]->setText(QString::number(itprop->first));
			this->buttons[i]->id = itprop->second;
		} while (image.isNull() && itprop != proposals.end());
	}
}

// STATS CALCUL
void Deck_builder::generateStats()
{
	int i, j, id, type;
	int creaturesU = 0, spellsU = 0;
	int nbCards = this->idsPool.size();
	int nbColorsU = 0;
	int colorsU[NB_COLORS];

	float mana = 0.0, creatures = 0.0, spells = 0.0;
	float colorsPercent[5];

	for (i = 0; i < NB_COLORS; ++i)
	{
		colorsU[i] = 0;
		colorsPercent[i] = 0.0;
	}

	for (i = 0; i < nbCards; ++i)
	{
		// ID de la carte dans le vector de cards
		id = this->G.Ids.right.at(this->idsPool[i]);

		// Cout en mana
		mana += (float)this->G.Cards[id].manaCost;
		
		// Récupération des types de la carte
		for (j = 0; j < this->G.Cards[id].types.size(); ++j)
		{
			type = (int)this->G.Cards[id].types[j];

			switch (type)
			{
			case 3:
				++creaturesU;
				break;
			case 5:
				++spellsU;
				break;
			case 6:
				++spellsU;
				break;
			case 7:
				++spellsU;
				break;
			case 14:
				++spellsU;
				break;
			}
		}

		// Récupération des couleurs de la carte
		for (j = 0; j < NB_COLORS; ++j)
		{
			if (this->G.Cards[id].colors[j] == true)
			{
				++colorsU[j];
				++nbColorsU;
			}
		}
	}

	mana /= (nbCards);
	creatures = (float)creaturesU / (float)nbCards * 100.0;
	spells = (float)spellsU / (float)nbCards * 100.0;

	for (i = 0; i < NB_COLORS; ++i)
		colorsPercent[i] = (float)colorsU[i] / (float)nbColorsU * 100.0;

	// influence[0] = spells
	// influence[1] = creatures
	// influence[2] = mana
	// influence[3-7] = colors
	this->influence[0] = round((this->spellsPart - spells) / 2);
	this->influence[1] = round((this->creaturesPart - (int)creatures) / 2);
	this->influence[2] = (this->mana*10) - (int)(mana*10);

	for (i = 0; i < NB_COLORS; ++i)
	{
		if (this->colors[i] == 1)
			this->influence[3 + i] = (100 / this->nbColors) - (int)colorsPercent[i];
		else
			this->influence[3 + i] = 0;
	}

	for (i = 0; i < 8; ++i)
		qDebug() << this->influence[i];

	ui.nbCards->setText(QString::number(nbCards));

	ui.manaU->setText(QString("%1").arg(mana, 2, 'f', 2));
	
	ui.creaturesU->setText(QString::number(creaturesU));
	ui.creaturesPercent->setText(QString("%1").arg(creatures, 2, 'f', 0));

	ui.spellsU->setText(QString::number(spellsU));
	ui.spellsPercent->setText(QString("%1").arg(spells, 2, 'f', 0));

	// colors[0] = blanc
	// colors[1] = bleu
	// colors[2] = noir
	// colors[3] = rouge
	// colors[4] = vert

	ui.whiteU->setText(QString::number(colorsU[0]));
	ui.whitePercent->setText(QString("%1").arg(colorsPercent[0], 2, 'f', 0));

	ui.blueU->setText(QString::number(colorsU[1]));
	ui.bluePercent->setText(QString("%1").arg(colorsPercent[1], 2, 'f', 0));

	ui.blackU->setText(QString::number(colorsU[2]));
	ui.blackPercent->setText(QString("%1").arg(colorsPercent[2], 2, 'f', 0));

	ui.greenU->setText(QString::number(colorsU[4]));
	ui.greenPercent->setText(QString("%1").arg(colorsPercent[4], 2, 'f', 0));

	ui.redU->setText(QString::number(colorsU[3]));
	ui.redPercent->setText(QString("%1").arg(colorsPercent[3], 2, 'f', 0));
}


// BUTTONS FUNCTIONS
void Deck_builder::handleAddButton(int j)
{
	QString url;
	QPixmap image;

	int i, multiverseid;

	if (this->nbCards < DECKSIZE)
	{
		this->idsPool.push_back(this->buttons[j]->id);

		multiverseid = this->G.Cards[this->G.Ids.right.at(this->buttons[j]->id)].multivereid;
		
		url = QString::number(multiverseid);
		url.push_front(R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");

		image.load(url);
		this->deck[this->nbCards]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));

		++this->nbCards;
		
		this->setProposals();

		this->generateStats();
	}
	else
	{
		for (i = 0; i < NB_PROPOSALS; ++i)
		{
			this->buttons[i]->setEnabled(false);
			this->buttons[i]->setText("");
			this->proposals[i]->clear();
		}
	}
}

void Deck_builder::handleOpenConfigButton()
{
	int res, i;
	
	string buffer;

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
			this->colorCoef = 0;
			this->typeCoef = 0;
			this->subtypeCoef = 0;
			this->capacityCoef = 0;
			this->editionCoef = 0;
			this->influenceCoef = 0;

			this->algorithm = 0;

			this->spellsPart = 0;
			this->creaturesPart = 0;
			this->mana = 0;
			this->nbColors = 0;

			file >> buffer >> this->colorCoef;
			file >> buffer >> this->typeCoef;
			file >> buffer >> this->subtypeCoef;
			file >> buffer >> this->capacityCoef;
			file >> buffer >> this->editionCoef;
			file >> buffer >> this->influenceCoef;

			file >> buffer >> this->algorithm;

			file >> buffer >> this->spellsPart;
			file >> buffer >> this->creaturesPart;
			file >> buffer >> this->mana;

			// colors[0] = blanc
			// colors[1] = bleu
			// colors[2] = noir
			// colors[3] = rouge
			// colors[4] = vert
			for (i = 0; i < NB_COLORS; ++i)
			{
				file >> buffer >> this->colors[i];
				if (this->colors[i] == 1)
					++this->nbColors;
			}
			file.close();

			ui.nbColors->setText(QString::number(this->nbColors));
			ui.mana->setText(QString::number(this->mana));
			ui.creaturesPart->setText(QString::number(this->creaturesPart));
			ui.spellsPart->setText(QString::number(this->spellsPart));

			ui.initiateButton->setEnabled(true);
		}
		else
			qDebug() << "Erreur lors de l'ouverture du fichier";
	}
}

void Deck_builder::handleInitiateButton()
{
	std::clock_t start;

	this->G = Graph();
	this->G.createCards();
	this->G.createEdges(this->colorCoef, this->typeCoef, this->subtypeCoef, this->capacityCoef, this->editionCoef);
	
	ui.openDeckButton->setEnabled(true);
}

void Deck_builder::handleOpenDeckButton()
{
	QString url;
	QPixmap image;

	int i, j, multiverseid, tmp;

	bimap_type proposals;
	bimap_type::right_iterator itprop;

	this->idsPool = readFile();
	tmp = this->idsPool.size();
	if (tmp != 0)
	{
		this->nbCards = this->idsPool.size();

		for (int i = 0; i < this->idsPool.size(); ++i)
		{
			multiverseid = this->G.Cards[this->G.Ids.right.at(this->idsPool[i])].multivereid;

			url = QString::number(multiverseid);
			url.push_front(R"(C:\Users\guill\Desktop\cards\)");
			url.push_back(".jpg");

			image.load(url);
			this->deck[i]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL)));
		}

		for (i = 0; i < this->buttons.size(); ++i)
			this->buttons[i]->setEnabled(true);

		this->generateStats();

		this->setProposals();

		ui.saveDeckButton->setEnabled(true);
	}
}

void Deck_builder::handleSaveDeckButton()
{
	writeFile(this->idsPool);
}

void Deck_builder::handleResetDeckButton()
{
	int i;
	this->idsPool.clear();
	this->idsPool.resize(0);

	for (i = 0; i < NB_PROPOSALS; ++i)
	{
		this->buttons[i]->setEnabled(false);
		this->buttons[i]->setText("Poids");
		this->proposals[i]->clear();
	}
	for (i = 0; i < DECKSIZE; ++i)
		this->deck[i]->clear();

	ui.whiteU->setText("0");
	ui.blueU->setText("0");
	ui.blackU->setText("0");
	ui.redU->setText("0");
	ui.greenU->setText("0");
	ui.creaturesU->setText("0");
	ui.spellsU->setText("0");
	ui.manaU->setText("0");

	ui.whitePercent->setText("0");
	ui.bluePercent->setText("0");
	ui.blackPercent->setText("0");
	ui.redPercent->setText("0");
	ui.greenPercent->setText("0");
	ui.creaturesPercent->setText("0");
	ui.spellsPercent->setText("0");

	ui.nbCards->setText("0");

	ui.saveDeckButton->setEnabled(false);
}

void Deck_builder::handleResetGraphButton()
{
	this->G.Edges.clear();

	ui.openDeckButton->setEnabled(false);
}