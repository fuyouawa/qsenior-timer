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

	QString CurProcName();
	QString PrevProcName();

	QString CurWinName();
	QString PrevWinName();

	void ScanForceWindow();

private:
	friend class TimerController;

	TCHAR proc_name_buf[MAX_PATH];
	TCHAR win_name_buf[MAX_PATH];
	TCHAR prev_proc_name_buf[MAX_PATH];
	TCHAR prev_win_name_buf[MAX_PATH];
	QTimer timer_;

private:
	FocusDetector(QObject* parent = nullptr);
};
