#include "Register.h"
#include "stdafx.h"
#include "login.h"

using namespace std;

Register::Register(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
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
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QStringLiteral("���벻��Ϊ��"), QMessageBox::Ok);
	}
	else if (password != password2) {
		QMessageBox::information(this, QString::fromLocal8Bit("����"), QStringLiteral("�����������벻һ��"), QMessageBox::Ok);
	}
	else {
		int flag = userToken->HandleRegister(username, password, phone, email);
		if (flag == 2) {
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QStringLiteral("�û����Ѵ���"), QMessageBox::Ok);
		}
		else if (flag == 0) {
			login* l = new login;
			l->show();
			this->close();
		}
		else {
			QMessageBox::information(this, QString::fromLocal8Bit("��ʾ"), QStringLiteral("ע��ʧ��"), QMessageBox::Ok);
		}
	}
}

void Register::on_return_clicked() {
	login* l = new login;
	l->show();
	this->close();
}