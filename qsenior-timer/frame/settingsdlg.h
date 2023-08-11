#pragma once

#include <QDialog>
#include <QMessageBox>
#include <QtEasyLib/QEasyEventSystem>

#include "global/config.h"
#include "global/event_types.h"
#include "ui_settingsdlg.h"
#include "global/utils.h"

class SettingsDlg  : public QDialog
{
	Q_OBJECT

public:
	SettingsDlg(QWidget *parent);
	~SettingsDlg();

private slots:
	void on_btn_apply_clicked();
	void on_btn_ok_clicked();

private:
	void MappingToConfig();

	Ui::SettingsDlgClass ui;
};
