#pragma once
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QtEasyLib/QEasyEventSystem>
#include "tools/timerdb.h"
#include "global/utils.h"
#include "global/event_types.h"

class TimerTableModel :
	public QStandardItemModel,
	QEasyEventHandler<SecondUpdateEvent>,
	QEasyEventHandler<FocusWindowChangedEvent>,
	QEasyEventHandler<NeedSaveLocalEvent>
{
	Q_OBJECT

public:
	TimerTableModel(QWidget* parent);
	~TimerTableModel();

	void InsertTimer(const TimerItemBasicInfo& info);
	void InsertTimer(const QString& timer_name, const TimerItemStoreData& data, bool start_imm);
	TimerItemStoreData* GetTimerItemStoreData(int row);
	void SetTimerItemTags(int row, TimerItemTags tags);
	TimerItemTags GetTimerItemTags(int row);
	void SaveTimers();
	QString AutoFormatSecondInData(const TimerItemStoreData& data);

private:
	void OnEvent(const SecondUpdateEvent& event) override;
	void OnEvent(const FocusWindowChangedEvent& event) override;
	void OnEvent(const NeedSaveLocalEvent& event) override;

private:
	void UpdateTimerCount(int row);
	void InitTimers();
	QJsonDocument dbconfig_jsondoc_;
	TimerDb timer_db_;

signals:
	void newTimerAppended();
};