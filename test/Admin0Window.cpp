#pragma execution_character_set("utf-8")

#include "Admin0Window.h"
#include "stdafx.h"
#include "login.h"

using namespace std;

int row = -1;

Admin0Window::Admin0Window(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	this->setWindowState(Qt::WindowMaximized);
	this->setWindowTitle("����ԤԼ����ϵͳ����������Ա��");
	ui.tabWidget->setCurrentIndex(0);
	ui.weeknumEdit->setValidator(new QIntValidator(1, 100, this));
	setMainPage();
	connect(ui.logoutButton, &QPushButton::clicked, this, &Admin0Window::on_logout_clicked);
	connect(ui.submitButton, &QPushButton::clicked, this, &Admin0Window::on_submit_clicked);
	connect(ui.returnButton, &QPushButton::clicked, this, &Admin0Window::on_return_clicked);
	connect(ui.tabWidget, static_cast<void (QTabWidget::*)(int index)> (&QTabWidget::currentChanged), this, &Admin0Window::on_tab_changed);
	connect(ui.addlabButton, &QPushButton::clicked, this, &Admin0Window::on_addlab_clicked);
	connect(ui.resetButton, &QPushButton::clicked, this, &Admin0Window::on_reset_clicked);
}

Admin0Window::~Admin0Window()
{
}

void Admin0Window::on_logout_clicked() {
	userToken->Logout();
	login* l = new login;
	l->show();
	this->close();
}

void Admin0Window::on_submit_clicked() {
	string username = ui.nameLine->text().toStdString();
	string newpass = ui.passwordLine->text().toStdString();
	string newpass2 = ui.password2Line->text().toStdString();
	int premission = ui.premissionLine->text().toInt();
	int premission2 = ui.tableWidget->item(row, 2)->text().toInt();
	string phone = ui.phoneLine->text().toStdString();
	string email = ui.emailLine->text().toStdString();
	string phone2 = ui.tableWidget->item(row, 3)->text().toStdString();
	string email2 = ui.tableWidget->item(row, 4)->text().toStdString();
	int passf = -1, premf = -1, phof = -1, emaf = -1;
	if (newpass != "") {
		if (newpass2 == "") {
			QMessageBox::information(this, "��ʾ", "��ȷ��������", QMessageBox::Ok);
		}
		else if (newpass != newpass2) {
			QMessageBox::information(this, "��ʾ", "��ȷ���������������һ��", QMessageBox::Ok);
		}
		else {
			passf = userToken->AdminChangePassword(username, newpass);
		}
	}
	if (premission != premission2) {
		premf = userToken->setPermission(username, premission);
	}
	if (username == userToken->getUsername()) {
		if (phone != phone2) {
			phof = userToken->setPhone(phone);
		}
		if (email != email2) {
			emaf = userToken->setEmail(email);
		}
	}
	if ((passf == 0 || passf == -1) && (premf == 0 || premf == -1) && (phof == 0 || phof == -1) && (emaf == 0 || emaf == -1)) {
		QMessageBox::information(this, "��ʾ", "���ĳɹ�", QMessageBox::Ok);
		premission2 = premission;
		phone2 = phone;
		email2 = email;
	}
	else {
		string query = "";
		string paw = "���� ";
		string phw = "��ϵ�绰 ";
		string emw = "�������� ";
		string pew = "Ȩ�޵ȼ� ";
		if (passf > 0)
			query.append(paw);
		if (premf > 0)
			query.append(pew);
		if (phof > 0)
			query.append(phw);
		if (emaf > 0)
			query.append(emw);
		query.append("����ʧ��");
		QMessageBox::information(this, "��ʾ", QString::fromStdString(query), QMessageBox::Ok);
	}
	setUserPage(username, phone2, email2, premission2);
}

void Admin0Window::on_return_clicked() {
	setMainPage();
}

void Admin0Window::setMainPage() {
	ui.stackedWidget->setCurrentWidget(ui.mainPage);
	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(0);
	string query = "SELECT * FROM users";
	ResultSet* res = connSQL->getMessage(query);
	QString id, name, permission, phone, email;
	QPushButton* change;
	for (int i = 0; res->next(); i++) {
	    id = QString::number(res->getInt("user_id"));
		name = QString::fromStdString(res->getString("user_name").c_str());
		permission = QString::number(res->getInt("user_permission"));
		phone = QString::fromStdString(res->getString("user_phone").c_str());
		email = QString::fromStdString(res->getString("user_email").c_str());
		ui.tableWidget->insertRow(i);
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(id));
		ui.tableWidget->item(i, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(name));
		ui.tableWidget->item(i, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(permission));
		ui.tableWidget->item(i, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(phone));
		ui.tableWidget->item(i, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(email));
		ui.tableWidget->item(i, 4)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		change = new QPushButton();
		ui.tableWidget->setCellWidget(i, 5, change);
		connect(change, &QPushButton::clicked, this, &Admin0Window::on_change_clicked);
	}
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //��ֹ�༭
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);     //���ָ���
	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ�������п�
}

void Admin0Window::setUserPage(string name, string phone, string email, int perm) {
	ui.stackedWidget->setCurrentWidget(ui.userPage);
	ui.nameLine->setText(QString::fromStdString(name));
	ui.emailLine->setText(QString::fromStdString(email));
	ui.phoneLine->setText(QString::fromStdString(phone));
	ui.premissionLine->setText(QString::number(perm));
	if (name == userToken->getUsername()) {
		ui.phoneLine->setFocusPolicy(Qt::StrongFocus);
		ui.phoneLine->setReadOnly(false);
		ui.phoneLine->setStyleSheet("background-color:rgba(255,255,255,255)");
		ui.emailLine->setFocusPolicy(Qt::StrongFocus);
		ui.emailLine->setReadOnly(false);
		ui.emailLine->setStyleSheet("background-color:rgba(255,255,255,255)");
	}
	else {
		ui.phoneLine->setFocusPolicy(Qt::NoFocus);
		ui.phoneLine->setReadOnly(true);
		ui.phoneLine->setStyleSheet("background-color:rgba(241,241,241,241);");
		ui.emailLine->setFocusPolicy(Qt::NoFocus);
		ui.emailLine->setReadOnly(true);
		ui.emailLine->setStyleSheet("background-color:rgba(241,241,241,241)");
	}
}

void Admin0Window::on_change_clicked() {
	QPushButton* senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == 0)
	{
		return;
	}
	QModelIndex index = ui.tableWidget->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	row = index.row();
	setUserPage(ui.tableWidget->item(row, 1)->text().toStdString(), ui.tableWidget->item(row, 3)->text().toStdString(), ui.tableWidget->item(row, 4)->text().toStdString(), ui.tableWidget->item(row, 2)->text().toInt());
}

void Admin0Window::showLabRoom() {
	ui.tableWidget_2->clearContents();
	ui.tableWidget_2->setRowCount(0);
	QPushButton* modify, * del;
	QWidget* tmp_widget;
	QHBoxLayout* tmp_layout;
	char query[255];
	sprintf(query, "select * from room_info");
	ResultSet* res = connSQL->getMessage(query);
	for (int row = 0; res->next(); row++) {
		ui.tableWidget_2->insertRow(row);
		ui.tableWidget_2->setItem(row, 0, new QTableWidgetItem(QString::number(res->getInt(1))));
		ui.tableWidget_2->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget_2->item(row, 0)->setFlags(ui.tableWidget_2->item(row, 0)->flags() & (~Qt::ItemIsEditable));
		ui.tableWidget_2->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(res->getString(2).c_str())));
		ui.tableWidget_2->item(row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget_2->setItem(row, 2, new QTableWidgetItem(QString::number(res->getInt(3))));
		ui.tableWidget_2->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget_2->setItem(row, 3, new QTableWidgetItem(QString::number(res->getInt(4))));
		ui.tableWidget_2->item(row, 3)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		modify = new QPushButton();
		modify->setText("�޸�");
		del = new QPushButton();
		del->setText("ɾ��");
		tmp_widget = new QWidget();
		tmp_layout = new QHBoxLayout(tmp_widget);
		tmp_layout->addWidget(modify);
		tmp_layout->addWidget(del);
		tmp_layout->setMargin(0);
		ui.tableWidget_2->setCellWidget(row, 4, tmp_widget);
		connect(modify, &QPushButton::clicked, this, &Admin0Window::on_modify_clicked);
		connect(del, &QPushButton::clicked, this, &Admin0Window::on_del_clicked);
	}
}

void Admin0Window::showLabType() {
	ui.tableWidget_3->clearContents();
	ui.tableWidget_3->setRowCount(0);
	char query[255];
	QPushButton* change;
	sprintf(query, "select type_id,type_str,user_name from type_info,users where type_info.user_id=users.user_id");
	ResultSet* res = connSQL->getMessage(query);
	for (int row = 0; res->next(); row++) {
		ui.tableWidget_3->insertRow(row);
		ui.tableWidget_3->setItem(row, 0, new QTableWidgetItem(QString::number(res->getInt(1))));
		ui.tableWidget_3->item(row, 0)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget_3->item(row, 0)->setFlags(ui.tableWidget_3->item(row, 0)->flags() & (~Qt::ItemIsEditable));
		ui.tableWidget_3->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(res->getString(2).c_str())));
		ui.tableWidget_3->item(row, 1)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		ui.tableWidget_3->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(res->getString(3).c_str())));
		ui.tableWidget_3->item(row, 2)->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);//Ԫ�ؾ���
		change = new QPushButton();
		ui.tableWidget_3->setCellWidget(row, 3, change);
		change->setText("�޸�");
		connect(change, &QPushButton::clicked, this, &Admin0Window::on_modify2_clicked);
	}
}

void Admin0Window::on_modify_clicked() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.tableWidget_2->indexAt(QPoint(x, y));
	int row = index.row();
	string name = ui.tableWidget_2->item(row, 1)->text().toStdString();
	int max = ui.tableWidget_2->item(row, 2)->text().toInt();
	int type = ui.tableWidget_2->item(row, 3)->text().toInt();
	int id = ui.tableWidget_2->item(row, 0)->text().toInt();
	if ((type != 1 && type != 2 && type != 3) || max <= 0) {
		QMessageBox::information(this, "��ʾ", "���ݸ�ʽ����", QMessageBox::Ok);
		return;
	}
	char query[255];
	sprintf(query, "select * from room_info where room_id=%d", id);
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		string room_name = res->getString(2).c_str();
		int room_max = res->getInt(3);
		if (room_max == max) {
			sprintf(query, "update room_info set room_name='%s',room_type=%d where room_id=%d", name.c_str(), type, id);
			int updateCount = connSQL->updateMessage(query);
			if (updateCount > 0) {
				QMessageBox::information(this, "��ʾ", "�޸ĳɹ�", QMessageBox::Ok);
			}
			else {
				QMessageBox::information(this, "��ʾ", "δ�����κ��޸�", QMessageBox::Ok);
			}
		}
		else if (room_max != max) {
			if (room_max > max) {
				int updateCount;
				for (int i = 0; i < 7; i++) {
					sprintf(query, "select * from %s where (room_margin_1<%d or room_margin_2<%d or room_margin_3<%d or room_margin_4<%d or room_margin_5<%d) and room_id=%d", weekdays[i].c_str(), room_max - max, room_max - max, room_max - max, room_max - max, room_max - max, id);
					res = connSQL->getMessage(query);
					if (res->next()) {
						QMessageBox::information(this, "��ʾ", "�޸�ʧ��", QMessageBox::Ok);
						showLabRoom();
						return;
					}
				}
				for (int i = 0; i < 7; i++) {
					sprintf(query, "update %s set room_margin_1=room_margin_1-%d,room_margin_2=room_margin_2-%d,room_margin_3=room_margin_3-%d,room_margin_4=room_margin_4-%d,room_margin_5=room_margin_5-%d where room_id=%d", weekdays[i].c_str(), room_max - max, room_max - max, room_max - max, room_max - max, room_max - max, id);
					updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						continue;
					}
					else {
						QMessageBox::information(this, "��ʾ", "����������������Ҫ��������Ա����ϵͳ", QMessageBox::Ok);
					}
				}
				sprintf(query, "update room_info set room_name='%s',room_max_num=%d,room_type=%d where room_id=%d", name.c_str(), max, type, id);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "��ʾ", "�޸ĳɹ�", QMessageBox::Ok);
				}
			}
			else
			{
				int updateCount;
				for (int i = 0; i < 7; i++) {
					sprintf(query, "update %s set room_margin_1=room_margin_1+%d,room_margin_2=room_margin_2+%d,room_margin_3=room_margin_3+%d,room_margin_4=room_margin_4+%d,room_margin_5=room_margin_5+%d where room_id=%d", weekdays[i].c_str(), max - room_max, max - room_max, max - room_max, max - room_max, max - room_max, id);
					updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						continue;
					}
					else {
						QMessageBox::information(this, "��ʾ", "����������������Ҫ��������Ա����ϵͳ", QMessageBox::Ok);
					}
				}
				sprintf(query, "update room_info set room_name='%s',room_max_num=%d,room_type=%d where room_id=%d", name.c_str(), max, type, id);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					QMessageBox::information(this, "��ʾ", "�޸ĳɹ�", QMessageBox::Ok);
				}
			}
		}
	}
}

void Admin0Window::on_del_clicked() {
	QPushButton* btn = (QPushButton*)sender();
	QWidget* w_parent = (QWidget*)btn->parent();
	int x = w_parent->mapToParent(QPoint(0, 0)).x();
	int y = w_parent->mapToParent(QPoint(0, 0)).y();
	QModelIndex index = ui.tableWidget_2->indexAt(QPoint(x, y));
	int row = index.row();
	int room_id = ui.tableWidget_2->item(row, 0)->text().toInt();
	char query[255];
	sprintf(query, "select * from order_info where order_room=%d", room_id);
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		QMessageBox::information(this, "��ʾ", "ɾ��ʧ�ܣ�ԤԼ���л�������ؼ�¼", QMessageBox::Ok);
	}
	else {
		sprintf(query, "delete from room_info where room_id=%d", room_id);
		int updateCount = connSQL->updateMessage(query);
		if (updateCount > 0) {
			QMessageBox::information(this, "��ʾ", "ɾ���ɹ�", QMessageBox::Ok);
			for (int i = 0; i < 7; i++) {
				sprintf(query, "delete from %s where room_id=%d", weekdays[i].c_str(), room_id);
				updateCount = connSQL->updateMessage(query);
				if (updateCount > 0) {
					continue;
				}
				else {
					QMessageBox::information(this, "��ʾ", "������δ֪�Ĵ���", QMessageBox::Ok);
				}
			}
		}
		else {
			QMessageBox::information(this, "��ʾ", "ɾ��ʧ��", QMessageBox::Ok);
		}
	}
	showLabRoom();
}

void Admin0Window::on_modify2_clicked() {
	QPushButton* senderObj = qobject_cast<QPushButton*>(sender());
	if (senderObj == 0)
	{
		return;
	}
	QModelIndex index = ui.tableWidget_3->indexAt(QPoint(senderObj->frameGeometry().x(), senderObj->frameGeometry().y()));
	int row = index.row();
	string teacher = ui.tableWidget_3->item(row, 2)->text().toStdString();
	string type = ui.tableWidget_3->item(row, 1)->text().toStdString();
	int id = ui.tableWidget_3->item(row, 0)->text().toInt();
	char query[255];
	sprintf(query, "select user_id from users where user_name='%s' and user_permission=1", teacher.c_str());
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		sprintf(query, "update type_info set type_str='%s',user_id=%d where type_id=%d", type.c_str(), res->getInt(1), id);
		int updateCount = connSQL->updateMessage(query);
		if (updateCount > 0) {
			QMessageBox::information(this, "��ʾ", "�޸ĳɹ�", QMessageBox::Ok);
		}
		else {
			QMessageBox::information(this, "��ʾ", "δ���κ��޸�", QMessageBox::Ok);
		}
	}
	else {
		QMessageBox::information(this, "��ʾ", "����������", QMessageBox::Ok);
	}
}

void Admin0Window::on_tab_changed() {
	if (ui.tabWidget->currentIndex() == 1) {
		ui.tableWidget_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ�������п�
		ui.tableWidget_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ�������п�
		ui.tableWidget_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ�������п�
		ui.tableWidget_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);//ƽ�������п�
		showLabRoom();
		showLabType();
		char query[255];
		sprintf(query, "select * from type_info");
		ResultSet* res = connSQL->getMessage(query);
		while (res->next()) {
			ui.labtypeBox->addItem(QString::fromStdString(res->getString(2).c_str()), res->getInt(1));
		}
		ui.labtypeBox->setCurrentIndex(-1);
	}
}

void Admin0Window::on_addlab_clicked() {
	string name = ui.labnameEdit->text().toStdString();
	int num = ui.labnumEdit->text().toInt();
	int type=ui.labtypeBox->currentData().toInt();
	char query[255];
	sprintf(query, "select room_id from room_info where room_name='%s'", name.c_str());
	ResultSet* res = connSQL->getMessage(query);
	if (res->next()) {
		QMessageBox::information(this, "��ʾ", "�û����Ѵ���", QMessageBox::Ok);
		return;
	}
	sprintf(query, "insert into room_info (room_name,room_max_num,room_type) values ('%s',%d,%d)", name.c_str(), num, type);
	int updateCount = connSQL->updateMessage(query);
	if (updateCount > 0) {
		sprintf(query, "select distinct week from monday_room_margin");
		ResultSet* res = connSQL->getMessage(query);
		sprintf(query, "select room_id from room_info where room_name='%s'", name.c_str());
		ResultSet* tmp = connSQL->getMessage(query);
		if (tmp->next()) {
			while (res->next()) {
				for (int i = 0; i < 7; i++) {
					sprintf(query, "insert into %s (room_id,room_margin_1,room_margin_2,room_margin_3,room_margin_4,room_margin_5,week) values (%d,%d,%d,%d,%d,%d,%d)", weekdays[i].c_str(), tmp->getInt(1), num, num, num, num, num, res->getInt(1));
					updateCount = connSQL->updateMessage(query);
					if (updateCount > 0) {
						continue;
					}
					else {
						QMessageBox::information(this, "��ʾ", "������δ֪�Ĵ���", QMessageBox::Ok);
					}
				}
			}
		}
	}
	QMessageBox::information(this, "��ʾ", "������", QMessageBox::Ok);
	showLabRoom();
}

void Admin0Window::on_reset_clicked() {
	int weeks = ui.weeknumEdit->text().toInt();
	if (weeks <= 0) {
		QMessageBox::information(this, "��ʾ", "������ʽ����", QMessageBox::Ok);
		return;
	}
	char query[255];
	sprintf(query, "truncate table order_info");
	int count = connSQL->updateMessage(query);
	for (int i = 0; i < 7; i++) {
		sprintf(query, "truncate table %s", weekdays[i].c_str());
		count = connSQL->updateMessage(query);
	}
	sprintf(query, "select room_id,room_max_num from room_info");
	ResultSet* res = connSQL->getMessage(query);
	int max, id;
	while (res->next()) {
		max = res->getInt(2);
		id = res->getInt(1);
		for (int i = 0; i < 7; i++) {
			for (int j = 1; j <= weeks; j++) {
				sprintf(query, "insert into %s (room_id,room_margin_1,room_margin_2,room_margin_3,room_margin_4,room_margin_5,week) values (%d,%d,%d,%d,%d,%d,%d)", weekdays[i].c_str(), id, max, max, max, max, max, j);
				count = connSQL->updateMessage(query);
			}
		}
	}
	QMessageBox::information(this, "��ʾ", "���óɹ�", QMessageBox::Ok);
	ui.weeknumEdit->setText("");
}