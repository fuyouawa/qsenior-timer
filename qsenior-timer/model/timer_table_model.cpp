#include "timer_table_model.h"

TimerTableModel::TimerTableModel(QWidget* parent): QStandardItemModel(parent)
{
	setHorizontalHeaderLabels(kTimerTableHorizontalHeaderLabels);
}

TimerTableModel::~TimerTableModel()
{
}

void TimerTableModel::InsertTimer(const TimerItemInfo& info)
{
    for (size_t i = 0; i < rowCount(); i++) {
        if (item(i, kTimerItemColomnTimerName)->text() == info.timer_name) {
            QMessageBox::warning((QWidget*)parent(), "错误", "添加计时器失败!\n原因: 已有相同名称的计时器!");
            return;
        }
    }
    auto item1 = new QStandardItem(info.timer_name);
    item1->setData(info.proc_name, Qt::UserRole);
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item2 = new QStandardItem("0天00时00分00秒");
    item2->setData(
        (info.can_del ? kFlagTimerItemCanDel : 0) |
        (info.can_pause ? kFlagTimerItemCanPause : 0) |
        (info.start_imm ? kFlagTimerItemStartImm : 0)
        , Qt::UserRole);
    item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item3 = new QStandardItem("初始化");
    item3->setData(kTimerItemStatusInit, Qt::UserRole);
    item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item4 = new QStandardItem();
    item4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    appendRow({ item1, item2, item3, item4 });

    emit onAppended();
}

void TimerTableModel::SetTimerStatus(int row, TimerItemStatus status)
{
    item(row, kTimerItemColomnStatus)->setData(status, Qt::UserRole);
}

void TimerTableModel::OnEvent(const SecondUpdateEvent& event)
{

}

void TimerTableModel::OnEvent(const FocusWindowChangedEvent& event)
{
    for (size_t i = 0; i < rowCount(); i++) {
        auto proc = item(i, kTimerItemDataColomnProcessName)->data(Qt::UserRole).toString();
        auto status_item = item(i, kTimerItemColomnStatus);
        if (status_item->data(Qt::UserRole) != kTimerItemStatusPaused) {
            if (proc == event.cur_proc) {
                status_item->setData(kTimerItemStatusRunning, Qt::UserRole);
            }
            else if (proc == event.prev_proc) {
                status_item->setData(kTimerItemStatusStanding, Qt::UserRole);
            }
        }
    }
}
