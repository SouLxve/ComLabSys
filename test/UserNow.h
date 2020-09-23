#pragma once
#include <iostream>
#include "md5.h"
#include "ConnectMysql.h"

class UserNow
{
private:
	bool effectiveness = 0;
	int id;
	string username;
	string password;
	int permission;
	string phone;
	string email;

public:
	UserNow();
	~UserNow();
	int LoginMatch(string, string);
	int HandleRegister(string, string, string, string);
	int ChangePassword(string, string);
	int AdminChangePassword(string, string);
	int setPermission(string, int);
	void Logout();
	bool IsEffective();
	int getID();
	string getUsername();
	int getPermission();
	//string getPassword();
	string getPhone();
	string getEmail();
	int setPhone(string);
	int setEmail(string);
};

