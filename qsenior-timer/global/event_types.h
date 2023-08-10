#pragma once
#include <QString>

struct SecondUpdateEvent {};
struct SettingsChangedEvent {};
struct NeedScanForceWindowEvent {};
struct NeedSaveLocalEvent {};

struct FocusWindowChangedEvent {
	QString prev_win;
	QString prev_proc;
	QString cur_win;
	QString cur_proc;
};