#pragma once

#include <QObject>
#include <QCursor>
#include "global/event_types.h"

class TimerController;

class HangupDetector  : public QObject
{
	Q_OBJECT

public:
	static HangupDetector* const Instance;

	~HangupDetector();

	void ScanCursorHangup();
	void ScanCursorHangupAuxiliary();

private:
	friend class TimerController;

	HangupDetector(QObject* parent = nullptr);
	QPoint prev_cursor_pos_;
	bool is_hangingup_;
	QTimer scan_hangup_timer_;
	QTimer scan_hangup_aux_timer_;
};
