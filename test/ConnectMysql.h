#pragma once
#include <iostream>
#include "jdbc/mysql_connection.h"
#include "jdbc/mysql_driver.h"
#include "jdbc/cppconn/statement.h"

using namespace std;
using namespace sql;

class ConnectMysql
{
private:  
	string addr;
	string name;
	string pass;
	string sche;
	Driver* driver;
	Connection* con;
	Statement* stmt;
	ResultSet* res;
public:
	ConnectMysql();
	ConnectMysql(string, string, string, string);
	~ConnectMysql();
	ResultSet* getMessage(string);
	int updateMessage(string);
};

