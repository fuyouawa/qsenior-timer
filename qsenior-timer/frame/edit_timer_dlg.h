#pragma once

#include <QDialog>
#include <QMessageBox>
#include "ui_edit_timer_dlg.h"

class EditTimerDlg : public QDialog
{
	Q_OBJECT

public:
	EditTimerDlg(QWidget *parent, const QString& init_timer_name, const QString& init_tags);
	~EditTimerDlg();

	std::tuple<QString, QString> GetEdit();

private:
	Ui::EditTimerDlgClass ui;

private slots:
	void on_btn_ok_clicked();
};
