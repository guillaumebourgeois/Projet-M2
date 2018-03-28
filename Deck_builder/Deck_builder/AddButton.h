/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#include "stdafx.h"
#pragma once

class AddButton : public QPushButton
{
	Q_OBJECT
public:
	AddButton(QWidget *parent = 0);
	~AddButton();
	
	int id;
};

