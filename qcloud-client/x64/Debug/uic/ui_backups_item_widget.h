/********************************************************************************
** Form generated from reading UI file 'backups_item_widget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BACKUPS_ITEM_WIDGET_H
#define UI_BACKUPS_ITEM_WIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BackupsItemWidgetClass
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QPushButton *pushButton;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QDoubleSpinBox *doubleSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_2;
    QPushButton *pushButton_2;
    QLineEdit *lineEdit;

    void setupUi(QWidget *BackupsItemWidgetClass)
    {
        if (BackupsItemWidgetClass->objectName().isEmpty())
            BackupsItemWidgetClass->setObjectName("BackupsItemWidgetClass");
        BackupsItemWidgetClass->setWindowModality(Qt::NonModal);
        BackupsItemWidgetClass->resize(536, 54);
        horizontalLayout = new QHBoxLayout(BackupsItemWidgetClass);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 4);
        label = new QLabel(BackupsItemWidgetClass);
        label->setObjectName("label");
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(45, 45));
        label->setContextMenuPolicy(Qt::NoContextMenu);
        label->setPixmap(QPixmap(QString::fromUtf8(":/pictures/saves.png")));
        label->setScaledContents(true);

        horizontalLayout->addWidget(label);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setVerticalSpacing(0);
        label_4 = new QLabel(BackupsItemWidgetClass);
        label_4->setObjectName("label_4");
        label_4->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(label_4, 0, 2, 1, 1);

        pushButton = new QPushButton(BackupsItemWidgetClass);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(100, 0));
        pushButton->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/pictures/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);

        gridLayout->addWidget(pushButton, 0, 4, 1, 1);

        label_3 = new QLabel(BackupsItemWidgetClass);
        label_3->setObjectName("label_3");
        label_3->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(label_3, 1, 0, 1, 1);

        dateTimeEdit = new QDateTimeEdit(BackupsItemWidgetClass);
        dateTimeEdit->setObjectName("dateTimeEdit");
        dateTimeEdit->setContextMenuPolicy(Qt::NoContextMenu);
        dateTimeEdit->setReadOnly(true);
        dateTimeEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);

        gridLayout->addWidget(dateTimeEdit, 1, 1, 1, 1);

        doubleSpinBox = new QDoubleSpinBox(BackupsItemWidgetClass);
        doubleSpinBox->setObjectName("doubleSpinBox");
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(doubleSpinBox->sizePolicy().hasHeightForWidth());
        doubleSpinBox->setSizePolicy(sizePolicy1);
        doubleSpinBox->setMinimumSize(QSize(80, 0));
        doubleSpinBox->setContextMenuPolicy(Qt::NoContextMenu);
        doubleSpinBox->setReadOnly(true);
        doubleSpinBox->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox->setAccelerated(false);
        doubleSpinBox->setMaximum(99.989999999999995);
        doubleSpinBox->setValue(0.000000000000000);

        gridLayout->addWidget(doubleSpinBox, 0, 3, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(107, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 2);

        label_2 = new QLabel(BackupsItemWidgetClass);
        label_2->setObjectName("label_2");
        label_2->setContextMenuPolicy(Qt::NoContextMenu);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(BackupsItemWidgetClass);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(100, 0));
        pushButton_2->setContextMenuPolicy(Qt::NoContextMenu);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/pictures/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);

        gridLayout->addWidget(pushButton_2, 1, 4, 1, 1);

        lineEdit = new QLineEdit(BackupsItemWidgetClass);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setContextMenuPolicy(Qt::NoContextMenu);
        lineEdit->setReadOnly(true);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);


        retranslateUi(BackupsItemWidgetClass);

        QMetaObject::connectSlotsByName(BackupsItemWidgetClass);
    } // setupUi

    void retranslateUi(QWidget *BackupsItemWidgetClass)
    {
        BackupsItemWidgetClass->setWindowTitle(QString());
        label->setText(QString());
        label_4->setText(QCoreApplication::translate("BackupsItemWidgetClass", "\345\255\230\346\241\243\345\244\247\345\260\217", nullptr));
        pushButton->setText(QCoreApplication::translate("BackupsItemWidgetClass", "\344\270\213\350\275\275\345\255\230\346\241\243", nullptr));
        label_3->setText(QCoreApplication::translate("BackupsItemWidgetClass", "  \345\210\233\345\273\272\346\227\245\346\234\237", nullptr));
        doubleSpinBox->setSuffix(QCoreApplication::translate("BackupsItemWidgetClass", "MB", nullptr));
        label_2->setText(QCoreApplication::translate("BackupsItemWidgetClass", "  \345\255\230\346\241\243\345\220\215", nullptr));
        pushButton_2->setText(QCoreApplication::translate("BackupsItemWidgetClass", "\345\210\240\351\231\244\345\255\230\346\241\243", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BackupsItemWidgetClass: public Ui_BackupsItemWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BACKUPS_ITEM_WIDGET_H
