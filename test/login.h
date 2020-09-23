#pragma once

#include <QtWidgets/QDialog>
#include "ui_login.h"

class login : public QDialog
{
    Q_OBJECT

public:
    login(QWidget *parent = Q_NULLPTR);
    ~login();

private slots:
    void on_login_clicked();
    void on_edit_clicked();
    void on_register_clicked();

private:
    Ui::loginClass ui;
};
