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
	Deck_builder(QWidget *parent = Q_NULLPTR);

	void handleOpenButton();
	void handleSaveButton();
	void handleAddButton();

	void initiate();

private:
	Ui::Deck_builderClass ui;
	
	// Labels
	std::vector<QLabel*> proposals;
	std::vector<QLabel*> deck;
	QVector<QPushButton*> buttons;

	std::vector<int> idsPool;

	Graph G;
};
