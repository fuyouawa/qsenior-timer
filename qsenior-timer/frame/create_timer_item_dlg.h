#pragma once
#include <qdialog.h>
#include <qmessagebox.h>
#include "ui_create_timer_item_dlg.h"
#include "global/config.h"

class CreateTimerItemDlg : public QDialog
{
	Q_OBJECT

public:
	CreateTimerItemDlg(QWidget* parent);
	~CreateTimerItemDlg();

	TimerItemInfo GetInfo();

private:
	Ui::CreateTimerItemDlg ui;

private slots:
	void on_btn_ok_clicked();
};