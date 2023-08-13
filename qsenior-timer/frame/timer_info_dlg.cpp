#include "timer_info_dlg.h"

TimerInfoDlg::TimerInfoDlg(QWidget* parent, const TimerItemStoreData& data, const QString& timer_name)
	: QDialog(parent)
{
	ui.setupUi(this);
	ui.edit_timer_name->setText(timer_name);
	ui.edit_proc_name->setText(data.proc_name);
	ui.edit_tags->setText(data.tags);
	ui.table_history->setColumnWidth(0, 100);
}

TimerInfoDlg::~TimerInfoDlg()
{
}

void TimerInfoDlg::ClearHistroyItems()
{
	for (size_t i = 0; i < ui.table_history->rowCount(); i++)
		ui.table_history->removeRow(0);
}

void TimerInfoDlg::AppendDayTimer(const TimerItemStoreData::DayTimer& timer)
{
	auto row = ui.table_history->rowCount();
	ui.table_history->setRowCount(row + 1);

	auto item1 = new QTableWidgetItem(QDate::fromJulianDay(timer.julian_date).toString(Qt::ISODate));
	item1->setTextAlignment(Qt::AlignCenter);
	item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

	auto item2 = new QTableWidgetItem(FormatSeconds(timer.day_time));
	item2->setTextAlignment(Qt::AlignCenter);
	item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

	auto item3 = new QTableWidgetItem(FormatSeconds(timer.max_continuous));
	item3->setTextAlignment(Qt::AlignCenter);
	item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

	auto item4 = new QTableWidgetItem(FormatSeconds(timer.last_continuous));
	item4->setTextAlignment(Qt::AlignCenter);
	item4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

	ui.table_history->setItem(row, 0, item1);
	ui.table_history->setItem(row, 1, item2);
	ui.table_history->setItem(row, 2, item3);
	ui.table_history->setItem(row, 3, item4);
}

void TimerInfoDlg::on_btn_load_history_clicked()
{
	if (auto opt = TimerDb::Instance->GetTimerHistory(ui.edit_timer_name->text()); opt.IsSome()) {
		ClearHistroyItems();
		auto history = opt.SomeVal();
		for (auto& item : history) {
			AppendDayTimer(item);
		}
	}
	else {
		ShowErrorMsg(TimerDb::Instance->LastError(), 1, this);
	}
}