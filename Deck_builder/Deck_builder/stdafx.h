/***
	Bellamy Lola & Bourgeois-Ducournau Guillaume
	M2 DAR - 2017/2018
	Projet - Magic cards
***/

#pragma once

/* DATABASE */
#define HOST "localhost"
#define USER "root"
#define PASS "root"
#define DB "magic"

#define NB_CARDS "20000"
#define COEF_COLOR 2
#define COEF_TYPE 1
#define COEF_SUBTYPE 2
#define COEF_CAPACITY 1
#define COEF_EDITION 2

/* COLORS */
#define NB_COLORS 5
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2
#define COLOR_U 3
#define COLOR_W 4

/* OPTIMISATION PROBLEM */
#define NB_NEIGHBORS 500
#define NB_PROPOSALS 10
#define DECKSIZE 40

/* DIMENSIONS */
#define WIDTHLABEL 225
#define HEIGHTLABEL 315
#define MARGIN 25

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <windows.h>

#include <boost/bimap.hpp>
#include <boost/bimap/support/lambda.hpp>
#include <boost/lexical_cast.hpp>

#include <QtWidgets/QMainWindow>
#include "ui_Deck_builder.h"
#include <QMessageBox>
#include <QVector>
#include <QGridLayout>
#include <qdebug.h>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QSignalMapper>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <vector>
#include <bitset>
#include <map>

#include "Util.h"
#include "AddButton.h"