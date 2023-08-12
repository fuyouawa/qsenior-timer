#include "timer_table_model.h"

TimerTableModel::TimerTableModel(QWidget* parent):
    QStandardItemModel(parent),
    msg_parent_(parent)
{
	setHorizontalHeaderLabels(kTextTimerTableHorizontalHeader);
    InitTimers();
}

TimerTableModel::~TimerTableModel()
{
    if (AppSettings::AutoCloseSave) {
        SaveTimers();
    }
}

void TimerTableModel::InsertTimer(const QString& timer_name, const TimerItemStoreData& data)
{
    for (size_t i = 0; i < rowCount(); i++) {
        if (GetTimerName(i) == timer_name) {
            QMessageBox::warning(msg_parent_, "错误", "添加计时器失败!\n原因: 已有相同名称的计时器!");
            return;
        }
    }
    auto item1 = new QStandardItem(timer_name);
    auto store = new TimerItemStoreData(data);
    item1->setData((qulonglong)store, Qt::UserRole);
    item1->setTextAlignment(Qt::AlignCenter);
    item1->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsUserCheckable);

    auto item2 = new QStandardItem(AutoFormatSecondInData(data));
    item2->setData(kFlagIsPreviousRunning, Qt::UserRole);
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
    return (TimerItemStoreData*)item(row, kDataStore)->data(Qt::UserRole).toULongLong();
}

void TimerTableModel::SetTimerItemFlags(int row, TimerItemFlags tags)
{
    item(row, kDataTags)->setData((int)tags, Qt::UserRole);
}

TimerItemFlags TimerTableModel::GetTimerItemFlags(int row)
{
    return (TimerItemFlags)item(row, kDataTags)->data(Qt::UserRole).toInt();
}

void TimerTableModel::SaveTimers()
{
    QMap<QString, TimerItemStoreData> total;
    for (size_t i = 0; i < rowCount(); i++) {
        if (!TimerDb::Instance->SaveData(GetTimerName(i), *GetTimerItemStoreData(i))) {
            ShowErrorMsg(TimerDb::Instance->LastError(), 1, msg_parent_);
            break;
        }
    }
}

QString TimerTableModel::AutoFormatSecondInData(const TimerItemStoreData& data)
{
    switch (ViewSettings::TimeCounterModel)
    {
    case kViewModelTotalTime:
        return FormatSeconds(data.total_time);
    case kViewModelTodayTime:
        return FormatSeconds(data.today.day_time);
    default:
        return FormatSeconds(data.today.last_continuous);
    }
}

QString TimerTableModel::GetTimerName(int row)
{
    return item(row, kColumnTimerName)->text();
}

QString TimerTableModel::GetTags(int row)
{
    return item(row, kColumnTags)->text();
}

void TimerTableModel::OnEvent(const SecondUpdateEvent& event)
{
    cur_run_items_row_.clear();
    for (size_t i = 0; i < rowCount(); i++) {
        auto data = GetTimerItemStoreData(i);

        if (data->status != kStatusPaused && data->status != kStatusHangup) {
            if (data->proc_name == cur_proc_name_) {
                data->status = kStatusRunning;
            }
            else if (data->proc_name == prev_proc_name_) {
                data->status = kStatusStanding;
                SetTimerItemFlags(i, kFlagIsPreviousRunning);
            }
        }
        item(i, kColumnStatus)->setText(kTextTimerItemStatus[data->status]);

        if (data->status == kStatusRunning) {
            if (GetTimerItemFlags(i) == kFlagIsPreviousRunning) {
                data->today.last_continuous = 0;
                SetTimerItemFlags(i, kFlagNone);
            }
            ++data->total_time;
            ++data->today.day_time;
            ++data->today.last_continuous;
            if (data->today.last_continuous > data->today.max_continuous)
                data->today.max_continuous = data->today.last_continuous;
            cur_run_items_row_.append(i);
            UpdateTimerCount(i);
        }
    }
}

void TimerTableModel::OnEvent(const FocusWindowChangedEvent& event)
{
    cur_proc_name_ = event.cur_proc;
    prev_proc_name_ = event.prev_proc;
}

void TimerTableModel::OnEvent(const NeedSaveLocalEvent& event)
{
    SaveTimers();
}

void TimerTableModel::OnEvent(const CursorHangedupEvent& event)
{
    for (auto row : cur_run_items_row_) {
        GetTimerItemStoreData(row)->status = kStatusHangup;
    }
    cur_hangingup_items_row_ = std::move(cur_run_items_row_);
}

void TimerTableModel::OnEvent(const CursorUnHangedupEvent& event)
{
    for (auto row : cur_hangingup_items_row_) {
        GetTimerItemStoreData(row)->status = kStatusStanding;
    }
    cur_hangingup_items_row_.clear();
}

void TimerTableModel::UpdateTimerCount(int row)
{
    item(row, kColumnTimeCounter)->setText(AutoFormatSecondInData(*GetTimerItemStoreData(row)));
}

void TimerTableModel::InitTimers()
{
    auto res = TimerDb::Instance->ForeachData([this](const QString& timer_name, const TimerItemStoreData& data) {
        InsertTimer(timer_name, data);
        });

    if (!res)
        ShowErrorMsg(TimerDb::Instance->LastError(), 1, msg_parent_);
}
