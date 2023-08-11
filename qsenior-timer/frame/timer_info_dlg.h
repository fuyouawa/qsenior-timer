#pragma once

#include <QDialog>
#include "ui_timer_info_dlg.h"
#include "global/utils.h"
#include "tools/timerdb.h"

class TimerInfoDlg : public QDialog
{
	Q_OBJECT

public:
	TimerInfoDlg(QWidget *parent, const TimerItemStoreData& data, const QString& timer_name);
	~TimerInfoDlg();

private:
	void AppendDayTimer(const TimerItemStoreData::DayTimer& timer);
	Ui::TimerInfoDlgClass ui;

private slots:
	void on_btn_load_history_clicked();
};
