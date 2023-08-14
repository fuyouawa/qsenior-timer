#pragma once

#include <QObject>
#include <QGuiApplication>
#include <Windows.h>
#include <QTimer>
#include <QMessageBox>
#include <strsafe.h>
#include "global/event_types.h"
#include "global/utils.h"

class TimerController;

class FocusDetector: public QObject
{
	Q_OBJECT

public:
	static FocusDetector* const Instance;
	~FocusDetector();

	void ScanForceWindow();

private:
	friend class TimerController;

	QString cur_proc_name_;
	QString prev_proc_name_;
	QTimer timer_;

private:
	FocusDetector(QObject* parent = nullptr);
};
