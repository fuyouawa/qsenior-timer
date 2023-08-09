#pragma once

#include <QObject>
#include <QTimer>

#include <QtEasyLib/QEasyEventSystem>

#include "global/config.h"
#include "global/focus_detector.h"

class TimerController  : public QObject
{
	Q_OBJECT

public:
	static TimerController* const Instance;
	~TimerController();

	void StartAll();
	void StopAll();

private:
	TimerController(QObject* parent=nullptr);
	QTimer focus_detector_timer_;
	QTimer second_timer_;

	void UpdateAll();
};
