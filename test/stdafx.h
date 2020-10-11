#pragma once
#include "ConnectMysql.h"
#include "UserNow.h"
#include <QTimer>
#include <QMessageBox>
#include <QIntValidator>
#include <QDesktopWidget>

extern ConnectMysql* connSQL;
extern UserNow* userToken;
extern std::string weekdays[7];
extern QTimer* timer;