/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "stdafx.h"

AddButton::AddButton(QWidget * parent) : QPushButton(parent)
{
	/*this->btn = new QPushButton(this);
	this->btn->setText("Poids");
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(this->btn);
	setLayout(hlay);

	this->setFixedWidth(WIDTHLABEL);
	this->setFixedHeight(40);
	this->setContentsMargins(0, 0, 0, 0);

	this->btn->setFixedWidth(WIDTHLABEL);
	this->btn->setFixedHeight(40);
	this->btn->setStyleSheet("font: 14pt;");
	this->btn->setText("Poids");
	this->btn->move(QPoint(0, 0));
	this->btn->setContentsMargins(0, 0, 0, 0);*/

	/*this->btn = new QPushButton(this);
	this->setText("Poids");
	QHBoxLayout *hlay = new QHBoxLayout;
	hlay->addWidget(this->btn);
	setLayout(hlay);

	this->setFixedWidth(WIDTHLABEL);
	this->setFixedHeight(40);
	this->setContentsMargins(0, 0, 0, 0);*/

	this->setFixedWidth(WIDTHLABEL);
	this->setFixedHeight(40);
	this->setStyleSheet("font: 14pt;");
	this->setText("Poids");
	this->move(QPoint(0, 0));
	this->setContentsMargins(0, 0, 0, 0);

	this->id = 0;
}

/*void AddButton::handleButton()
{
	this->btn->setText("Done");
}*/

AddButton::~AddButton()
{
}
