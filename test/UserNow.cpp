#include "stdafx.h"

UserNow::UserNow() {
	id=-1;
	username="";
	password="";
	permission=-1;
}

UserNow::~UserNow() {

}

int UserNow::LoginMatch(string name, string pass) {
	char query[255];
	MD5 getMD5(pass);
	string md5 = getMD5.md5();
	sprintf(query, "SELECT * FROM users WHERE user_name='%s'", name.c_str());
	ResultSet* res = connSQL->getMessage(query);
	while (res->next()) {
		this->id = res->getInt(1);
		this->username = res->getString(2).c_str();
		this->password = res->getString(3).c_str();
		this->permission = res->getInt(4);
		this->phone = res->getString(5).c_str();
		this->email = res->getString(6).c_str();
	}
	if (this->password == md5) {
		this->effectiveness = 1;
		return 0;                  //成功登录
	}
	return 1;                      //登陆失败
}

int UserNow::HandleRegister(string name, string pass, string phone0, string email0) {
	if (this->effectiveness == 1) {
		return 1;                 //已登录，无法注册
	}
	char query[255];
	sprintf(query, "SELECT * FROM users WHERE user_name='%s'", name.c_str());
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		return 2;                 //用户名已存在
	}
	MD5 getMD5(pass);
	string md5 = getMD5.md5();
	sprintf(query, "INSERT INTO users (user_name,user_password,user_permission,user_phone,user_email) VALUES ('%s','%s','2','%s','%s')", name.c_str(), md5.c_str(), phone0.c_str(), email0.c_str());
	int re = connSQL->updateMessage(query);
	if (re == 1) {
		return 0;                 //注册成功
	}
	else
		return 3;                 //失败
}

int UserNow::ChangePassword(string oldpass, string newpass) {
	if (this->effectiveness == 0) {
		return 1;                 //未登录
	}
	MD5 getMD5(oldpass);
	string md5 = getMD5.md5();
	if (md5 != password) {
		return 2;                 //密码错误
	}
	MD5 getMD5_2(newpass);
	md5 = getMD5_2.md5();
	char query[255];
	sprintf(query, "UPDATE users SET user_password='%s' WHERE user_name='%s'", md5.c_str(), this->username.c_str());
	int re = connSQL->updateMessage(query);
	if (re == 1) {
		this->password == md5;
		return 0;                 //修改成功
	}
	else
		return 3;                 //失败
}

int UserNow::AdminChangePassword(string name, string newpass) {
	if (this->effectiveness == 0) {
		return 1;                 //未登录
	}
	if (this->permission != 0) {
		return 2;                 //无权限
	}
	MD5 getMD5(newpass);
	string md5 = getMD5.md5();
	char query[255];
	sprintf(query, "UPDATE users SET user_password='%s' WHERE user_name='%s'", md5.c_str(), name.c_str());
	int re = connSQL->updateMessage(query);
	if (re == 1) {
		if (username == name) {
			this->password == md5;
		}
		return 0;                 //修改成功
	}
	else
		return 3;                 //失败
}

//设置权限
//0级权限不可降级
//0级1级可以给低级权限提高等级或降低等级
//等级最高不超过自身且不能为0级
//等级最低不低于3
int UserNow::setPermission(string name, int perm) {
	if (this->effectiveness == 0) {
		return 1;                 //未登录
	}
	char query[255];
	if (username == name) {
		return 5;                 //不能给自身设置
	}
	if (this->permission == 0 || this->permission == 1) {
		if (perm >= 1 && perm <= 3) {
			sprintf(query, "UPDATE users SET user_permission='%d' WHERE user_name='%s'", perm, name.c_str());
			int re = connSQL->updateMessage(query);
			if (re == 1)
				return 0;         //成功
			else
				return 4;         //失败
		}
		else {
			return 3;             //格式不对
		}
	}
	else {
		return 2;                 //无权限
	}
}

bool UserNow::IsEffective() {
	return effectiveness;
}

int UserNow::getID() {
	return id;
}

string UserNow::getUsername() {
	return username;
}

int UserNow::getPermission() {
	return permission;
}

/*string UserNow::getPassword() {
	return password;
}*/

string UserNow::getPhone() {
	return phone;
}

string UserNow::getEmail() {
	return email;
}

int UserNow::setPhone(string phone0) {
	if (effectiveness == 0) {
		return 1;                //未登录
	}
	char query[255];
	sprintf(query, "UPDATE users SET user_phone='%s' WHERE user_name='%s'", phone0.c_str(), username.c_str());
	int re = connSQL->updateMessage(query);
	if (re == 1) {
		this->phone = phone0;
		return 0;                //成功
	}
	else
		return 2;                //错误
}

int UserNow::setEmail(string email0) {
	if (effectiveness == 0) {
		return 1;                //未登录
	}
	char query[255];
	sprintf(query, "UPDATE users SET user_email='%s' WHERE user_name='%s'", email0.c_str(), username.c_str());
	int re = connSQL->updateMessage(query);
	if (re == 1) {
		this->email = email0;
		return 0;                //成功
	}
	else
		return 2;                //错误
}

void UserNow::Logout() {
	this->effectiveness = 0;
	this->username = "";
	this->password = "";
}