/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "Deck_builder.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	/*
	int i, j, tmp;

	vector<int> idsPool;
	Graph G = Graph();
	G.createCards();
	G.createEdges();

	idsPool = readFile();

	//graph.printGraph();

	*/

	QApplication app(argc, argv);
	Deck_builder widget;
	widget.showMaximized();
	
	//widget.initiate();

	return app.exec();
}
