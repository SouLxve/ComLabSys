#pragma execution_character_set("utf-8")

#include "AdminWindow.h"
#include "stdafx.h"
#include "login.h"

AdminWindow::AdminWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1500, 900);
	this->setWindowTitle("机房预约管理系统（管理员）");
	getType();
	setMainPage();
	ui.ordernumBox->setValidator(new QIntValidator(0, 100, this));
	ui.timetableFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.userFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.frame_2->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.myappointFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.doappointFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	timer->setInterval(5000);
	//ADD();
	connect(ui.logoutButton, &QPushButton::clicked, this, &AdminWindow::on_logout_clicked);
	connect(ui.modifyButton, &QPushButton::clicked, this, &AdminWindow::on_modify_clicked);
	connect(ui.messsubmitButton_2, &QPushButton::clicked, this, &AdminWindow::on_messsubmit_clicked);
	connect(ui.passsubmitButton_2, &QPushButton::clicked, this, &AdminWindow::on_passsubmit_clicked);
	connect(ui.userreturnButton_2, &QPushButton::clicked, this, &AdminWindow::on_userreturn_clicked);
	connect(ui.inquiryButton, &QPushButton::clicked, this, &AdminWindow::on_inquiry_clicked);
	connect(ui.permchangeButton, &QPushButton::clicked, this, &AdminWindow::on_permchange_clicked);
	connect(ui.labnumberBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &AdminWindow::on_table_changed);
	connect(ui.weeknumberBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &AdminWindow::on_table_changed);
	connect(ui.startweekBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &AdminWindow::on_startweek_changed);
	connect(ui.yesButton, &QPushButton::clicked, this, &AdminWindow::on_submit_clicked);
	connect(ui.noButton, &QPushButton::clicked, this, &AdminWindow::on_clear_clicked);
	connect(timer, &QTimer::timeout, this, &AdminWindow::timer_handle);
	timer->start();
}

AdminWindow::~AdminWindow()
{
	timer->stop();
}

void AdminWindow::setMainPage() {
	ui.stackedWidget->setCurrentWidget(ui.mainPage);
	ui.usernameLine->setText(QString::fromStdString(userToken->getUsername()));
	ui.phoneLine->setText(QString::fromStdString(userToken->getPhone()));
	ui.emailLine->setText(QString::fromStdString(userToken->getEmail()));
	ui.premissionLine->setText(QString::number(userToken->getPermission()));
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.tableWidget->setShowGrid(false);
	ui.tableWidget->setFocusPolicy(Qt::NoFocus);
	ui.tableWidget->verticalHeader()->setMinimumSectionSize(60);
	ui.appointTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	//ui.appointTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.appointTable->verticalHeader()->setDefaultSectionSize(60);
	ui.appointTable->setShowGrid(false);
	ui.appointTable->setFocusPolicy(Qt::NoFocus);
	ui.labTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	ui.labTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.labTable->verticalHeader()->setMinimumSectionSize(60);
	ui.labTable->setShowGrid(false);
	ui.labTable->setFocusPolicy(Qt::NoFocus);
	appointView();
	labView();
	initBoxs();
	timer->start();
	//showorder();
}

void AdminWindow::setUserPage() {
	ui.stackedWidget->setCurrentWidget(ui.userPage);
	ui.unusernameLine_2->setText(QString::fromStdString(userToken->getUsername()));
	ui.newemailLine_2->setText(QString::fromStdString(userToken->getEmail()));
	ui.newphoneLine_2->setText(QString::fromStdString(userToken->getPhone()));
	ui.unpremisionLine_2->setText(QString::number(userToken->getPermission()));
	timer->stop();
}

void AdminWindow::getType() {
	char query[100];
	sprintf(query, "select type_id from type_info where user_id=%d", userToken->getID());
	ResultSet* res = connSQL->getMessage(query);
	int count = 1;
	for (; res->next(); count++) {
		this->my_type[count] = res->getInt(1);
	}
	this->my_type[0] = count - 1;
}

void AdminWindow::appointView() {
	char query[550];
	ResultSet* res;
	QPushButton* agree, * disagree;
	QWidget* tmp_widget;
	QHBoxLayout* tmp_layout;
	ui.appointTable->clearContents();
	ui.appointTable->setRowCount(0);
	int row = 0;
	int sta[3] = { 1,3,2 };
	for (int i = 0; i < 3; i++) {
		for (int count = 1; count <= this->my_type[0]; count++) {
			sprintf(query, "select users.user_name,order_info.startweek,order_info.endweek,date_info.date_str,time_info.time_str,room_info.room_name,state_info.state_str,order_info.order_id,order_amount from order_info,date_info,room_info,state_info,time_info,users where order_info.order_room=room_info.room_id and order_info.state_id=state_info.state_id and order_info.order_date=date_info.date_id and order_info.order_time=time_info.time_id and order_info.user_id=users.user_id and room_info.room_type=%d and order_info.state_id=%d",this->my_type[count],sta[i]);
			res = connSQL->getMessage(query);
			for (; res->next(); row++) {
				this->appoint_list[row] = res->getInt(8);
				this->state_list[row] = sta[i];
				ui.appointTable->insertRow(row);
				ui.appointTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(res->getString(1).c_str())));
				ui.appointTable->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
				ui.appointTable->setItem(row, 1, new QTableWidgetItem(QString::number(res->getInt(2))));
				ui.appointTable->item(row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
				ui.appointTable->setItem(row, 2, new QTableWidgetItem(QString::number(res->getInt(3))));
				ui.appointTable->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.appointTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(res->getString(4).c_str())));
				ui.appointTable->item(row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.appointTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(res->getString(5).c_str())));
				ui.appointTable->item(row, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.appointTable->setItem(row, 5, new QTableWidgetItem(QString::number(res->getInt(9))));
				ui.appointTable->item(row, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.appointTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(res->getString(6).c_str())));
				ui.appointTable->item(row, 6)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				ui.appointTable->setItem(row, 7, new QTableWidgetItem(QString::fromStdString(res->getString(7).c_str())));
				ui.appointTable->item(row, 7)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
				agree = new QPushButton();
				//agree->setText("同意");
				agree->setIcon(QIcon::fromTheme("folder", QIcon(":/login/select-bold.png")));
				agree->setIconSize(QSize(24, 24));
				agree->setStyleSheet("QPushButton{min-width:32px;max-width:32px;min-height:32px;max-height:32px;border: none; background-color:transparent;}QPushButton:hover{background-color:#dcdcdc;}QPushButton:pressed{background-color:#c5c5c5;}");
				agree->setFixedSize(48, 48);
				if (sta[i] == 3) {
					agree->setEnabled(false);
				}
				disagree = new QPushButton();
				//disagree->setText("拒绝");
				disagree->setIcon(QIcon::fromTheme("folder", QIcon(":/login/close-bold.png")));
				disagree->setIconSize(QSize(24, 24));
				disagree->setStyleSheet("QPushButton{min-width:32px;max-width:32px;min-height:32px;max-height:32px;border: none; background-color:transparent;}QPushButton:hover{background-color:#dcdcdc;}QPushButton:pressed{background-color:#c5c5c5;}");
				disagree->setFixedSize(48, 48);
				if (sta[i] == 2) {
					disagree->setEnabled(false);
				}
				tmp_widget = new QWidget();
				tmp_layout = new QHBoxLayout(tmp_widget);
				tmp_layout->addWidget(agree);
				tmp_layout->addWidget(disagree);
				tmp_layout->setMargin(0);
				ui.appointTable->setCellWidget(row, 8, tmp_widget);
				connect(agree, &QPushButton::clicked, this, &AdminWindow::on_agree_clicked);
				connect(disagree, &QPushButton::clicked, this, &AdminWindow::on_disagree_clicked);
			}
		}
	}
}

void AdminWindow::labView() {
	ui.labTable->clearContents();
	ui.labTable->setRowCount(0);
	char query[255];
	QPushButton* change;
	sprintf(query, "select room_name,room_max_num,type_str,room_id from room_info,type_info where room_info.room_type=type_info.type_id and type_info.user_id=%d", userToken->getID());
	ResultSet* res = connSQL->getMessage(query);
	for (int row = 0; res->next(); row++) {
		ui.labTable->insertRow(row);
		ui.labTable->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(res->getString(1).c_str())));
		ui.labTable->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
		ui.labTable->setItem(row, 1, new QTableWidgetItem(QString::number(res->getInt(2))));
		ui.labTable->item(row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
		ui.labTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(res->getString(3).c_str())));
		ui.labTable->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
		ui.labTable->item(row, 2)->setFlags(ui.labTable->item(row, 2)->flags() & (~Qt::ItemIsEditable));
		this->room_ids[row] = res->getInt(4);
		QWidget* widget = new QWidget;
		QHBoxLayout* layout = new QHBoxLayout;
		change = new QPushButton();
		//change->setText("修改");
		change->setIcon(QIcon::fromTheme("folder", QIcon(":/login/edit.png")));
		change->setIconSize(QSize(24, 24));
		change->setStyleSheet("QPushButton{min-width:32px;max-width:32px;min-height:32px;max-height:32px;border: none; background-color:transparent;}QPushButton:hover{background-color:#dcdcdc;}QPushButton:pressed{background-color:#c5c5c5;}");
		change->setFixedSize(48, 48);
		layout->addWidget(change);
		layout->setMargin(0);
		layout->setAlignment(change, Qt::AlignCenter);
		widget->setLayout(layout);
		ui.labTable->setCellWidget(row, 3, widget);
		connect(change, &QPushButton::clicked, this, &AdminWindow::on_change_clicked);
	}
}

void AdminWindow::initBoxs() {
	ui.weeknumberBox->clear();
	ui.labnumberBox->clear();
	ui.labtypeBox->clear();
	ui.startweekBox->clear();
	ui.endweekBox->clear();
	ui.weekdayBox->clear();
	ui.whichlessonBox->clear();
	char query[255];
	//week
	sprintf(query, "select distinct week from monday_room_margin");
	ResultSet* res = connSQL->getMessage(query);
	while (res->next()) {
		sprintf(query, "第%s周", res->getString(1).c_str());
		ui.weeknumberBox->addItem(query, res->getInt(1));
		ui.startweekBox->addItem(query, res->getInt(1));
	}
	//room
	sprintf(query, "select room_id,room_name from room_info,type_info where type_info.user_id=%d and type_info.type_id=room_info.room_type", userToken->getID());
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.labnumberBox->addItem(res->getString(2).c_str(), res->getInt(1));
	}
	//data_info
	sprintf(query, "select * from date_info");
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.weekdayBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	//time_info
	sprintf(query, "select * from time_info");
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.whichlessonBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	//type_info
	sprintf(query, "select * from type_info where user_id=%d", userToken->getID());
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.labtypeBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	ui.labtypeBox->setCurrentIndex(-1);
	ui.startweekBox->setCurrentIndex(-1);
	ui.weekdayBox->setCurrentIndex(-1);
	ui.whichlessonBox->setCurrentIndex(-1);
	ui.weeknumberBox->setCurrentIndex(0);
	ui.labnumberBox->setCurrentIndex(0);
	on_table_changed();
}

//槽函数
//
void AdminWindow::on_change_clicked() {
	QPushButton* senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == 0)
	{
		return;
	}
	QModelIndex index = ui.labTable->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	int row = index.row();
	string name = ui.labTable->item(row, 0)->text().toStdString();
	int max = ui.labTable->item(row, 1)->text().toInt();
	int room_max;
	string room_name;
	char query[255];
	sprintf(query, "select * from room_info where room_id=%d", this->room_ids[row]);
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		room_name = res->getString(2).c_str();
		room_max = res->getInt(3);
		if (room_name != name || room_max == max) {
			sprintf(query, "update room_info set room_name='%s' where room_id=%d", name.c_str(), this->room_ids[row]);
			int updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				QMessageBox::information(this, "提示", "修改成功", QMessageBox::Ok);
			}
			else {
				QMessageBox::information(this, "提示", "未进行任何修改", QMessageBox::Ok);
			}
		}
		else if (room_max != max) {
			if (room_max > max) {
				int updateCount;
				for (int i = 0; i < 7; i++) {
					sprintf(query, "select * from %s where (room_margin_1<%d or room_margin_2<%d or room_margin_3<%d or room_margin_4<%d or room_margin_5<%d) and room_id=%d", weekdays[i].c_str(), room_max - max, room_max - max, room_max - max, room_max - max, room_max - max, this->room_ids[row]);
					res= connSQL->getMessage(query);
					if (res->next()) {
						QMessageBox::information(this, "提示", "修改失败", QMessageBox::Ok);
						labView();
						return;
					}
				}
				for (int i = 0; i < 7; i++) {
					sprintf(query, "update %s set room_margin_1=room_margin_1-%d,room_margin_2=room_margin_2-%d,room_margin_3=room_margin_3-%d,room_margin_4=room_margin_4-%d,room_margin_5=room_margin_5-%d where room_id=%d", weekdays[i].c_str(), room_max - max, room_max - max, room_max - max, room_max - max, room_max - max, this->room_ids[row]);
					updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						continue;
					}
					else {
						QMessageBox::information(this, "提示", "出现了致命错误，需要超级管理员重置系统", QMessageBox::Ok);
					}
				}
				sprintf(query, "update room_info set room_name='%s',room_max_num=%d where room_id=%d", name.c_str(), max, this->room_ids[row]);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "提示", "修改成功", QMessageBox::Ok);
				}
			}
			else
			{
				int updateCount;
				for (int i = 0; i < 7; i++) {
					sprintf(query, "update %s set room_margin_1=room_margin_1+%d,room_margin_2=room_margin_2+%d,room_margin_3=room_margin_3+%d,room_margin_4=room_margin_4+%d,room_margin_5=room_margin_5+%d where room_id=%d", weekdays[i].c_str(), max - room_max, max - room_max, max - room_max, max - room_max, max - room_max, this->room_ids[row]);
					updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						continue;
					}
					else {
						QMessageBox::information(this, "提示", "出现了致命错误，需要超级管理员重置系统", QMessageBox::Ok);
					}
				}
				sprintf(query, "update room_info set room_name='%s',room_max_num=%d where room_id=%d", name.c_str(), max, this->room_ids[row]);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "提示", "修改成功", QMessageBox::Ok);
				}
			}
		}
	}
	labView();
}

void AdminWindow::on_submit_clicked() {
	char query[255];
	int room_type, order_amount, startweek, endweek, order_date, order_time, room_id, user_id;
	room_type = ui.labtypeBox->currentData().toInt();
	order_amount = ui.ordernumBox->text().toInt();
	startweek = ui.startweekBox->currentData().toInt();
	endweek = ui.endweekBox->currentData().toInt();
	order_date = ui.weekdayBox->currentData().toInt();
	order_time = ui.whichlessonBox->currentData().toInt();
	if (order_amount <= 0 || room_type == 0 || startweek == 0 || endweek == 0 || order_date == 0 || order_time == 0) {
		QMessageBox::information(this, "提示", "申请信息有误", QMessageBox::Ok);
		return;
	}
	sprintf(query, "select user_id from users where user_name='%s'", ui.usernameEdit->text().toStdString().c_str());
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		user_id = res->getInt(1);
	}
	else {
		QMessageBox::information(this, "提示", "不存在该用户", QMessageBox::Ok);
		return;
	}
	int updateCount;
	sprintf(query, "select room_id from room_info where room_type=%d", room_type);
	res = connSQL->getMessage(query);
	while (res->next()) {
		room_id = res->getInt(1);
		sprintf(query, "select * from %s where room_id=%d and week between %d and %d and room_margin_%d < %d", weekdays[order_date - 1].c_str(), room_id, startweek, endweek, order_time, order_amount);
		ResultSet* tmp = connSQL->getMessage(query);
		if (tmp->next()) {
			continue;
		}
		else {
			//成功
			sprintf(query, "update %s set room_margin_%d=room_margin_%d-%d where week between %d and %d and room_id=%d", weekdays[order_date - 1].c_str(), order_time, order_time, order_amount, startweek, endweek, room_id);
			updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				QMessageBox::information(this, "提示", "分配成功", QMessageBox::Ok);
				sprintf(query, "insert into order_info(user_id,order_date,order_time,order_room,state_id,startweek,endweek,order_amount) values (%d,%d,%d,%d,3,%d,%d,%d)", user_id, order_date, order_time, room_id, startweek, endweek, order_amount);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					appointView();
					on_clear_clicked();
					return;
				}
			}
			QMessageBox::information(this, "提示", "未知错误", QMessageBox::Ok);
		}
	}
	QMessageBox::information(this, "提示", "申请失败，该时间段机房剩余空间不足", QMessageBox::Ok);
}

void AdminWindow::on_clear_clicked() {
	ui.labtypeBox->setCurrentIndex(-1);
	ui.startweekBox->setCurrentIndex(-1);
	ui.endweekBox->setCurrentIndex(-1);
	ui.weekdayBox->setCurrentIndex(-1);
	ui.whichlessonBox->setCurrentIndex(-1);
	ui.usernameEdit->setText("");
	ui.ordernumBox->setText("");
}

void AdminWindow::on_startweek_changed() {
	char query[255];
	sprintf(query, "select distinct week from monday_room_margin");
	ResultSet* res = connSQL->getMessage(query);
	ui.endweekBox->clear();
	int tmp = ui.startweekBox->currentData().toInt();
	while (res->next()) {
		if (res->getInt(1) < tmp) {
			continue;
		}
		sprintf(query, "第%s周", res->getString(1).c_str());
		ui.weeknumberBox->addItem(query, res->getInt(1));
		ui.endweekBox->addItem(query, res->getInt(1));
		ui.endweekBox->setCurrentIndex(-1);
	}
}

void AdminWindow::on_table_changed() {
	int room_id = ui.labnumberBox->currentData().toInt();
	int week_id = ui.weeknumberBox->currentData().toInt();
	char query[255];
	ResultSet* res;
	for (int col = 0; col < 7; col++) {
		sprintf(query, "select * from %s where room_id=%d and week=%d", weekdays[col].c_str(), room_id, week_id);
		res = connSQL->getMessage(query);
		while (res->next()) {
			ui.tableWidget->setItem(0, col, new QTableWidgetItem(QString::number(res->getInt(2))));
			ui.tableWidget->item(0, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget->setItem(1, col, new QTableWidgetItem(QString::number(res->getInt(3))));
			ui.tableWidget->item(1, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget->setItem(2, col, new QTableWidgetItem(QString::number(res->getInt(4))));
			ui.tableWidget->item(2, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget->setItem(3, col, new QTableWidgetItem(QString::number(res->getInt(5))));
			ui.tableWidget->item(3, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.tableWidget->setItem(4, col, new QTableWidgetItem(QString::number(res->getInt(6))));
			ui.tableWidget->item(4, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
}

void AdminWindow::on_logout_clicked() {
	userToken->Logout();
	login* l = new login;
	l->show();
	this->close();
}

void AdminWindow::on_modify_clicked() {
	setUserPage();
}

void AdminWindow::on_messsubmit_clicked() {
	string newphone = ui.newphoneLine_2->text().toStdString();
	string newemail = ui.newemailLine_2->text().toStdString();
	int flag = 0, flag1 = 0;
	if (newphone != userToken->getPhone()) {
		flag = userToken->setPhone(newphone);
	}
	if (newemail != userToken->getEmail()) {
		flag1 = userToken->setEmail(newemail);
	}
	if (flag != 0 && flag1 != 0) {
		QMessageBox::information(this, "提示", "联系方式与电子邮件更改失败", QMessageBox::Ok);
	}
	else if (flag != 0) {
		QMessageBox::information(this, "提示", "联系方式更改失败", QMessageBox::Ok);
	}
	else if (flag1 != 0) {
		QMessageBox::information(this, "提示", "电子邮件更改失败", QMessageBox::Ok);
	}
	else {
		QMessageBox::information(this, "提示", "更改成功", QMessageBox::Ok);
	}
	setUserPage();
}

void AdminWindow::on_passsubmit_clicked() {
	string oldpass = ui.oldpassLine_2->text().toStdString();
	string newpass = ui.newpassLine_2->text().toStdString();
	string newpass2 = ui.newpass2Line_2->text().toStdString();
	if (newpass != newpass2) {
		QMessageBox::information(this, "提示", "两次输入的新密码不一致", QMessageBox::Ok);
	}
	else {
		int flag = userToken->ChangePassword(oldpass, newpass);
		if (flag == 2) {
			QMessageBox::information(this, "提示", "原密码错误", QMessageBox::Ok);
		}
		else if (flag == 0) {
			QMessageBox::information(this, "提示", "密码更改成功", QMessageBox::Ok);
		}
		else {
			QMessageBox::information(this, "提示", "密码更改失败", QMessageBox::Ok);
		}
	}
	setUserPage();
}

void AdminWindow::on_userreturn_clicked() {
	setMainPage();
}

void AdminWindow::on_inquiry_clicked() {
	string name=ui.pusernameLine->text().toStdString();
	if (name != "") {
		char query[100];
		sprintf(query, "SELECT user_permission FROM users WHERE user_name='%s'", name.c_str());
		ResultSet* res = connSQL->getMessage(query);
		int perm;
		if (res->next()) {
			perm = res->getInt(1);
			ui.permnowLine->setText(QString::number(perm));
		}
		else {
			QMessageBox::information(this, "提示", "无此用户", QMessageBox::Ok);
		}
	}
	ui.setpermLine->setText("");
}

void AdminWindow::on_permchange_clicked() {
	string name = ui.pusernameLine->text().toStdString();
	if (name != "") {
		if (ui.setpermLine->text().toInt() >= 0 && ui.setpermLine->text().toInt() <= 3) {
			int flag = userToken->setPermission(name, ui.setpermLine->text().toInt());
			if (flag == 0) {
				QMessageBox::information(this, "提示", "更改成功", QMessageBox::Ok);
				ui.permnowLine->setText(ui.setpermLine->text());
				ui.setpermLine->setText("");
			}
			else {
				QMessageBox::information(this, "提示", "权限更改失败", QMessageBox::Ok);
			}
		}
		else {
			QMessageBox::information(this, "提示", "权限格式错误", QMessageBox::Ok);
		}
	}
	ui.setpermLine->setText("");
}

void AdminWindow::on_agree_clicked() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.appointTable->indexAt(QPoint(x, y));
	int row = index.row();
	char query[255];
	int updateCount;
	sprintf(query, "select startweek,endweek,order_date,order_time,order_room,order_amount,state_id from order_info where order_id='%d'", this->appoint_list[row]);
	ResultSet* res = connSQL->getMessage(query);
	int room_id, order_amount, startweek, endweek, order_date, order_time;
	if (res->next()) {
		room_id = res->getInt(5);
		order_amount = res->getInt(6);
		startweek = res->getInt(1);
		endweek = res->getInt(2);
		order_date = res->getInt(3);
		order_time = res->getInt(4);
	}
	if (order_amount <= 0) {
		QMessageBox::information(this, "提示", "申请数量格式错误", QMessageBox::Ok);
		return;
	}
	sprintf(query, "select * from %s where room_id=%d and week between %d and %d and room_margin_%d < %d", weekdays[order_date - 1].c_str(), room_id, startweek, endweek, order_time, order_amount);
	res = connSQL->getMessage(query);
	if (res->next()) {
		QMessageBox::information(this, "提示", "该申请时间段机房余量不足", QMessageBox::Ok);
	}
	else {
		sprintf(query, "update %s set room_margin_%d=room_margin_%d-%d where week between %d and %d and room_id=%d", weekdays[order_date - 1].c_str(), order_time, order_time, order_amount, startweek, endweek, room_id);
		updateCount = connSQL->updateMessage(query);
		if (updateCount > 0) {
			QMessageBox::information(this, "提示", "分配成功", QMessageBox::Ok);
			sprintf(query, "update order_info set state_id=3 where order_id=%d", this->appoint_list[row]);
			updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				appointView();
			}
		}
	}
}

void AdminWindow::on_disagree_clicked() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.appointTable->indexAt(QPoint(x, y));
	int row = index.row();
	char query[255];
	int updateCount;
	ResultSet* res;
	if (this->state_list[row] == 1) {
		sprintf(query, "update order_info set state_id=2 where order_id=%d", this->appoint_list[row]);
		updateCount = connSQL->updateMessage(query);
		if (updateCount > 0) {
			QMessageBox::information(this, "提示", "拒绝成功", QMessageBox::Ok);
			appointView();
		}
	}
	else if (this->state_list[row] == 3) {
		sprintf(query, "select startweek,endweek,order_date,order_time,order_room,order_amount,state_id from order_info where order_id='%d'", this->appoint_list[row]);
		res = connSQL->getMessage(query);
		if (res->next()) {
			sprintf(query, "update %s set room_margin_%d=room_margin_%d+%d where week between %d and %d and room_id=%d", weekdays[res->getInt(3) - 1].c_str(), res->getInt(4), res->getInt(4), res->getInt(6), res->getInt(1), res->getInt(2), res->getInt(5));
			int updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				sprintf(query, "update order_info set state_id=2 where order_id=%d", this->appoint_list[row]);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "提示", "拒绝成功", QMessageBox::Ok);
					appointView();
				}
			}
		}
	}
}

void AdminWindow::timer_handle() {
	appointView();
	on_table_changed();
}