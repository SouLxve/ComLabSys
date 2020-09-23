#pragma once

#include <QWidget>
#include "ui_Register.h"

class Register : public QWidget
{
	Q_OBJECT

public:
	Register(QWidget *parent = Q_NULLPTR);
	~Register();

private slots:
	void on_submit_clicked();
	void on_return_clicked();

private:
	Ui::Register ui;
};
