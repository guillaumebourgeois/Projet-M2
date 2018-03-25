/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Deck_builder.h"

#include "Graph.h"
#include "stdafx.h"

class Deck_builder : public QMainWindow
{
	Q_OBJECT

public:
	Ui::Deck_builderClass ui;
	
	// Labels
	std::vector<QLabel*> proposals;
	std::vector<QLabel*> deck;

	QVector<AddButton*> buttons;
	QSignalMapper mapper;

	// Config
	bool configOpened;
	bool deckOpened;

	int colorCoef;
	int typeCoef;
	int subtypeCoef;
	int capacityCoef;
	int editionCoef;
	
	int algorithm;

	int spellsPart;
	int creaturesPart;
	int mana;
	int nbColors;

	// Deck
	int nbCards;

	Graph G;

	std::vector<int> idsPool;

	// Constructor
	Deck_builder(QWidget *parent = Q_NULLPTR);

	void setProposals();
	void generateStats();

private slots:
	void handleAddButton(int);

	void handleOpenConfigButton();
	void handleInitiateButton();
	void handleOpenDeckButton();
	void handleResetDeckButton();
	void handleResetGraphButton();
	void handleSaveDeckButton();
};
