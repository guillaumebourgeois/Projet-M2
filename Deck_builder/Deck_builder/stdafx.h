#pragma once

/* DATABASE */
#define HOST "localhost"
#define USER "root"
#define PASS "root"
#define DB "magic"

#define NB_CARDS "10"

/* COLORS */
#define NB_COLORS 5
#define COLOR_B 0
#define COLOR_G 1
#define COLOR_R 2
#define COLOR_U 3
#define COLOR_W 4

#include "targetver.h"

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <windows.h>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <vector>
#include <boost/bimap.hpp>
#include <bitset>

#include "Card.h"
#include "Edge.h"
#include "Graph.h"
#include "Util.h"