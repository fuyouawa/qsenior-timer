#pragma once

#include <QDialog>
#include "ui_settingsdlg.h"

class SettingsDlg  : public QDialog
{
	Q_OBJECT

public:
	SettingsDlg(QWidget *parent);
	~SettingsDlg();

private:
	Ui::SettingsDlg ui;
};
