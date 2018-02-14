#include "stdafx.h"

#include "mysql_connection.h"
#include "mysql_driver.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#define HOST "localhost"
#define USER "root"
#define PASS "root"
#define DB "magic_card"

using namespace std;

int main()
{
	cout << "Connector/C++ tutorial framework..." << endl;
	cout << endl;

	try {
		sql::Driver *driver;
		sql::Connection *con;
		//sql::Statement *stmt;
		//sql::ResultSet *res;

		/* Create a connection */
		driver = get_driver_instance();
		//con = driver->connect(HOST, USER, PASS);
		/* Connect to the MySQL database */
		//con->setSchema(DB);
		

		//delete con;
	}
	catch (sql::SQLException &e) {
		/*
		MySQL Connector/C++ throws three different exceptions:

		- sql::MethodNotImplementedException (derived from sql::SQLException)
		- sql::InvalidArgumentException (derived from sql::SQLException)
		- sql::SQLException (derived from std::runtime_error)
		*/
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		/* what() (derived from std::runtime_error) fetches error message */
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;

		return EXIT_FAILURE;
	}

	cout << "Done." << endl;

	int tmp;
	cout << "Press enter to return" << endl;
	cin >> tmp;

	return EXIT_SUCCESS;
}

