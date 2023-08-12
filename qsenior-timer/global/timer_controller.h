#pragma once

#include <QObject>
#include <QTimer>

#include "global/event_types.h"
#include "global/config.h"
#include "global/focus_detector.h"
#include "global/hangup_detector.h"


class TimerController : public QObject, QEasyEventHandler<SettingsChangedEvent>
{
	Q_OBJECT

public:
	static TimerController* const Instance;
	~TimerController();

	void AutoStartOrClose();

private:
	TimerController(QObject* parent=nullptr);
	void OnEvent(const SettingsChangedEvent& event);

	QTimer second_timer_;

	QTimer auto_save_local_timer_;
};
