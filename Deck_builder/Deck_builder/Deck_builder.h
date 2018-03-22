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

	int nbCards;

	std::vector<int> idsPool;

	Graph G;

	Deck_builder(QWidget *parent = Q_NULLPTR);

	void initiate();
	void setProposals();

private slots:
	void handleAddButton(int);
};
