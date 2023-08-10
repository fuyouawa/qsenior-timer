#include "timer_controller.h"

TimerController* const TimerController::Instance = new TimerController();

TimerController::TimerController(QObject *parent)
	: QObject(parent),
    focus_detector_timer_(this),
    second_timer_(this),
    auto_save_local_timer_(this)
{
    second_timer_.setInterval(1000);

    connect(&focus_detector_timer_, &QTimer::timeout, [this]() {
        QEasyEventBus::Emit(NeedScanForceWindowEvent());
        });
    connect(&second_timer_, &QTimer::timeout, [this]() {
        QEasyEventBus::Emit(SecondUpdateEvent());
        });
    connect(&auto_save_local_timer_, &QTimer::timeout, [this]() {
        QEasyEventBus::Emit(NeedSaveLocalEvent());
        });
}

TimerController::~TimerController()
{}


void TimerController::StartNeeded()
{
    UpdateAll();
    focus_detector_timer_.start();
    if (AppSettings::AutoSaveLocalInter) {
        auto_save_local_timer_.start();
    }
    second_timer_.start();
}

void TimerController::UpdateAll()
{
    focus_detector_timer_.setInterval(AppSettings::ScanFocusInter * 1000);
    auto_save_local_timer_.setInterval(AppSettings::AutoSaveLocalInter * 1000);
}

void TimerController::OnEvent(const SettingsChangedEvent& event)
{
    StartNeeded();
}
