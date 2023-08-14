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
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWinClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_5;
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
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btn_upload_saves;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btn_download_saves;
    QSpacerItem *horizontalSpacer_4;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QPlainTextEdit *edit_data_log;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_4;
    QDoubleSpinBox *edit_cur_saves_size;
    QLabel *label_5;
    QDateTimeEdit *edit_last_upload_date;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btn_load_saves_histroy;
    QSpacerItem *horizontalSpacer_6;
    QTableWidget *table_saves_histroy;

    void setupUi(QMainWindow *MainWinClass)
    {
        if (MainWinClass->objectName().isEmpty())
            MainWinClass->setObjectName("MainWinClass");
        MainWinClass->resize(580, 485);
        centralWidget = new QWidget(MainWinClass);
        centralWidget->setObjectName("centralWidget");
        verticalLayout_5 = new QVBoxLayout(centralWidget);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName("groupBox");
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName("gridLayout");
        edit_user_name = new QLineEdit(groupBox);
        edit_user_name->setObjectName("edit_user_name");
        edit_user_name->setReadOnly(true);

        gridLayout->addWidget(edit_user_name, 0, 1, 1, 1);

        edit_password = new QLineEdit(groupBox);
        edit_password->setObjectName("edit_password");
        edit_password->setReadOnly(true);

        gridLayout->addWidget(edit_password, 1, 1, 1, 1);

        btn_view_pwd = new QToolButton(groupBox);
        btn_view_pwd->setObjectName("btn_view_pwd");
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/close_eyes.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_view_pwd->setIcon(icon);

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
        edit_registry_date->setReadOnly(true);
        edit_registry_date->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(edit_registry_date, 0, 4, 1, 2);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(172, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 1, 4, 1, 1);


        verticalLayout_5->addWidget(groupBox);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        tab = new QWidget();
        tab->setObjectName("tab");
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btn_upload_saves = new QPushButton(tab);
        btn_upload_saves->setObjectName("btn_upload_saves");

        horizontalLayout->addWidget(btn_upload_saves);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btn_download_saves = new QPushButton(tab);
        btn_download_saves->setObjectName("btn_download_saves");

        horizontalLayout->addWidget(btn_download_saves);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout);

        groupBox_2 = new QGroupBox(tab);
        groupBox_2->setObjectName("groupBox_2");
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        edit_data_log = new QPlainTextEdit(groupBox_2);
        edit_data_log->setObjectName("edit_data_log");
        edit_data_log->setReadOnly(true);

        verticalLayout_2->addWidget(edit_data_log);


        verticalLayout_3->addWidget(groupBox_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName("tab_2");
        verticalLayout = new QVBoxLayout(tab_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_4 = new QLabel(tab_2);
        label_4->setObjectName("label_4");

        horizontalLayout_3->addWidget(label_4);

        edit_cur_saves_size = new QDoubleSpinBox(tab_2);
        edit_cur_saves_size->setObjectName("edit_cur_saves_size");
        edit_cur_saves_size->setReadOnly(true);
        edit_cur_saves_size->setButtonSymbols(QAbstractSpinBox::NoButtons);
        edit_cur_saves_size->setDecimals(2);
        edit_cur_saves_size->setMaximum(9999.989999999999782);

        horizontalLayout_3->addWidget(edit_cur_saves_size);

        label_5 = new QLabel(tab_2);
        label_5->setObjectName("label_5");

        horizontalLayout_3->addWidget(label_5);

        edit_last_upload_date = new QDateTimeEdit(tab_2);
        edit_last_upload_date->setObjectName("edit_last_upload_date");
        edit_last_upload_date->setReadOnly(true);
        edit_last_upload_date->setButtonSymbols(QAbstractSpinBox::NoButtons);

        horizontalLayout_3->addWidget(edit_last_upload_date);


        verticalLayout->addLayout(horizontalLayout_3);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName("groupBox_3");
        verticalLayout_4 = new QVBoxLayout(groupBox_3);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btn_load_saves_histroy = new QPushButton(groupBox_3);
        btn_load_saves_histroy->setObjectName("btn_load_saves_histroy");

        horizontalLayout_2->addWidget(btn_load_saves_histroy);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);


        verticalLayout_4->addLayout(horizontalLayout_2);

        table_saves_histroy = new QTableWidget(groupBox_3);
        if (table_saves_histroy->columnCount() < 2)
            table_saves_histroy->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        table_saves_histroy->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        table_saves_histroy->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        table_saves_histroy->setObjectName("table_saves_histroy");
        table_saves_histroy->setEditTriggers(QAbstractItemView::NoEditTriggers);
        table_saves_histroy->horizontalHeader()->setDefaultSectionSize(150);
        table_saves_histroy->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_4->addWidget(table_saves_histroy);


        verticalLayout->addWidget(groupBox_3);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_5->addWidget(tabWidget);

        MainWinClass->setCentralWidget(centralWidget);

        retranslateUi(MainWinClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWinClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWinClass)
    {
        MainWinClass->setWindowTitle(QCoreApplication::translate("MainWinClass", "\344\272\221\345\255\230\346\241\243", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWinClass", "\350\264\246\346\210\267\344\277\241\346\201\257", nullptr));
        edit_password->setText(QString());
        btn_view_pwd->setText(QString());
        label_3->setText(QCoreApplication::translate("MainWinClass", "\346\263\250\345\206\214\346\227\245\346\234\237", nullptr));
        label->setText(QCoreApplication::translate("MainWinClass", "\347\224\250\346\210\267\345\220\215", nullptr));
        btn_logout->setText(QCoreApplication::translate("MainWinClass", "\351\200\200\345\207\272\347\231\273\345\275\225", nullptr));
        label_2->setText(QCoreApplication::translate("MainWinClass", "\345\257\206\347\240\201", nullptr));
        btn_upload_saves->setText(QCoreApplication::translate("MainWinClass", "\344\270\212\344\274\240\345\255\230\346\241\243", nullptr));
        btn_download_saves->setText(QCoreApplication::translate("MainWinClass", "\344\270\213\350\275\275\345\255\230\346\241\243", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWinClass", "\346\225\260\346\215\256\344\274\240\350\276\223\346\227\245\345\277\227", nullptr));
        edit_data_log->setPlaceholderText(QCoreApplication::translate("MainWinClass", "\346\232\202\346\227\240\346\227\245\345\277\227\344\277\241\346\201\257", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainWinClass", "\345\255\230\346\241\243\346\223\215\344\275\234", nullptr));
        label_4->setText(QCoreApplication::translate("MainWinClass", "\345\275\223\345\211\215\346\234\215\345\212\241\345\231\250\344\270\212\347\232\204\345\255\230\346\241\243\345\244\247\345\260\217", nullptr));
        edit_cur_saves_size->setSuffix(QCoreApplication::translate("MainWinClass", "MB", nullptr));
        label_5->setText(QCoreApplication::translate("MainWinClass", "\344\270\212\344\270\200\346\254\241\344\270\212\344\274\240\346\227\245\346\234\237", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWinClass", "\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        btn_load_saves_histroy->setText(QCoreApplication::translate("MainWinClass", "\345\212\240\350\275\275\345\216\206\345\217\262\350\256\260\345\275\225", nullptr));
        QTableWidgetItem *___qtablewidgetitem = table_saves_histroy->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWinClass", "\344\270\212\344\274\240\346\227\245\346\234\237", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = table_saves_histroy->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWinClass", "\344\270\212\344\274\240\347\232\204\345\255\230\346\241\243\345\244\247\345\260\217", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWinClass", "\345\255\230\346\241\243\344\277\241\346\201\257", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWinClass: public Ui_MainWinClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIN_H
