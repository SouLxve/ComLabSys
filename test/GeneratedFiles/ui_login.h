/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.12.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_loginClass
{
public:
    QGridLayout *gridLayout;
    QLineEdit *nameLine;
    QSpacerItem *verticalSpacer_4;
    QLabel *label;
    QPushButton *loginButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer;
    QPushButton *editButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *passwordLine;
    QLabel *label_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *registerButton;

    void setupUi(QDialog *loginClass)
    {
        if (loginClass->objectName().isEmpty())
            loginClass->setObjectName(QString::fromUtf8("loginClass"));
        loginClass->resize(600, 400);
        QIcon icon;
        icon.addFile(QString::fromUtf8("\347\224\250\346\210\267.png"), QSize(), QIcon::Normal, QIcon::Off);
        loginClass->setWindowIcon(icon);
        gridLayout = new QGridLayout(loginClass);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        nameLine = new QLineEdit(loginClass);
        nameLine->setObjectName(QString::fromUtf8("nameLine"));

        gridLayout->addWidget(nameLine, 3, 3, 1, 3);

        verticalSpacer_4 = new QSpacerItem(20, 41, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_4, 13, 4, 1, 1);

        label = new QLabel(loginClass);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 3, 1, 1, 1);

        loginButton = new QPushButton(loginClass);
        loginButton->setObjectName(QString::fromUtf8("loginButton"));

        gridLayout->addWidget(loginButton, 8, 3, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 6, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(137, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 4, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 6, 5, 1, 1);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_6, 1, 4, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 14, 4, 1, 1);

        editButton = new QPushButton(loginClass);
        editButton->setObjectName(QString::fromUtf8("editButton"));

        gridLayout->addWidget(editButton, 8, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(136, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 6, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 3, 1, 3);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 9, 4, 1, 1);

        passwordLine = new QLineEdit(loginClass);
        passwordLine->setObjectName(QString::fromUtf8("passwordLine"));
        passwordLine->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(passwordLine, 5, 3, 1, 3);

        label_2 = new QLabel(loginClass);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setLayoutDirection(Qt::LeftToRight);
        label_2->setTextFormat(Qt::AutoText);

        gridLayout->addWidget(label_2, 5, 1, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_2, 0, 4, 1, 1);

        registerButton = new QPushButton(loginClass);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));

        gridLayout->addWidget(registerButton, 14, 6, 1, 1);

        QWidget::setTabOrder(nameLine, passwordLine);
        QWidget::setTabOrder(passwordLine, loginButton);
        QWidget::setTabOrder(loginButton, editButton);
        QWidget::setTabOrder(editButton, registerButton);

        retranslateUi(loginClass);

        QMetaObject::connectSlotsByName(loginClass);
    } // setupUi

    void retranslateUi(QDialog *loginClass)
    {
        loginClass->setWindowTitle(QApplication::translate("loginClass", "\347\231\273\345\275\225", nullptr));
        label->setText(QApplication::translate("loginClass", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        loginButton->setText(QApplication::translate("loginClass", "\347\231\273\345\275\225", nullptr));
        editButton->setText(QApplication::translate("loginClass", "\346\270\205\347\251\272", nullptr));
        label_2->setText(QApplication::translate("loginClass", "\345\257\206\347\240\201\357\274\232", nullptr));
        registerButton->setText(QApplication::translate("loginClass", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class loginClass: public Ui_loginClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
