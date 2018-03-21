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
	QString url = R"(C:\Users\guill\Desktop\cards\0.jpg)";
	QPixmap img(url);

	int i, j, k;

	ui.setupUi(this);

	// Buttons
	connect(this->ui.openButton, SIGNAL(clicked()), this, SLOT(handleOpenButton()));
	connect(this->ui.saveButton, SIGNAL(released()), this, SLOT(handleSaveButton()));

	// Vectors of labels
	this->proposals.resize(NB_PROPOSALS);
	this->deck.resize(DECKSIZE);
	this->buttons.resize(NB_PROPOSALS);

	// Initiate proposals box, scroll area, widget, labels
	ui.proposalsBox->setFixedHeight(465);
	ui.proposalsBox->setFixedWidth(1920);
	ui.proposalsBox->move(QPoint(0, 0));

	ui.proposalsArea->setFixedHeight(425);
	ui.proposalsArea->setFixedWidth(1920);
	ui.proposalsArea->move(QPoint(0, 40));

	QWidget *proposalsWidget = new QWidget();
	proposalsWidget->setFixedHeight(390);
	proposalsWidget->setFixedWidth(NB_PROPOSALS * (MARGIN + WIDTHLABEL) + MARGIN);
	ui.proposalsArea->setWidget(proposalsWidget);

	for (i = 0; i < NB_PROPOSALS; ++i)
	{
		this->proposals[i] = new QLabel("proposalsLabel" + i, proposalsWidget);
		this->proposals[i]->setFixedWidth(WIDTHLABEL);
		this->proposals[i]->setFixedHeight(HEIGHTLABEL);
		this->proposals[i]->move(QPoint(25 + i * (MARGIN + WIDTHLABEL), MARGIN));

		this->proposals[i]->setPixmap(img.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));

		this->buttons[i] = new AddButton(proposalsWidget);
		this->buttons[i]->move(QPoint(25 + i * (MARGIN + WIDTHLABEL), MARGIN + HEIGHTLABEL + 10));
	}

	// Initiate deck box, scroll area, widget, labels
	ui.deckBox->setFixedHeight(689);
	ui.deckBox->setFixedWidth(1920);
	ui.deckBox->move(QPoint(0, 465));

	ui.deckArea->setFixedHeight(549);
	ui.deckArea->setFixedWidth(1920);
	ui.deckArea->move(QPoint(0, 40));

	QWidget *deckWidget = new QWidget();
	deckWidget->setFixedWidth(1920);
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

			this->deck[i]->setPixmap(img);
		}
	}
}

void Deck_builder::initiate()
{
	QString url;
	QPixmap image;

	int i, multiverseid;

	this->idsPool = readFile();
	this->G = Graph();
	this->G.createCards();
	this->G.createEdges(COEF_COLOR, COEF_TYPE, COEF_SUBTYPE, COEF_CAPACITY, COEF_EDITION);

	for (int i = 0; i < this->idsPool.size(); ++i)
	{
		multiverseid = this->G.Cards[this->G.Ids.right.at(this->idsPool[i])].multivereid;

		url = QString::number(multiverseid);
		url.push_front(R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");

		image.load(url);
		image = image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL));

		this->deck[i]->setPixmap(image);
	}


	//this->proposals[i]->clear();

	//vector<int> finalDeck = this->G.heavyNeighbour(this->idsPool);
	//writeFile(imgs);
	/*
	for (int i = 0; i < DECKSIZE; ++i)
	{
		url = QString::number(imgs[i]);
		url.push_front(R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");

		image.load(url);
		image = image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL));

		this->deck[i]->setPixmap(image);
	}
	*/
	//writeFile(imgs);
}	

void Deck_builder::handleTestButton()
{
	QMessageBox msgBox;
	msgBox.setWindowTitle("Hello");
	msgBox.setText("You Clicked " + ((QPushButton*)sender())->text());
	msgBox.exec();
}