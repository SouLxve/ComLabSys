#include "login.h"
#include <QtWidgets/QApplication>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QDesktopWidget>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/login/base.css");
    if (file.open(QFile::ReadOnly))
    {
        QString styleSheet = QLatin1String(file.readAll());
        a.setStyleSheet(styleSheet);
        file.close();

    }
    else  // 引入出错
    {
        QMessageBox::warning(NULL, "warning", "Open failed", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    login w;
    w.move((QApplication::desktop()->availableGeometry().width() - w.width()) / 2, (QApplication::desktop()->availableGeometry().height() - w.height()) / 2);
    w.show();
    return a.exec();
}
