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

/* COLORS */
#define NB_COLORS 5

/* OPTIMISATION PROBLEM */
#define NB_PROPOSALS 50
#define DECKSIZE 40

/* DIMENSIONS */
#define WIDTHLABEL 225
#define HEIGHTLABEL 315
#define MARGIN 10

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
#include <map>
#include <bitset>

#include "Util.h"
#include "AddButton.h"