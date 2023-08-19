/********************************************************************************
** Form generated from reading UI file 'connect_server_win.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONNECT_SERVER_WIN_H
#define UI_CONNECT_SERVER_WIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ConnectServerWinClass
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *lab_msg;

    void setupUi(QMainWindow *ConnectServerWinClass)
    {
        if (ConnectServerWinClass->objectName().isEmpty())
            ConnectServerWinClass->setObjectName("ConnectServerWinClass");
        ConnectServerWinClass->resize(248, 118);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ConnectServerWinClass->sizePolicy().hasHeightForWidth());
        ConnectServerWinClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(ConnectServerWinClass);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(centralWidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMinimumSize(QSize(0, 0));
        label->setMaximumSize(QSize(100, 100));
        label->setPixmap(QPixmap(QString::fromUtf8(":/pictures/poster.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        lab_msg = new QLabel(centralWidget);
        lab_msg->setObjectName("lab_msg");
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        lab_msg->setFont(font);

        horizontalLayout->addWidget(lab_msg);

        ConnectServerWinClass->setCentralWidget(centralWidget);

        retranslateUi(ConnectServerWinClass);

        QMetaObject::connectSlotsByName(ConnectServerWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *ConnectServerWinClass)
    {
        ConnectServerWinClass->setWindowTitle(QCoreApplication::translate("ConnectServerWinClass", "\346\217\220\347\244\272", nullptr));
        label->setText(QString());
        lab_msg->setText(QCoreApplication::translate("ConnectServerWinClass", "\350\277\236\346\216\245\346\234\215\345\212\241\345\231\250\344\270\255......\n"
"\350\257\267\345\213\277\345\205\263\351\227\255\347\250\213\345\272\217!", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ConnectServerWinClass: public Ui_ConnectServerWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONNECT_SERVER_WIN_H
