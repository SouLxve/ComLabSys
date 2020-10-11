#pragma execution_character_set("utf-8")

#include "MainWindow.h"
#include "stdafx.h"
#include "login.h"

MainWindow::MainWindow(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setFixedSize(1500, 900);
	this->setWindowState(Qt::WindowMaximized);
	this->setWindowTitle("机房预约管理系统");
	ui.appointnumberBox->setValidator(new QIntValidator(0, 100, this));
	ui.tabWidget->setCurrentIndex(0);
	ui.userFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.doappointFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	ui.myappointFrame->setStyleSheet("QFrame{ background: #eaeaea;border-radius: 12px;}");
	timer->setInterval(5000);
	setMainPage();
	connect(ui.logoutButton, &QPushButton::clicked, this, &MainWindow::on_logout_clicked);
	connect(ui.modifyButton, &QPushButton::clicked, this, &MainWindow::on_modify_clicked);
	connect(ui.messsubmitButton, &QPushButton::clicked, this, &MainWindow::on_messsubmit_clicked);
	connect(ui.passsubmitButton, &QPushButton::clicked, this, &MainWindow::on_passsubmit_clicked);
	connect(ui.userreturnButton, &QPushButton::clicked, this, &MainWindow::on_userreturn_clicked);
	connect(ui.substartBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &MainWindow::on_substart_changed);
	connect(ui.labkindBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &MainWindow::on_table_changed);
	connect(ui.weeknumberBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &MainWindow::on_table_changed);
	connect(ui.lessonweekBox, static_cast<void (QComboBox::*)(int index)> (&QComboBox::currentIndexChanged), this, &MainWindow::on_lesson_changed);
	connect(ui.submitButton, &QPushButton::clicked, this, &MainWindow::on_appoint_submit);
	connect(ui.clearButton, &QPushButton::clicked, this, &MainWindow::on_clear_clicked);
	connect(timer, &QTimer::timeout, this, &MainWindow::timer_handle);
	timer->start();
}


MainWindow::~MainWindow()
{
	timer->stop();
}

void MainWindow::on_logout_clicked() {
	userToken->Logout();
	login* l = new login;
	l->show();
	this->close();
}

void MainWindow::on_modify_clicked() {
	setUserPage();
}

void MainWindow::on_messsubmit_clicked() {
	string newphone = ui.newphoneLine->text().toStdString();
	string newemail = ui.newemailLine->text().toStdString();
	int flag=0, flag1=0;
	if (newphone != userToken->getPhone()) {
		flag = userToken->setPhone(newphone);
	}
	if (newemail != userToken->getEmail()) {
		flag1 = userToken->setEmail(newemail);
	}
	if (flag != 0 && flag1 != 0) {
		QMessageBox::information(this, "提示","联系方式与电子邮件更改失败", QMessageBox::Ok);
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

void MainWindow::on_passsubmit_clicked() {
	string oldpass = ui.oldpassLine->text().toStdString();
	string newpass = ui.newpassLine->text().toStdString();
	string newpass2 = ui.newpass2Line->text().toStdString();
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

void MainWindow::on_userreturn_clicked() {
	setMainPage();
}

void MainWindow::on_substart_changed() {
	char query[255];
	sprintf(query, "select distinct week from monday_room_margin");
	ResultSet* res = connSQL->getMessage(query);
	ui.subendBox->clear();
	int tmp = ui.substartBox->currentData().toInt();
	while (res->next()) {
		if (res->getInt(1) < tmp) {
			continue;
		}
		sprintf(query, "第%s周", res->getString(1).c_str());
		ui.weeknumberBox->addItem(query, res->getInt(1));
		ui.subendBox->addItem(query, res->getInt(1));
		ui.subendBox->setCurrentIndex(-1);
	}
}

void MainWindow::on_table_changed() {
	int type_id = ui.labkindBox->currentData().toInt();
	int week_id = ui.weeknumberBox->currentData().toInt();
	char query[255];
	ResultSet* res;
	for (int col = 0; col < 7; col++) {
		sprintf(query, "select sum(room_margin_1),sum(room_margin_2),sum(room_margin_3),sum(room_margin_4),sum(room_margin_5) from %s where room_id in (select room_id from room_info where room_type='%d') and week='%d'", weekdays[col].c_str(), type_id, week_id);
		res = connSQL->getMessage(query);
		while (res->next()) {
			ui.labTable->setItem(0, col, new QTableWidgetItem(QString::number(res->getInt(1))));
			ui.labTable->item(0, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.labTable->setItem(1, col, new QTableWidgetItem(QString::number(res->getInt(2))));
			ui.labTable->item(1, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.labTable->setItem(2, col, new QTableWidgetItem(QString::number(res->getInt(3))));
			ui.labTable->item(2, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.labTable->setItem(3, col, new QTableWidgetItem(QString::number(res->getInt(4))));
			ui.labTable->item(3, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			ui.labTable->setItem(4, col, new QTableWidgetItem(QString::number(res->getInt(5))));
			ui.labTable->item(4, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		}
	}
}

void MainWindow::on_lesson_changed() {
	ui.lessonTable->clearContents();
	int week_id = ui.weeknumberBox->currentData().toInt();
	char query[255];
	string table[5][7];
	int weekday = ui.lessonweekBox->currentData().toInt();
	sprintf(query, "select order_date,order_time,room_name from order_info,room_info where user_id=%d and state_id=3 and startweek<=%d and endweek>=%d and order_info.order_room=room_info.room_id", userToken->getID(), weekday, weekday);
	ResultSet* res = connSQL->getMessage(query);
	while (res->next()) {
		if (table[res->getInt(2) - 1][res->getInt(1) - 1] != "") {
			table[res->getInt(2) - 1][res->getInt(1) - 1].append("\n");
		}
		table[res->getInt(2)-1][res->getInt(1)-1].append(res->getString(3).c_str());
	}
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 7; col++) {
			if (table[row][col] != "") {
				ui.lessonTable->setItem(row, col, new QTableWidgetItem(QString::fromStdString(table[row][col])));
				ui.lessonTable->item(row, col)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
			}
		}
	}
}

void MainWindow::on_appoint_modify() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.appointTable->indexAt(QPoint(x, y));
	int row = index.row();
	this->order_id = this->appoint_list[row];
	char query[255];
	sprintf(query, "select room_info.room_type,order_info.order_room,startweek,endweek,order_date,order_time,order_amount from order_info,room_info where order_id='%d' and order_info.order_room=room_info.room_id", this->order_id);
	ResultSet* res = connSQL->getMessage(query);
	while (res->next()) {
		ui.sublabBox->setCurrentIndex(res->getInt(1)-1);
		ui.substartBox->setCurrentIndex(res->getInt(3) - 1);
		ui.subendBox->setCurrentIndex(res->getInt(4) - res->getInt(3));
		ui.subdayBox->setCurrentIndex(res->getInt(5) - 1);
		ui.sublessonBox->setCurrentIndex(res->getInt(6) - 1);
		ui.appointnumberBox->setText(QString::number(res->getInt(7)));
	}
	ui.submitButton->setText("修改申请");
	ui.clearButton->setText("取消修改");
}

void MainWindow::on_appoint_delete() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.appointTable->indexAt(QPoint(x, y));
	int row = index.row();
	char query[255];
	sprintf(query, "select startweek,endweek,order_date,order_time,order_room,order_amount,state_id from order_info where order_id='%d'", this->appoint_list[row]);
	ResultSet* res = connSQL->getMessage(query);
	int startweek, endweek, order_date, order_room, order_amount, order_time;
	while (res->next()) {
		if (res->getInt(6) == 0 || res->getInt(7) != 3) {
			sprintf(query, "delete from order_info where order_id=%d", this->appoint_list[row]);
			int updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				QMessageBox::information(this, "提示", "删除成功", QMessageBox::Ok);
			}
		}
		else {
			startweek = res->getInt(1);
			endweek = res->getInt(2);
			order_date = res->getInt(3);
			order_time = res->getInt(4);
			order_room = res->getInt(5);
			order_amount = res->getInt(6);
			sprintf(query, "update %s set room_margin_%d=room_margin_%d+%d where week between %d and %d and room_id=%d", weekdays[order_date - 1].c_str(), order_time, order_time, order_amount, startweek, endweek, order_room);
			int updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				sprintf(query, "delete from order_info where order_id=%d", this->appoint_list[row]);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "提示", "删除成功", QMessageBox::Ok);
					on_table_changed();
					on_lesson_changed();
				}
			}
		}
		on_clear_clicked();
		appointView();
	}
}

void MainWindow::on_appoint_submit() {
	int room_type, order_amount, startweek, endweek, order_date, order_time, room_id;
	room_type = ui.sublabBox->currentData().toInt();
	order_amount = ui.appointnumberBox->text().toInt();
	startweek = ui.substartBox->currentData().toInt();
	endweek = ui.subendBox->currentData().toInt();
	order_date = ui.subdayBox->currentData().toInt();
	order_time = ui.sublessonBox->currentData().toInt();
	if (order_amount <= 0 || room_type == 0 || startweek == 0 || endweek == 0 || order_date == 0 || order_time == 0) {
		QMessageBox::information(this, "提示", "申请信息有误", QMessageBox::Ok);
		return;
	}
	char query[255];
	ResultSet* res;
	if (this->order_id == 0) {
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
				sprintf(query, "insert into order_info(user_id,order_date,order_time,order_room,state_id,startweek,endweek,order_amount) values (%d,%d,%d,%d,1,%d,%d,%d)", userToken->getID(), order_date, order_time, room_id, startweek, endweek, order_amount);
				int updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "提示", "申请成功", QMessageBox::Ok);
					appointView();
					on_clear_clicked();
					return;
				}
				QMessageBox::information(this, "提示", "未知错误", QMessageBox::Ok);
				return;
			}
		}
		QMessageBox::information(this, "提示", "申请失败，该时间段机房剩余空间不足", QMessageBox::Ok);
		return;
	}
	sprintf(query, "select state_id from order_info where order_id=%d", this->order_id);
	res = connSQL->getMessage(query);
	if (res->next()) {
		if (res->getInt(1) == 1 || res->getInt(1) == 2) {
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
					sprintf(query, "update order_info set order_date=%d,order_time=%d,order_room=%d,state_id=1,startweek=%d,endweek=%d,order_amount=%d where order_id=%d", order_date, order_time, room_id, startweek, endweek, order_amount, this->order_id);
					int updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						QMessageBox::information(this, "提示", "修改成功", QMessageBox::Ok);
						appointView();
						on_clear_clicked();
						return;
					}
					QMessageBox::information(this, "提示", "未知错误", QMessageBox::Ok);
					return;
				}
			}
			QMessageBox::information(this, "提示", "修改失败，该时间段机房剩余空间不足", QMessageBox::Ok);
			return;
		}
	}
}

void MainWindow::on_clear_clicked() {
	this->order_id = 0;
	ui.sublabBox->setCurrentIndex(-1);
	ui.subdayBox->setCurrentIndex(-1);
	ui.subendBox->setCurrentIndex(-1);
	ui.sublessonBox->setCurrentIndex(-1);
	ui.substartBox->setCurrentIndex(-1);
	ui.appointnumberBox->setText("");
	ui.submitButton->setText("提交");
	ui.clearButton->setText("清空");
}

void MainWindow::timer_handle() {
	on_table_changed();
	on_lesson_changed();
	appointView();
}


//初始化

void MainWindow::setMainPage() {
	ui.stackedWidget->setCurrentWidget(ui.mainPage);
	ui.usernameLine->setText(QString::fromStdString(userToken->getUsername()));
	ui.phoneLine->setText(QString::fromStdString(userToken->getPhone()));
	ui.emailLine->setText(QString::fromStdString(userToken->getEmail()));
	ui.premissionLine->setText(QString::number(userToken->getPermission()));
	ui.labTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	ui.labTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.labTable->setShowGrid(false);
	ui.labTable->setFocusPolicy(Qt::NoFocus);
	ui.lessonTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	ui.lessonTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.lessonTable->setShowGrid(false);
	ui.lessonTable->setFocusPolicy(Qt::NoFocus);
	ui.appointTable->verticalHeader()->setMinimumSectionSize(60);
	ui.appointTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配列宽
	//ui.appointTable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//平均分配行宽
	ui.appointTable->verticalHeader()->setDefaultSectionSize(60);
	ui.appointTable->setShowGrid(false);
	ui.appointTable->setFocusPolicy(Qt::NoFocus);
	initBoxs();//初始化下拉框
	appointView(); 
	on_clear_clicked();
	timer->start();
}

void MainWindow::setUserPage() {
	ui.stackedWidget->setCurrentWidget(ui.userPage);
	ui.unusernameLine->setText(QString::fromStdString(userToken->getUsername()));
	ui.newemailLine->setText(QString::fromStdString(userToken->getEmail()));
	ui.newphoneLine->setText(QString::fromStdString(userToken->getPhone()));
	ui.unpremisionLine->setText(QString::number(userToken->getPermission()));
	timer->stop();
}

void MainWindow::initBoxs() {
	ui.subdayBox->clear();
	ui.labkindBox->clear();
	ui.sublabBox->clear();
	ui.sublessonBox->clear();
	ui.weeknumberBox->clear();
	ui.lessonweekBox->clear();
	ui.substartBox->clear();
	char query[255];
	//data_info
	sprintf(query, "select * from date_info");
	ResultSet* res = connSQL->getMessage(query);
	while (res->next()) {
		ui.subdayBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	res = connSQL->getMessage(query);
	//type_info
	sprintf(query, "select * from type_info");
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.labkindBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
		ui.sublabBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	//time_info
	sprintf(query, "select * from time_info");
	res = connSQL->getMessage(query);
	while (res->next()) {
		ui.sublessonBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
	}
	//week
	sprintf(query, "select distinct week from monday_room_margin");
	res = connSQL->getMessage(query);
	while (res->next()) {
		sprintf(query, "第%s周", res->getString(1).c_str());
		ui.weeknumberBox->addItem(query, res->getInt(1));
		ui.lessonweekBox->addItem(query, res->getInt(1));
		ui.substartBox->addItem(query, res->getInt(1));
	}
	ui.subdayBox->setCurrentIndex(-1);
	ui.sublabBox->setCurrentIndex(-1);
	ui.substartBox->setCurrentIndex(-1);
	ui.sublessonBox->setCurrentIndex(-1);
	ui.labkindBox->setCurrentIndex(0);
	ui.weeknumberBox->setCurrentIndex(0);
	ui.lessonweekBox->setCurrentIndex(0);
	on_table_changed();
}

void MainWindow::appointView() {
	char query[500];
	sprintf(query, "select order_info.startweek,order_info.endweek,date_info.date_str,time_info.time_str,room_info.room_name,state_info.state_str,order_info.order_id,order_amount,order_info.state_id from order_info,date_info,room_info,state_info,time_info where user_id= '%d' and order_info.order_room=room_info.room_id and order_info.state_id=state_info.state_id and order_info.order_date=date_info.date_id and order_info.order_time=time_info.time_id order by order_info.state_id", userToken->getID());
	ResultSet* res = connSQL->getMessage(query);
	QPushButton* change, * del;
	QWidget* tmp_widget;
	QHBoxLayout* tmp_layout;
	ui.appointTable->clearContents();
	ui.appointTable->setRowCount(0);
	for (int row = 0; res->next(); row++) {
		this->appoint_list[row] = res->getInt(7);
		ui.appointTable->insertRow(row);
		ui.appointTable->setItem(row, 0, new QTableWidgetItem(QString::number(res->getInt(1))));
		ui.appointTable->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//元素居中
		ui.appointTable->setItem(row, 1, new QTableWidgetItem(QString::number(res->getInt(2))));
		ui.appointTable->item(row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.appointTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(res->getString(3).c_str())));
		ui.appointTable->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.appointTable->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(res->getString(4).c_str())));
		ui.appointTable->item(row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.appointTable->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(res->getString(8).c_str())));
		ui.appointTable->item(row, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.appointTable->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(res->getString(5).c_str())));
		ui.appointTable->item(row, 5)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.appointTable->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(res->getString(6).c_str())));
		ui.appointTable->item(row, 6)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		change = new QPushButton();
		//change->setText("修改");
		change->setIcon(QIcon::fromTheme("folder", QIcon(":/login/edit.png")));
		change->setIconSize(QSize(24, 24));
		change->setStyleSheet("QPushButton{min-width:32px;max-width:32px;min-height:32px;max-height:32px;border: none; background-color:transparent;}QPushButton:hover{background-color:#dcdcdc;}QPushButton:pressed{background-color:#c5c5c5;}");
		change->setFixedSize(48, 48);
		if (res->getInt(9) == 3) {
			change->setEnabled(false);
		}
		del = new QPushButton();
		//del->setText("撤销");
		del->setIcon(QIcon::fromTheme("folder", QIcon(":/login/close-bold.png")));
		del->setIconSize(QSize(24, 24));
		del->setStyleSheet("QPushButton{min-width:32px;max-width:32px;min-height:32px;max-height:32px;border: none; background-color:transparent;}QPushButton:hover{background-color:#dcdcdc;}QPushButton:pressed{background-color:#c5c5c5;}");
		del->setFixedSize(48, 48);
		tmp_widget = new QWidget();
		tmp_layout = new QHBoxLayout(tmp_widget);
		tmp_layout->addWidget(change);
		tmp_layout->addWidget(del);
		tmp_layout->setMargin(0);
		ui.appointTable->setCellWidget(row, 7, tmp_widget);
		connect(change, &QPushButton::clicked, this, &MainWindow::on_appoint_modify);
		connect(del, &QPushButton::clicked, this, &MainWindow::on_appoint_delete);
	}
}