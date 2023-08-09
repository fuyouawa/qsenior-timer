#include "timer_table_model.h"

TimerTableModel::TimerTableModel(QWidget* parent): QStandardItemModel(parent)
{
	setHorizontalHeaderLabels(kTimerTableHorizontalHeaderLabels);
    dbconfig_jsondoc_ = ReadDbConfigFile(parent);

    InitItems();
}

TimerTableModel::~TimerTableModel()
{
}

void TimerTableModel::InsertTimer(const TimerItemInfo& info)
{
    for (size_t i = 0; i < rowCount(); i++) {
        if (item(i, kTimerTableColomnTimerName)->text() == info.timer_name) {
            QMessageBox::warning((QWidget*)parent(), "错误", "添加计时器失败!\n原因: 已有相同名称的计时器!");
            return;
        }
    }
    auto item1 = new QStandardItem(info.timer_name);
    item1->setData((qulonglong)(new TimerItemInfo(info)), Qt::UserRole);
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item2 = new QStandardItem("0天00时00分00秒");
    item2->setData(kTimerItemTagIsPreviousRunning, Qt::UserRole);
    item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item3 = new QStandardItem("初始化");
    item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item4 = new QStandardItem();
    item4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    AppendToJsonDoc(info);
    appendRow({ item1, item2, item3, item4 });

    auto a = GetTimerItemInfo(0);

    emit newTimerAppended();
}

void TimerTableModel::SetTimerStatus(int row, TimerItemStatus status)
{
    item(row, kTimerTableColomnStatus)->setData(status, Qt::UserRole);
}

void TimerTableModel::OnEvent(const SecondUpdateEvent& event)
{
    for (size_t i = 0; i < rowCount(); i++) {
        auto info = GetTimerItemInfo(i);
        if (info->status == kTimerItemStatusRunning) {
            if (GetTimerItemTags(i) == kTimerItemTagIsPreviousRunning)
                info->time.continuous = 0;
            ++info->time.total;
            ++info->time.today;
            ++info->time.continuous;
            if (info->time.continuous > info->time.max_continuous)
                info->time.max_continuous = info->time.continuous;
            UpdateTimerCount(i);
        }
    }
}

void TimerTableModel::OnEvent(const FocusWindowChangedEvent& event)
{
    for (size_t i = 0; i < rowCount(); i++) {
        auto info = GetTimerItemInfo(i);
        if (info->status != kTimerItemStatusPaused) {
            if (info->proc_name == event.cur_proc) {
                info->status = kTimerItemStatusRunning;
            }
            else if (info->proc_name == event.prev_proc) {
                info->status = kTimerItemStatusStanding;
                SetTimerItemTags(i, kTimerItemTagIsPreviousRunning);
            }
        }
    }
}

void TimerTableModel::InitItems()
{
    for (auto val : dbconfig_jsondoc_.array()) {
        InsertTimer(JsonToTimerItemInfo(val.toObject()));
    }
}

void TimerTableModel::AppendToJsonDoc(const TimerItemInfo& info)
{
    if (!dbconfig_jsondoc_.isArray() || dbconfig_jsondoc_.isEmpty()) {
        dbconfig_jsondoc_.setArray(QJsonArray());
    }
    auto arr = dbconfig_jsondoc_.array();
    if (FindTimerItemInfoInJsonByTimerName(arr, info.proc_name).IsSome()) {
        return;
    }
    arr.append(TimerItemInfoToJson(info));
    dbconfig_jsondoc_.setArray(arr);
}

TimerItemInfo* TimerTableModel::GetTimerItemInfo(int row)
{
    return (TimerItemInfo*)item(row, kTimerItemDataColumnInfo)->data(Qt::UserRole).toULongLong();
}

TimerItemTags TimerTableModel::GetTimerItemTags(int row)
{
    return (TimerItemTags)item(row, kTimerItemDataColumnTags)->data(Qt::UserRole).toInt();
}

void TimerTableModel::SetTimerItemTags(int row, TimerItemTags tags)
{
    item(row, kTimerItemDataColumnTags)->setData((int)tags, Qt::UserRole);
}

void TimerTableModel::UpdateTimerCount(int row)
{
    auto info = GetTimerItemInfo(row);
    item(row, kTimerTableColomnTimeCounter)->setText(FormatSeconds(info->time.total));
}
