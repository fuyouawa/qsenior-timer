#include "focus_detector.h"

FocusDetector* const FocusDetector::Instance = new FocusDetector();

FocusDetector::FocusDetector(QObject* parent) :
    QObject(parent),
    timer_(this)
{
    connect(&timer_, &QTimer::timeout, this, &FocusDetector::ScanForceWindow);
}

FocusDetector::~FocusDetector()
{
}


void FocusDetector::ScanForceWindow()
{
    HWND hwnd = GetForegroundWindow();

    if (hwnd) {
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        if (auto res = GetProcessName(pid); res.IsOk()) {
            cur_proc_name_ = res.OkVal();
        }
        else {
            ShowErrorMsg(FormatErrCode("无法获取当前聚焦窗体的进程名称!", res.ErrVal()), 2);
            return;
        }
        if (cur_proc_name_ != prev_proc_name_)
        {
            FocusWindowChangedEvent tmp;
            tmp.cur_proc = cur_proc_name_;
            tmp.prev_proc = prev_proc_name_;
            prev_proc_name_ = cur_proc_name_;
            QEasyEventBus::Emit(std::move(tmp));
        }
    }
    else {
        ShowErrorMsg(FormatErrCode("无法获取当前聚焦窗体的进程名称!", GetLastError()), 2);
    }
}