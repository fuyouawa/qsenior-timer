#pragma once

#include <QObject>
#include <QTimer>

#include <QtEasyLib/QEasyEventSystem>

#include "global/event_types.h"
#include "global/config.h"

class TimerController : public QObject, QEasyEventHandler<SettingsChangedEvent>
{
	Q_OBJECT

public:
	static TimerController* const Instance;
	~TimerController();

	void StartNeeded();

private:
	TimerController(QObject* parent=nullptr);
	void UpdateAll();
	void OnEvent(const SettingsChangedEvent& event);

	QTimer focus_detector_timer_;
	QTimer second_timer_;

	QTimer auto_save_local_timer_;

};
