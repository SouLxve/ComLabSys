#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/********************数据库配置信息***********************/
QString dataBaseIP = "localhost";
QString dataBase = "test";
unsigned int dataBasePort = 3306;
QString dataBaseUser = "sms";
QString dataBasePWD = "1234";
bool connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dataBaseIP);   //主机名称，如localhost
    db.setDatabaseName(dataBase);    //数据库名称
    db.setPort(dataBasePort);              //数据库端口号
    db.setUserName(dataBaseUser);        //用户名称
    db.setPassword(dataBasePWD);      //用户密码
    db.open();
    if (db.isOpen())
    {

        return true;
    }
    else
    {
        return false;
    }
}
#endif // GLOBALCONFIG_H
