/********************************************************************************
** Form generated from reading UI file 'mainwin.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIN_H
#define UI_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWinClass
{
public:
    QAction *act_add_backups;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *edit_user_name;
    QLineEdit *edit_password;
    QToolButton *btn_view_pwd;
    QLabel *label_3;
    QLabel *label;
    QPushButton *btn_logout;
    QDateTimeEdit *edit_registry_date;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_4;
    QDateTimeEdit *edit_update_date;
    QLabel *label_6;
    QSpinBox *edit_update_count;
    QLabel *label_5;
    QSpinBox *edit_saves_size;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_upload_saves;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_download_saves;
    QSpacerItem *horizontalSpacer_4;
    QPlainTextEdit *edit_log;

    void setupUi(QMainWindow *MainWinClass)
    {
        if (MainWinClass->objectName().isEmpty())
            MainWinClass->setObjectName("MainWinClass");
        MainWinClass->resize(493, 308);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/qcloud-client.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWinClass->setWindowIcon(icon);
        act_add_backups = new QAction(MainWinClass);
        act_add_backups->setObjectName("act_add_backups");
        act_add_backups->setMenuRole(QAction::NoRole);
        centralWidget = new QWidget(MainWinClass);
        centralWidget->setObjectName("centralWidget");
        centralWidget->setMinimumSize(QSize(0, 0));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_2 = new QVBoxLayout(tab);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        edit_user_name = new QLineEdit(groupBox);
        edit_user_name->setObjectName("edit_user_name");
        edit_user_name->setMinimumSize(QSize(150, 0));
        edit_user_name->setReadOnly(true);

        gridLayout->addWidget(edit_user_name, 0, 1, 1, 1);

        edit_password = new QLineEdit(groupBox);
        edit_password->setObjectName("edit_password");
        edit_password->setMinimumSize(QSize(150, 0));
        edit_password->setEchoMode(QLineEdit::Password);
        edit_password->setReadOnly(true);

        gridLayout->addWidget(edit_password, 1, 1, 1, 1);

        btn_view_pwd = new QToolButton(groupBox);
        btn_view_pwd->setObjectName("btn_view_pwd");
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pictures/close_eyes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_view_pwd->setIcon(icon1);
        btn_view_pwd->setCheckable(true);

        gridLayout->addWidget(btn_view_pwd, 1, 2, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        btn_logout = new QPushButton(groupBox);
        btn_logout->setObjectName("btn_logout");

        gridLayout->addWidget(btn_logout, 1, 5, 1, 1);

        edit_registry_date = new QDateTimeEdit(groupBox);
        edit_registry_date->setObjectName("edit_registry_date");
        edit_registry_date->setMinimumSize(QSize(150, 0));
        edit_registry_date->setReadOnly(true);
        edit_registry_date->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(edit_registry_date, 0, 4, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(172, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName("gridLayout_2");
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName("label_4");

        gridLayout_2->addWidget(label_4, 0, 0, 1, 1);

        edit_update_date = new QDateTimeEdit(groupBox_2);
        edit_update_date->setObjectName("edit_update_date");
        edit_update_date->setMinimumSize(QSize(150, 0));
        edit_update_date->setReadOnly(true);
        edit_update_date->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout_2->addWidget(edit_update_date, 0, 1, 1, 1);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName("label_6");

        gridLayout_2->addWidget(label_6, 0, 2, 1, 1);

        edit_update_count = new QSpinBox(groupBox_2);
        edit_update_count->setObjectName("edit_update_count");
        edit_update_count->setMinimumSize(QSize(150, 0));
        edit_update_count->setButtonSymbols(QAbstractSpinBox::NoButtons);
        edit_update_count->setMaximum(999999);

        gridLayout_2->addWidget(edit_update_count, 0, 3, 1, 1);

        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 0, 1, 1);

        edit_saves_size = new QSpinBox(groupBox_2);
        edit_saves_size->setObjectName("edit_saves_size");
        edit_saves_size->setMinimumSize(QSize(150, 0));
        edit_saves_size->setButtonSymbols(QAbstractSpinBox::NoButtons);
        edit_saves_size->setMaximum(999999);

        gridLayout_2->addWidget(edit_saves_size, 1, 1, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(201, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 1, 2, 1, 2);


        verticalLayout_2->addWidget(groupBox_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/pictures/saves.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(tab, icon2, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout_3 = new QVBoxLayout(tab_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_upload_saves = new QPushButton(tab_2);
        btn_upload_saves->setObjectName("btn_upload_saves");
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/pictures/upload.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_upload_saves->setIcon(icon3);

        horizontalLayout->addWidget(btn_upload_saves);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_download_saves = new QPushButton(tab_2);
        btn_download_saves->setObjectName("btn_download_saves");
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/pictures/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_download_saves->setIcon(icon4);

        horizontalLayout->addWidget(btn_download_saves);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout);

        edit_log = new QPlainTextEdit(tab_2);
        edit_log->setObjectName("edit_log");
        edit_log->setReadOnly(true);

        verticalLayout_3->addWidget(edit_log);

        tabWidget->addTab(tab_2, icon, QString());

        verticalLayout->addWidget(tabWidget);

        MainWinClass->setCentralWidget(centralWidget);

        retranslateUi(MainWinClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinClass)
    {
        MainWinClass->setWindowTitle(QCoreApplication::translate("MainWinClass", "\344\272\221\345\255\230\346\241\243", nullptr));
        act_add_backups->setText(QCoreApplication::translate("MainWinClass", "\346\267\273\345\212\240\345\244\207\344\273\275", nullptr));
#if QT_CONFIG(tooltip)
        act_add_backups->setToolTip(QCoreApplication::translate("MainWinClass", "\346\267\273\345\212\240\345\244\207\344\273\275", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox->setTitle(QCoreApplication::translate("MainWinClass", "\350\264\246\346\210\267\344\277\241\346\201\257", nullptr));
        edit_password->setText(QString());
        btn_view_pwd->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWinClass", "\346\263\250\345\206\214\346\227\245\346\234\237", nullptr));
        label->setText(QCoreApplication::translate("MainWinClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        btn_logout->setText(QCoreApplication::translate("MainWinClass", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("MainWinClass", "\345\257\206\347\240\201", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWinClass", "\345\255\230\346\241\243\344\277\241\346\201\257", nullptr));
        label_4->setText(QCoreApplication::translate("MainWinClass", "\346\233\264\346\226\260\346\227\245\346\234\237", nullptr));
        label_6->setText(QCoreApplication::translate("MainWinClass", "\346\233\264\346\226\260\346\254\241\346\225\260", nullptr));
        edit_update_count->setSuffix(QCoreApplication::translate("MainWinClass", "\346\254\241", nullptr));
        edit_update_count->setPrefix(QString());
        label_5->setText(QCoreApplication::translate("MainWinClass", "\345\255\230\346\241\243\345\244\247\345\260\217", nullptr));
        edit_saves_size->setSuffix(QCoreApplication::translate("MainWinClass", "kb", nullptr));
        edit_saves_size->setPrefix(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWinClass", "\350\264\246\346\210\267/\345\255\230\346\241\243\344\277\241\346\201\257", nullptr));
        btn_upload_saves->setText(QCoreApplication::translate("MainWinClass", "\344\270\212\344\274\240\345\255\230\346\241\243", nullptr));
        btn_download_saves->setText(QCoreApplication::translate("MainWinClass", "\344\270\213\350\275\275\345\255\230\346\241\243", nullptr));
        edit_log->setPlaceholderText(QCoreApplication::translate("MainWinClass", "\346\225\260\346\215\256\344\274\240\350\276\223\346\227\245\345\277\227", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWinClass", "\345\255\230\346\241\243\346\223\215\344\275\234", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWinClass: public Ui_MainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
