#include "login.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QDebug>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login w;
        w.show();
        return a.exec();
    
}
