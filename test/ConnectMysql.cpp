#include "stdafx.h"

ConnectMysql::ConnectMysql() {
	addr = "tcp://127.0.0.1:3306";
	name = "sms";
	pass = "1234";
	sche = "test";
	try {
		driver = get_driver_instance();
		con = driver->connect(addr.c_str(), name.c_str(), pass.c_str());
		con->setSchema(sche.c_str());
		stmt = con->createStatement();
	}
	catch (SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}

ConnectMysql::ConnectMysql(string a, string b, string c, string d) {
	addr = a;
	name = b;
	pass = c;
	sche = d;
	try {
		driver = get_driver_instance();
		con = driver->connect(addr, name, pass);
		con->setSchema(sche);
		stmt = con->createStatement();
	}
	catch (SQLException& e) {
		cout << "# ERR: SQLException in " << __FILE__;
		cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
		cout << "# ERR: " << e.what();
		cout << " (MySQL error code: " << e.getErrorCode();
		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
	}
}

ConnectMysql::~ConnectMysql() {
	if (res != 0) {
		delete res;
	}
	if (stmt != 0) {
		delete stmt;
	}
	if (con != 0) {
		delete con;
	}
}

ResultSet* ConnectMysql::getMessage(string query) {
	res = stmt->executeQuery(query.c_str());
	return res;
}

int ConnectMysql::updateMessage(string query) {
	int updateCount = stmt->executeUpdate(query.c_str());
	return updateCount;
}