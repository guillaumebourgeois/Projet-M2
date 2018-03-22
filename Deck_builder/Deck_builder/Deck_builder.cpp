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
	//QString url = R"(C:\Users\guill\Desktop\cards\0.jpg)";
	//QPixmap img(url);

	int i, j, k;

	ui.setupUi(this);

	// Vectors of labels
	this->proposals.resize(NB_PROPOSALS);
	this->deck.resize(DECKSIZE);
	this->buttons.resize(NB_PROPOSALS);

	this->nbCards = 0;

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
		this->proposals[i] = new QLabel("proposalsLabel", proposalsWidget);
		this->proposals[i]->setFixedWidth(WIDTHLABEL);
		this->proposals[i]->setFixedHeight(HEIGHTLABEL);
		this->proposals[i]->move(QPoint(25 + i * (MARGIN + WIDTHLABEL), MARGIN));

		this->proposals[i]->clear();

		this->buttons[i] = new AddButton(proposalsWidget);
		this->buttons[i]->move(QPoint(25 + i * (MARGIN + WIDTHLABEL), MARGIN + HEIGHTLABEL + 10));

		connect(this->buttons[i], SIGNAL(clicked()), &this->mapper, SLOT(map()));
		this->mapper.setMapping(this->buttons[i], i);
	}

	connect(&this->mapper, SIGNAL(mapped(int)), this, SLOT(handleAddButton(int)));

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

			this->deck[i]->clear();
		}
	}
}

void Deck_builder::initiate()
{
	QString url;
	QPixmap image;

	int i, j, multiverseid;

	bimap_type proposals;
	bimap_type::right_iterator itprop;

	this->idsPool = readFile();
	this->nbCards = this->idsPool.size();
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
		this->deck[i]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL)));
	}

	this->setProposals();
}

void Deck_builder::setProposals()
{
	QString url;
	QPixmap image;

	int i, multiverseid;

	bimap_type proposals;
	bimap_type::right_iterator itprop;

	proposals = this->G.heavyNeighbour(this->idsPool);

	for (i = 0, itprop = proposals.right.end(); i < NB_PROPOSALS && itprop != proposals.right.begin(); ++i)
	{
		--itprop;
		multiverseid = this->G.Cards[this->G.Ids.right.at(itprop->second)].multivereid;

		url = QString::number(multiverseid);
		url.push_front(R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");

		image.load(url);
		this->proposals[i]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));

		this->buttons[i]->setText(QString::number(itprop->first));
		this->buttons[i]->id = itprop->second;
	}
}

void Deck_builder::handleAddButton(int j)
{
	QString url;
	QPixmap image;

	int i, multiverseid;

	if (this->nbCards < DECKSIZE)
	{
		this->idsPool.push_back(this->buttons[j]->id);

		multiverseid = this->G.Cards[this->G.Ids.right.at(this->buttons[j]->id)].multivereid;
		
		qDebug() << this->buttons[j]->id << " " << multiverseid;

		url = QString::number(multiverseid);
		url.push_front(R"(C:\Users\guill\Desktop\cards\)");
		url.push_back(".jpg");

		image.load(url);
		this->deck[this->nbCards]->setPixmap(image.scaled(QSize(WIDTHLABEL, HEIGHTLABEL), Qt::IgnoreAspectRatio));

		++this->nbCards;
		
		this->setProposals();
	}
	else
	{
		int k = 0;
		for (i = 0; i < NB_PROPOSALS; ++i)
		{
			this->buttons[i]->setEnabled(false);
			this->buttons[i]->setText("");
			this->proposals[i]->clear();
		}

		for (i = 0; i < this->idsPool.size(); ++i)
		{
			for (j = 0; j < this->idsPool.size(); ++j)
				if (idsPool[i] == idsPool[j])
					++k;
		}
		qDebug() << k;
	}
}