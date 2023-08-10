﻿#pragma once

#include <QObject>
#include <QGuiApplication>
#include <Windows.h>
#include <QTimer>
#include <QMessageBox>
#include <QtEasyLib/QEasyEventSystem>
#include <strsafe.h>
#include "global/event_types.h"
#include "global/utils.h"

class FocusDetector: public QObject, QEasyEventHandler<NeedScanForceWindowEvent>
{
	Q_OBJECT

public:
	static FocusDetector* const Instance;
	~FocusDetector();

private:
	TCHAR proc_name_buf[MAX_PATH];
	TCHAR win_name_buf[MAX_PATH];
	TCHAR prev_proc_name_buf[MAX_PATH];
	TCHAR prev_win_name_buf[MAX_PATH];
	void OnEvent(const NeedScanForceWindowEvent& event) override;

private:
	FocusDetector(QObject* parent = nullptr);
};
