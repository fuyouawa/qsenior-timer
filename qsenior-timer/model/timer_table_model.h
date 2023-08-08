#pragma once
#include <QStandardItemModel>
#include <QMessageBox>
#include <QtEasyLib/QEasyEventSystem>
#include "global/config.h"
#include "global/event_types.h"

class TimerTableModel : public QStandardItemModel, QEasyEventHandler<SecondUpdateEvent>, QEasyEventHandler<FocusWindowChangedEvent>
{
	Q_OBJECT

public:
	TimerTableModel(QWidget* parent);
	~TimerTableModel();

	void InsertTimer(const TimerItemInfo& info);
	void SetTimerStatus(int row, TimerItemStatus status);

private:
	void OnEvent(const SecondUpdateEvent& event) override;
	void OnEvent(const FocusWindowChangedEvent& event) override;

signals:
	void onAppended();
};