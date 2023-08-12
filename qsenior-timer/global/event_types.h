#pragma once
#include <QString>
#include <QtEasyLib/QEasyEventSystem>
#include "global/config.h"

struct SecondUpdateEvent {};
struct SettingsChangedEvent {};
struct NeedSaveLocalEvent {};
struct CursorHangedupEvent {};
struct CursorUnHangedupEvent {};

struct FocusWindowChangedEvent {
	QString prev_win;
	QString prev_proc;
	QString cur_win;
	QString cur_proc;
};