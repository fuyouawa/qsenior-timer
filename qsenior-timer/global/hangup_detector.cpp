#include "hangup_detector.h"

HangupDetector* const HangupDetector::Instance = new HangupDetector();

HangupDetector::HangupDetector(QObject *parent)
	: QObject(parent),
	prev_cursor_pos_(QCursor::pos()),
	is_hangingup_(false),
	scan_hangup_timer_(this),
	scan_hangup_aux_timer_(this)
{
	connect(&scan_hangup_timer_, &QTimer::timeout, this, &HangupDetector::ScanCursorHangup);
	connect(&scan_hangup_aux_timer_, &QTimer::timeout, this, &HangupDetector::ScanCursorHangupAuxiliary);
}

HangupDetector::~HangupDetector()
{}

void HangupDetector::ScanCursorHangup()
{
	if (QCursor::pos() == prev_cursor_pos_) {
		is_hangingup_ = true;
		scan_hangup_timer_.stop();
		qteasylib::EventBus::Emit(CursorHangedupEvent());
	}
}

void HangupDetector::ScanCursorHangupAuxiliary()
{
	auto cur_pos = QCursor::pos();
	auto active = scan_hangup_timer_.isActive();
	if (cur_pos == prev_cursor_pos_) {
		if (!active && !is_hangingup_)
			scan_hangup_timer_.start();
	}
	else {
		if (active)
			scan_hangup_timer_.stop();
		prev_cursor_pos_ = cur_pos;
		if (is_hangingup_) {
			is_hangingup_ = false;
			qteasylib::EventBus::Emit(CursorUnHangedupEvent());
		}
	}
}
