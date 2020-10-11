#include "Register.h"
#include "stdafx.h"
#include "login.h"

using namespace std;

Register::Register(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(500, 400);
	connect(ui.submitButton, &QPushButton::clicked, this, &Register::on_submit_clicked);
	connect(ui.returnButton, &QPushButton::clicked, this, &Register::on_return_clicked);
}

Register::~Register()
{
}

void Register::on_submit_clicked() {
	string username = ui.nameLine->text().toStdString();
	string password = ui.passwordLine->text().toStdString();
	string password2 = ui.password2Line->text().toStdString();
	string phone = ui.phoneLine->text().toStdString();
	string email = ui.emailLine->text().toStdString();
	if (username == "" || password == "" || password2=="") {
		QMessageBox::information(this, QString::fromLocal8Bit("警告"), QStringLiteral("输入不能为空"), QMessageBox::Ok);
	}
	else if (password != password2) {
		QMessageBox::information(this, QString::fromLocal8Bit("警告"), QStringLiteral("两次输入密码不一致"), QMessageBox::Ok);
	}
	else {
		int flag = userToken->HandleRegister(username, password, phone, email);
		if (flag == 2) {
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QStringLiteral("用户名已存在"), QMessageBox::Ok);
		}
		else if (flag == 0) {
			login* l = new login;
			l->show();
			this->close();
		}
		else {
			QMessageBox::information(this, QString::fromLocal8Bit("提示"), QStringLiteral("注册失败"), QMessageBox::Ok);
		}
	}
}

void Register::on_return_clicked() {
	login* l = new login;
	l->show();
	this->close();
}