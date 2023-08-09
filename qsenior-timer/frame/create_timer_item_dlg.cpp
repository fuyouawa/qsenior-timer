#include "create_timer_item_dlg.h"

CreateTimerItemDlg::CreateTimerItemDlg(QWidget* parent): QDialog(parent)
{
	ui.setupUi(this);
}

CreateTimerItemDlg::~CreateTimerItemDlg()
{
}

TimerItemInfo CreateTimerItemDlg::GetInfo()
{
	TimerItemInfo info;
	info.timer_name = ui.edit_timer_name->text().trimmed();
	info.proc_name = ui.edit_proc_name->text().trimmed();
	info.can_del = ui.chk_can_del->isChecked();
	info.can_pause = ui.chk_can_pause->isChecked();
	info.can_edit = ui.chk_can_edit->isChecked();
	info.start_imm = ui.chk_start_imm->isChecked();
	info.status = kTimerItemStatusInit;
	info.time = { 0, 0, 0, 0};
	return info;
}

void CreateTimerItemDlg::on_btn_aim_process_clicked()
{
}

void CreateTimerItemDlg::on_btn_ok_clicked()
{
	if (ui.edit_timer_name->text().isEmpty() || ui.edit_proc_name->text().isEmpty()) {
		QMessageBox::warning(this, "警告", "您还有项没填写!");
	}
	else if (QMessageBox::question(this, "询问", "你确定要创建吗, 部分选项一经创建无法修改!") == QMessageBox::Yes) {
		accept();
	}
}