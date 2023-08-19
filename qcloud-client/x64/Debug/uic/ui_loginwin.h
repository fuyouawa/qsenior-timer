/********************************************************************************
** Form generated from reading UI file 'loginwin.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIN_H
#define UI_LOGINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWinClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *edit_user_name;
    QLabel *label_2;
    QLineEdit *edit_password;
    QToolButton *btn_view_pwd;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_signin;
    QPushButton *btn_login;

    void setupUi(QMainWindow *LoginWinClass)
    {
        if (LoginWinClass->objectName().isEmpty())
            LoginWinClass->setObjectName("LoginWinClass");
        LoginWinClass->resize(247, 100);
        centralWidget = new QWidget(LoginWinClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        edit_user_name = new QLineEdit(centralWidget);
        edit_user_name->setObjectName("edit_user_name");

        gridLayout->addWidget(edit_user_name, 0, 1, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        edit_password = new QLineEdit(centralWidget);
        edit_password->setObjectName("edit_password");
        edit_password->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(edit_password, 1, 1, 1, 1);

        btn_view_pwd = new QToolButton(centralWidget);
        btn_view_pwd->setObjectName("btn_view_pwd");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/close_eyes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_view_pwd->setIcon(icon);
        btn_view_pwd->setCheckable(true);
        btn_view_pwd->setChecked(false);

        gridLayout->addWidget(btn_view_pwd, 1, 2, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_signin = new QPushButton(centralWidget);
        btn_signin->setObjectName("btn_signin");

        horizontalLayout->addWidget(btn_signin);

        btn_login = new QPushButton(centralWidget);
        btn_login->setObjectName("btn_login");
        btn_login->setEnabled(true);

        horizontalLayout->addWidget(btn_login);


        verticalLayout->addLayout(horizontalLayout);

        LoginWinClass->setCentralWidget(centralWidget);

        retranslateUi(LoginWinClass);

        QMetaObject::connectSlotsByName(LoginWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWinClass)
    {
        LoginWinClass->setWindowTitle(QCoreApplication::translate("LoginWinClass", "\347\231\273\345\275\225\347\225\214\351\235\242", nullptr));
        label->setText(QCoreApplication::translate("LoginWinClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        label_2->setText(QCoreApplication::translate("LoginWinClass", "\345\257\206\347\240\201", nullptr));
        btn_view_pwd->setText(QString());
        btn_signin->setText(QCoreApplication::translate("LoginWinClass", "\347\231\273\345\275\225", nullptr));
        btn_login->setText(QCoreApplication::translate("LoginWinClass", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWinClass: public Ui_LoginWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIN_H
