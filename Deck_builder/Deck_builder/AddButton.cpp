/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "stdafx.h"

AddButton::AddButton(QWidget * parent) : QPushButton(parent)
{
	this->setFixedWidth(WIDTHLABEL);
	this->setFixedHeight(40);
	this->setStyleSheet("font: 14pt;");
	this->setText("Poids");
	this->move(QPoint(0, 0));
	this->setContentsMargins(0, 0, 0, 0);

	this->id = 0;
}

AddButton::~AddButton()
{
}
