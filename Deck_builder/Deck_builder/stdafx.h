#pragma once

#include "targetver.h"

#include <tchar.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include <vector>
#include <map>

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include <boost/bimap.hpp>

#include "Card.h"
#include "Edge.h"
#include "Graph.h"