#pragma once

#include <QWidget>
#include "ui_MainWindow.h"

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private slots:
	void on_logout_clicked();
	void on_modify_clicked();
	void on_messsubmit_clicked();
	void on_passsubmit_clicked();
	void on_userreturn_clicked();
	void on_substart_changed();
	void on_table_changed();
	void on_lesson_changed();
	void on_appoint_modify();
	void on_appoint_delete();
	void on_appoint_submit();
	void on_clear_clicked();
	void timer_handle();
	/*
	void on_loginButton_clicked();
	void on_pushButton_checkSelfOrder_clicked();
	void on_weeknumberBox_currentIndexChanged(int index);
	void getRoomInfo();
	int getID(QString str);
	void getRoomMargin(int& roomMargin1, int& roomMargin2, int& roomMargin3, int& roomMargin4, int& roomMargin5, int row);
	void updateRoomInfo();
	void updateRoomInfoTable();
	void updateRoomInfoTable1();
	void showOrderInfo(int lookFlag);
	int chooseroom();*/

private:
	Ui::MainWindow ui;
	int order_id = 0;
	int appoint_list[300];
	/*int orderDateIndex = 0;
	QString orderDate = "周一";
	int orderTimeIndex = 0;
	QString orderTime = "第一大节";
	int orderRoomIndex = 0;
	QString orderRoom = "1号机房";
	int roomID;
	QString roomStr;
	int roomMargin1;
	int roomMargin2;
	int roomMargin3;
	int roomMargin4;
	int roomMargin5;
	int roomMaxNum;
	int margin[7][5][5];
	int appointDay;
	int appointTime;
	QString tableName;*/
	void setMainPage();//显示mainPage初始化
	void setUserPage();//显示userPage初始化
	void initBoxs();//初始化下拉框
	void appointView();//初始化预约信息
};
