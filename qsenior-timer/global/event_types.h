#pragma once
#include <QString>

struct SecondUpdateEvent {};

struct FocusWindowChangedEvent {
	QString prev_win;
	QString prev_proc;
	QString cur_win;
	QString cur_proc;
};