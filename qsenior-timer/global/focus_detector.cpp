#include "focus_detector.h"

FocusDetector* const FocusDetector::Instance = new FocusDetector();

FocusDetector::FocusDetector(QObject* parent) :
    QObject(parent),
    win_name_buf(),
    proc_name_buf(),
    prev_win_name_buf(),
    prev_proc_name_buf(),
    timer_(this)
{
    connect(&timer_, &QTimer::timeout, this, &FocusDetector::ScanForceWindow);
}

FocusDetector::~FocusDetector()
{
}

QString FocusDetector::CurProcName()
{
    return QString::fromWCharArray(proc_name_buf);
}

QString FocusDetector::PrevProcName()
{
    return QString::fromWCharArray(prev_proc_name_buf);
}

QString FocusDetector::CurWinName()
{
    return QString::fromWCharArray(win_name_buf);
}

QString FocusDetector::PrevWinName()
{
    return QString::fromWCharArray(prev_win_name_buf);
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
                ShowErrorMsg(FormatErrCode("无法获取当前聚焦窗体的进程名称!", GetLastError()), 2);
                CloseHandle(hprocess);
                return;
            }
            CloseHandle(hprocess);
        }
        else {
            ShowErrorMsg(FormatErrCode("无法获取当前聚焦窗体的进程名称!", GetLastError()), 2);
            return;
        }
        if (CompareStringOrdinal(win_name_buf, _countof(win_name_buf), prev_win_name_buf, _countof(prev_win_name_buf), TRUE) != CSTR_EQUAL ||
            CompareStringOrdinal(proc_name_buf, _countof(proc_name_buf), prev_proc_name_buf, _countof(prev_proc_name_buf), TRUE) != CSTR_EQUAL)
        {
            FocusWindowChangedEvent tmp;
            tmp.cur_win = CurWinName();
            tmp.cur_proc = CurProcName();
            tmp.prev_win = PrevWinName();
            tmp.prev_proc = PrevProcName();
            QEasyEventBus::Emit(std::move(tmp));
            StringCchCopy(prev_win_name_buf, _countof(prev_win_name_buf), win_name_buf);
            StringCchCopy(prev_proc_name_buf, _countof(prev_proc_name_buf), proc_name_buf);
        }
    }
}