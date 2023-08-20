#pragma once
#include <QString>
#include <qteasylib/event_system.h>
#include "global/config.h"

struct SecondUpdateEvent {};
struct SettingsChangedEvent {};
struct NeedSaveLocalEvent {};
struct CursorHangedupEvent {};
struct CursorUnHangedupEvent {};

struct FocusWindowChangedEvent {
	QString prev_proc;
	QString cur_proc;
};

struct NeedAssignNewTimersEvent {
	QJsonObject timers_obj;
};