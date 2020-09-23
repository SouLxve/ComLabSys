#include "stdafx.h"

ConnectMysql* connSQL = new ConnectMysql();
UserNow* userToken = new UserNow();
string weekdays[7] = { "monday_room_margin","tuesday_room_margin","wednesday_room_margin","thursday_room_margin","friday_room_margin","saturday_room_margin","sunday_room_margin" };
QTimer* timer = new QTimer();