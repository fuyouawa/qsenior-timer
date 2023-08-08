#pragma once

#include <QObject>
#include <QGuiApplication>
#include <Windows.h>
#include <QTimer>
#include <QMessageBox>
#include <QtEasyLib/QEasyEventSystem>
#include <strsafe.h>
#include "global/config.h"
#include "global/event_types.h"

class FocusDetector: public QObject
{
	Q_OBJECT

public:
	static FocusDetector* const Instance;
	~FocusDetector();

	void StartScanning();
	void StopScanning();

private:
	TCHAR proc_name_buf[MAX_PATH];
	TCHAR win_name_buf[MAX_PATH];
	TCHAR prev_proc_name_buf[MAX_PATH];
	TCHAR prev_win_name_buf[MAX_PATH];
	QTimer scan_timer_;

private:
	FocusDetector(QObject* parent = nullptr);
	void ScanForceWindow();
};
