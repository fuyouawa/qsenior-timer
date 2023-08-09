#include "timer_controller.h"

TimerController* const TimerController::Instance = new TimerController();

TimerController::TimerController(QObject *parent)
	: QObject(parent),
    focus_detector_timer_(this),
    second_timer_(this)
{
    second_timer_.setInterval(1000);

	connect(&focus_detector_timer_, &QTimer::timeout, FocusDetector::Instance, &FocusDetector::ScanForceWindow);
    connect(&second_timer_, &QTimer::timeout, [this]() {
        QEasyEventBus::Emit(SecondUpdateEvent());
        });
}

TimerController::~TimerController()
{}


void TimerController::StartAll()
{
    UpdateAll();
    focus_detector_timer_.start();
    second_timer_.start();
}

void TimerController::StopAll()
{
    focus_detector_timer_.stop();
    second_timer_.stop();
}

void TimerController::UpdateAll()
{
    focus_detector_timer_.setInterval(AppSettings::ScanFocusInter * 1000);
}
