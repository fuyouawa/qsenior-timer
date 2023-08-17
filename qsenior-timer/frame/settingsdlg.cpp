#include "settingsdlg.h"

SettingsDlg::SettingsDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.chk_auto_check_update->setChecked(AppSettings::AutoCheckUpdate);
	ui.chk_auto_close_save->setChecked(AppSettings::AutoCloseSave);
	ui.edit_auto_save_local_inter->setValue(AppSettings::SaveLocalInter);
	ui.edit_err_level->setValue(AppSettings::ErrLevel);
	ui.chk_run_in_tray->setChecked(AppSettings::RunInTray);
	ui.edit_scan_forces_inter->setValue(AppSettings::ScanFocusInter);
	ui.chk_startup->setChecked(AppSettings::Startup);
	ui.chk_auto_save_local->setChecked(AppSettings::AutoTimerSaveLocal);
	ui.chk_scan_hang_up->setChecked(AppSettings::ScanHangup);
	ui.edit_hang_up_judge->setValue(AppSettings::HangupJudgeTime);
}

SettingsDlg::~SettingsDlg()
{}

void SettingsDlg::MappingToConfig()
{
	AppSettings::AutoCheckUpdate = ui.chk_auto_check_update->isChecked();
	AppSettings::AutoCloseSave = ui.chk_auto_close_save->isChecked();
	AppSettings::SaveLocalInter = ui.edit_auto_save_local_inter->value();
	AppSettings::ErrLevel = ui.edit_err_level->value();
	AppSettings::RunInTray = ui.chk_run_in_tray->isChecked();
	AppSettings::ScanFocusInter = ui.edit_scan_forces_inter->value();
	AppSettings::Startup = ui.chk_startup->isChecked();
	AppSettings::AutoTimerSaveLocal = ui.chk_auto_save_local->isChecked();
	AppSettings::ScanHangup = ui.chk_scan_hang_up->isChecked();
	AppSettings::HangupJudgeTime = ui.edit_hang_up_judge->value();

	SaveSettings();

	qteasylib::EventBus::Emit(SettingsChangedEvent());
}

void SettingsDlg::on_btn_apply_clicked()
{
	MappingToConfig();
	AutoRegistryStartup();
	QMessageBox::information(this, "提示", "应用成功!");
}


void SettingsDlg::on_btn_ok_clicked()
{
	MappingToConfig();
	AutoRegistryStartup();
	accept();
}