#pragma once

#include <QWidget>
#include "ui_Admin0Window.h"

using namespace std;

class Admin0Window : public QWidget
{
	Q_OBJECT

public:
	Admin0Window(QWidget *parent = Q_NULLPTR);
	~Admin0Window();

private slots:
	void on_logout_clicked();
	void on_return_clicked();
	void on_submit_clicked();
	void on_change_clicked();
	void on_modify_clicked();
	void on_modify2_clicked();
	void on_del_clicked();
	void on_tab_changed();
	void on_addlab_clicked();
	void on_reset_clicked();

private:
	Ui::Admin0Window ui;
	void setMainPage();//显示mainPage初始化
	void setUserPage(string, string, string, int);//显示userPage初始化
	void showLabRoom();
	void showLabType();
};
