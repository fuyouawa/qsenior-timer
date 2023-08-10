#include "settingsdlg.h"

SettingsDlg::SettingsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SettingsDlg::~SettingsDlg()
{}

void SettingsDlg::MappingToConfig()
{
	AppSettings::AutoCheckUpdate = ui.chk_auto_check_update->isChecked();
	AppSettings::AutoCloseSave = ui.chk_auto_close_save->isChecked();
	AppSettings::AutoSaveLocalInter = ui.edit_auto_save_local_inter->value();
	AppSettings::ErrLevel = ui.edit_err_level->value();
	AppSettings::RunInBg = ui.chk_run_in_bg->isChecked();
	AppSettings::ScanFocusInter = ui.edit_scan_forces_inter->value();
	AppSettings::Startup = ui.chk_startup->isChecked();
	AppSettings::TimerSaveLocal = ui.chk_timer_save_local->isChecked();

	SaveSettings();

	QEasyEventBus::Emit(SettingsChangedEvent());
}

void SettingsDlg::on_btn_apply_clicked()
{
	MappingToConfig();
	QMessageBox::information(this, "提示", "应用成功!");
}


void SettingsDlg::on_btn_ok_clicked()
{
	MappingToConfig();
	accept();
}