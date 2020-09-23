#ifndef GLOBALCONFIG_H
#define GLOBALCONFIG_H
#include <QString>
#include <QDebug>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

/********************���ݿ�������Ϣ***********************/
QString dataBaseIP = "localhost";
QString dataBase = "test";
unsigned int dataBasePort = 3306;
QString dataBaseUser = "sms";
QString dataBasePWD = "1234";
bool connectDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(dataBaseIP);   //�������ƣ���localhost
    db.setDatabaseName(dataBase);    //���ݿ�����
    db.setPort(dataBasePort);              //���ݿ�˿ں�
    db.setUserName(dataBaseUser);        //�û�����
    db.setPassword(dataBasePWD);      //�û�����
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
