#include "timer_controller.h"

TimerController* const TimerController::Instance = new TimerController();

TimerController::TimerController(QObject *parent)
	: QObject(parent),
    second_timer_(this),
    auto_save_local_timer_(this)
{
    connect(&second_timer_, &QTimer::timeout, [this]() {
        qteasylib::EventBus::Emit(SecondUpdateEvent());
        });
    connect(&auto_save_local_timer_, &QTimer::timeout, [this]() {
        qteasylib::EventBus::Emit(NeedSaveLocalEvent());
        });
}

TimerController::~TimerController()
{}


void TimerController::AutoStartOrClose()
{
    FocusDetector::Instance->timer_.setInterval(AppSettings::ScanFocusInter);
    auto_save_local_timer_.setInterval(AppSettings::SaveLocalInter);
    HangupDetector::Instance->scan_hangup_timer_.setInterval(AppSettings::HangupJudgeTime);
    second_timer_.setInterval(1000);
    HangupDetector::Instance->scan_hangup_aux_timer_.setInterval(100);

    FocusDetector::Instance->timer_.start();

    if (AppSettings::AutoTimerSaveLocal)
        auto_save_local_timer_.start();
    else
        auto_save_local_timer_.stop();

    if (AppSettings::ScanHangup)
        HangupDetector::Instance->scan_hangup_aux_timer_.start();
    else {
        HangupDetector::Instance->scan_hangup_aux_timer_.stop();
        HangupDetector::Instance->scan_hangup_timer_.stop();
    }

    second_timer_.start();
}

void TimerController::OnEvent(const SettingsChangedEvent& event)
{
    AutoStartOrClose();
}
