#include "login.h"
#include "MainWindow.h"
#include "AdminWindow.h"
#include "Admin0Window.h"
#include "Register.h"
#include "stdafx.h"

using namespace std;

login::login(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);
    ui.passwordLine->setEchoMode(QLineEdit::Password);
    connect(ui.loginButton, &QPushButton::clicked, this, &login::on_login_clicked);
    connect(ui.registerButton, &QPushButton::clicked, this, &login::on_register_clicked);
    connect(ui.editButton, &QPushButton::clicked, this, &login::on_edit_clicked);
}


login::~login()
{

}

void login::on_login_clicked()
{
    string username = ui.nameLine->text().toStdString();
    string password = ui.passwordLine->text().toStdString();
    if (username == "" || password == "")
    {
        QMessageBox::information(this, QString::fromLocal8Bit("警告"), QStringLiteral("输入不能为空"), QMessageBox::Ok);
    }
    else
    {
        int flag = userToken->LoginMatch(username, password);
        if (flag == 0) {
            if (userToken->getPermission() == 2) {
                MainWindow* w = new MainWindow;
                w->show();
                this->close();
            }
            else if (userToken->getPermission() == 1) {
                AdminWindow* w = new AdminWindow;
                w->show();
                this->close();
            }
            else if (userToken->getPermission() == 0) {
                Admin0Window* w = new Admin0Window;
                w->show();
                this->close();
            }
        }
        else {
            QMessageBox::information(this, QString::fromLocal8Bit("警告"), QStringLiteral("用户名或密码错误"), QMessageBox::Ok);
        }
    }
}

void login::on_register_clicked()
{
    Register* r = new Register;
    r->show();
    this->close();
}

void login::on_edit_clicked() {
    ui.nameLine->clear();
    ui.passwordLine->clear();
}