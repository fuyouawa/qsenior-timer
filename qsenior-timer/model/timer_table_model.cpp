#include "timer_table_model.h"

TimerTableModel::TimerTableModel(QWidget* parent):
    QStandardItemModel(parent),
    timer_db_(parent)
{
	setHorizontalHeaderLabels(kTextTimerTableHorizontalHeader);
    timer_db_.Open();
    InitTimers();
}

TimerTableModel::~TimerTableModel()
{
    if (AppSettings::AutoCloseSave) {
        SaveTimers();
    }
    timer_db_.Close();
}

void TimerTableModel::InsertTimer(const TimerItemBasicInfo& info)
{
    InsertTimer(info.proc_name, TimerItemBasicInfoToStoreData(info), info.start_imm);
}

void TimerTableModel::InsertTimer(const QString& timer_name, const TimerItemStoreData& data, bool start_imm)
{
    for (size_t i = 0; i < rowCount(); i++) {
        if (item(i, kTimerTableColomnTimerName)->text() == timer_name) {
            QMessageBox::warning((QWidget*)parent(), "错误", "添加计时器失败!\n原因: 已有相同名称的计时器!");
            return;
        }
    }
    auto item1 = new QStandardItem(timer_name);
    auto store = new TimerItemStoreData(data);
    store->status = start_imm ? kTimerItemStatusStanding : kTimerItemStatusPaused;
    item1->setData((qulonglong)store, Qt::UserRole);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item2 = new QStandardItem("0天00时00分00秒");
    item2->setData(kTimerItemTagNone, Qt::UserRole);
    item2->setTextAlignment(Qt::AlignCenter);
    item2->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item3 = new QStandardItem(data.tags);
    item3->setTextAlignment(Qt::AlignCenter);
    item3->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item4 = new QStandardItem("初始化");
    item4->setTextAlignment(Qt::AlignCenter);
    item4->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item5 = new QStandardItem();
    item5->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    appendRow({ item1, item2, item3, item4, item5 });

    emit newTimerAppended();
}

TimerItemStoreData* TimerTableModel::GetTimerItemStoreData(int row)
{
    return (TimerItemStoreData*)item(row, kTimerItemDataColumnStoreData)->data(Qt::UserRole).toULongLong();
}

void TimerTableModel::SetTimerItemTags(int row, TimerItemTags tags)
{
    item(row, kTimerItemDataColumnTags)->setData((int)tags, Qt::UserRole);
}

TimerItemTags TimerTableModel::GetTimerItemTags(int row)
{
    return (TimerItemTags)item(row, kTimerItemDataColumnTags)->data(Qt::UserRole).toInt();
}

void TimerTableModel::SaveTimers()
{
    QMap<QString, TimerItemStoreData> total;
    for (size_t i = 0; i < rowCount(); i++) {
        auto data = *GetTimerItemStoreData(i);
        auto name = item(i, kTimerTableColomnTimerName)->text();
        total[name] = std::move(data);
    }
    timer_db_.SaveDataList(total);
}

void TimerTableModel::OnEvent(const SecondUpdateEvent& event)
{
    for (size_t i = 0; i < rowCount(); i++) {
        auto data = GetTimerItemStoreData(i);
        if (data->status == kTimerItemStatusRunning) {
            if (GetTimerItemTags(i) == kTimerItemTagIsPreviousRunning) {
                data->today.last_continuous = 0;
                SetTimerItemTags(i, kTimerItemTagNone);
            }
            ++data->total_time;
            ++data->today.day_time;
            ++data->today.last_continuous;
            if (data->today.last_continuous > data->today.max_continuous)
                data->today.max_continuous = data->today.last_continuous;
            UpdateTimerCount(i);
        }
    }
}

void TimerTableModel::OnEvent(const FocusWindowChangedEvent& event)
{
    for (size_t i = 0; i < rowCount(); i++) {
        auto data = GetTimerItemStoreData(i);
        if (data->status != kTimerItemStatusPaused) {
            if (data->proc_name == event.cur_proc) {
                data->status = kTimerItemStatusRunning;
            }
            else if (data->proc_name == event.prev_proc) {
                data->status = kTimerItemStatusStanding;
                SetTimerItemTags(i, kTimerItemTagIsPreviousRunning);
            }
            item(i, kTimerTableColomnStatus)->setText(kTextTimerItemStatus[data->status]);
        }
    }
}

void TimerTableModel::OnEvent(const NeedSaveLocalEvent& event)
{
    SaveTimers();
}

void TimerTableModel::UpdateTimerCount(int row)
{
    auto data = GetTimerItemStoreData(row);
    item(row, kTimerTableColomnTimeCounter)->setText(FormatSeconds(data->total_time));
}

void TimerTableModel::InitTimers()
{
    timer_db_.ForeachData([this](const QString& timer_name, const TimerItemStoreData& data) {
        InsertTimer(timer_name, data, true);
        });
}
