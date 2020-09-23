#pragma once

#include <QWidget>
#include "ui_AdminWindow.h"

class AdminWindow : public QWidget
{
	Q_OBJECT

public:
	AdminWindow(QWidget *parent = Q_NULLPTR);
	~AdminWindow();

	//void ADD();

private slots:
	void on_logout_clicked();
	void on_modify_clicked();
	void on_messsubmit_clicked();
	void on_passsubmit_clicked();
	void on_userreturn_clicked();
	void on_inquiry_clicked();
	void on_permchange_clicked();
	void on_agree_clicked();
	void on_disagree_clicked();
	void timer_handle();
	void on_table_changed();
	void on_change_clicked();
	void on_submit_clicked();
	void on_clear_clicked();
	void on_startweek_changed();

	/*void on_weeknumberBox_currentIndexChanged(int index);
	void on_labnumberBox_currentIndexChanged(int index);
	void getRoomInfo();
	int getID(QString str);
	void getRoomMargin(int& roomMargin1, int& roomMargin2, int& roomMargin3, int& roomMargin4, int& roomMargin5, int row);
	void updateRoomInfo();
	void updateRoomInfoTable();
	void showorder();*/
private:
	Ui::AdminWindow ui;
	int my_type[10];
	int room_ids[20];
	int appoint_list[1000];
	int state_list[1000];
	void getType();
	/*int orderDateIndex = 0;
	QString orderDate = "��һ";
	int orderTimeIndex = 0;
	QString orderTime = "��һ���";
	int orderRoomIndex = 1;
	QString orderRoom = "1�Ż���";
	int roomID;
	QString roomStr;
	int roomMargin1;
	int roomMargin2;
	int roomMargin3;
	int roomMargin4;
	int roomMargin5;
	int roomMaxNum;
	int margin[7][5][5];
	QString tableName;*/
	void setMainPage();//��ʾmainPage��ʼ��
	void setUserPage();//��ʾuserPage��ʼ��
	void initBoxs();//��ʼ��������
	void appointView();//��ʼ��ԤԼ��Ϣ
	void labView();//��ʼ��������Ϣ
};
