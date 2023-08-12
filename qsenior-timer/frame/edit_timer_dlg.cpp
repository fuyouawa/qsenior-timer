#include "edit_timer_dlg.h"

EditTimerDlg::EditTimerDlg(QWidget *parent, const QString& init_timer_name, const QString& init_tags)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.edit_timer_name->setText(init_timer_name);
	ui.edit_tags->setText(init_tags);
}

EditTimerDlg::~EditTimerDlg()
{}

std::tuple<QString, QString> EditTimerDlg::GetEdit()
{
	return std::tuple(ui.edit_timer_name->text(), ui.edit_tags->text());
}

void EditTimerDlg::on_btn_ok_clicked()
{
	if (ui.edit_tags->text().isEmpty() || ui.edit_timer_name->text().isEmpty()) {
		QMessageBox::warning(this, "警告", "您还有项没填写!");
	}
	else if (QMessageBox::question(this, "询问", "你确定要应用更改吗?\n应用此更改会立即存入缓存, 无法撤回!") == QMessageBox::Yes) {
		accept();
	}
}