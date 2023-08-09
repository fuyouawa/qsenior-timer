#pragma once
#include <QStandardItemModel>
#include <QMessageBox>
#include <QFile>
#include <QApplication>
#include <QtEasyLib/QEasyEventSystem>
#include "global/utils.h"
#include "global/event_types.h"

class TimerTableModel : public QStandardItemModel, QEasyEventHandler<SecondUpdateEvent>, QEasyEventHandler<FocusWindowChangedEvent>
{
	Q_OBJECT

public:
	TimerTableModel(QWidget* parent);
	~TimerTableModel();

	void InsertTimer(const TimerItemInfo& info);
	void SetTimerStatus(int row, TimerItemStatus status);
	TimerItemInfo* GetTimerItemInfo(int row);
	TimerItemTags GetTimerItemTags(int row);
	void SetTimerItemTags(int row, TimerItemTags tags);

private:
	void OnEvent(const SecondUpdateEvent& event) override;
	void OnEvent(const FocusWindowChangedEvent& event) override;

private:
	void InitItems();
	void AppendToJsonDoc(const TimerItemInfo& info);
	void UpdateTimerCount(int row);
	QJsonDocument dbconfig_jsondoc_;

signals:
	void newTimerAppended();
};