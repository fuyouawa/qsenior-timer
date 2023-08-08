#include "focus_detector.h"

FocusDetector* const FocusDetector::Instance = new FocusDetector();

FocusDetector::FocusDetector(QObject* parent) :
    QObject(parent),
    win_name_buf(),
    proc_name_buf(),
    prev_win_name_buf(),
    prev_proc_name_buf(),
    scan_timer_(this)
{
    scan_timer_.setInterval(Settings::ScanFocusInter * 1000);
    connect(&scan_timer_, &QTimer::timeout, this, &FocusDetector::ScanForceWindow);
}

FocusDetector::~FocusDetector()
{
}

void FocusDetector::StartScanning()
{
    scan_timer_.start();
}

void FocusDetector::StopScanning()
{
    scan_timer_.stop();
}

void FocusDetector::ScanForceWindow()
{
    HWND hwnd = GetForegroundWindow();
    if (hwnd) {
        GetWindowText(hwnd, win_name_buf, _countof(win_name_buf));
        DWORD pid;
        GetWindowThreadProcessId(hwnd, &pid);
        HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
        if (hprocess) {
            DWORD proc_name_capacity = _countof(proc_name_buf);
            if (!QueryFullProcessImageName(hprocess, 0, proc_name_buf, &proc_name_capacity)) {
                auto error = GetLastError();
                LPTSTR err_msg = nullptr;
                FormatMessage(
                    FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                    NULL,
                    error,
                    MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                    (LPTSTR)&err_msg,
                    0,
                    NULL);
                QString tip_text = "无法获取当前聚焦窗体的进程!\n失败原因: %1\n错误码: %2\n可根据这个错误码前往[微软官方文档]查询以获取更多信息";
                if (err_msg)
                    tip_text = tip_text.arg(err_msg).arg(error);
                else
                    tip_text = tip_text.arg("无法分析失败原因").arg(error);
                QMessageBox::critical(nullptr, "严重错误", tip_text);
            }
            CloseHandle(hprocess);
        }
        if (CompareStringOrdinal(win_name_buf, _countof(win_name_buf), prev_win_name_buf, _countof(prev_win_name_buf), TRUE) != 0 ||
            CompareStringOrdinal(proc_name_buf, _countof(proc_name_buf), prev_proc_name_buf, _countof(prev_proc_name_buf), TRUE) != 0)
        {
            FocusWindowChangedEvent tmp;
            tmp.cur_win = QString::fromWCharArray(win_name_buf);
            tmp.cur_proc = QString::fromWCharArray(proc_name_buf);
            tmp.prev_win = QString::fromWCharArray(prev_win_name_buf);
            tmp.prev_proc = QString::fromWCharArray(prev_proc_name_buf);
            QEasyEventBus::Emit(tmp);
            StringCchCopy(prev_win_name_buf, _countof(prev_win_name_buf), win_name_buf);
            StringCchCopy(prev_proc_name_buf, _countof(prev_proc_name_buf), proc_name_buf);
        }
    }
    scan_timer_.setInterval(Settings::ScanFocusInter * 1000);
}