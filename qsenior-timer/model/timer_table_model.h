#pragma once
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include "tools/timerdb.h"
#include "global/utils.h"
#include "global/event_types.h"

class TimerTableModel :
	public QStandardItemModel,
	qteasylib::EventHandler<SecondUpdateEvent>,
	qteasylib::EventHandler<FocusWindowChangedEvent>,
	qteasylib::EventHandler<NeedSaveLocalEvent>,
	qteasylib::EventHandler<CursorHangedupEvent>,
	qteasylib::EventHandler<CursorUnHangedupEvent>
{
	Q_OBJECT

public:
	TimerTableModel(QWidget* parent);
	~TimerTableModel();

	void InsertTimer(const QString& timer_name, const TimerItemStoreData& data);
	TimerItemStoreData* GetTimerItemStoreData(int row);
	void SetTimerItemFlags(int row, TimerItemFlags tags);
	TimerItemFlags GetTimerItemFlags(int row);
	bool SaveTimers();
	QString AutoFormatSecondInData(const TimerItemStoreData& data);
	QString GetTimerName(int row);
	QString GetTags(int row);

private:
	void OnEvent(const SecondUpdateEvent& event) override;
	void OnEvent(const FocusWindowChangedEvent& event) override;
	void OnEvent(const NeedSaveLocalEvent& event) override;
	void OnEvent(const CursorHangedupEvent& event) override;
	void OnEvent(const CursorUnHangedupEvent& event) override;

private:
	void UpdateTimerCount(int row);
	void InitTimers();
	QJsonDocument dbconfig_jsondoc_;
	QWidget* msg_parent_;
	QString cur_proc_name_;
	QString prev_proc_name_;

	QVector<int> cur_run_items_row_;
	QVector<int> cur_hangingup_items_row_;

signals:
	void newTimerAppended();
};