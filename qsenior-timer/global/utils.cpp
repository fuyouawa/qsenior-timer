#include "utils.h"

QString JoinPaths(std::initializer_list<QString> parts)
{
	QString res;
	for (auto& part : parts) {
		if (!res.isEmpty() && !res.endsWith(QDir::separator())) {
			res += QDir::separator();
		}
		res += part;
	}
	return QDir::cleanPath(res);
}

bool CreateDirIfNoExist(const QString& path)
{
	QDir dir(path);
	if (!dir.exists()) {
		return dir.mkpath(".");
	}
	return true;
}

bool CreateFileIfNoExist(const QString& path)
{
	QFile file(path);
	if (!file.open(QIODevice::ReadOnly) && !file.open(QIODevice::WriteOnly)) {
		return false;
	}
	return true;
}

QString FormatSeconds(int sec)
{
	int days = sec / 86400;
	int hours = (sec % 86400) / 3600;
	int minutes = (sec % 3600) / 60;
	int seconds = sec % 60;

	return QString("%1天%2时%3分%4秒")
		.arg(days, 1, 10, QLatin1Char('0'))
		.arg(hours, 2, 10, QLatin1Char('0'))
		.arg(minutes, 2, 10, QLatin1Char('0'))
		.arg(seconds, 2, 10, QLatin1Char('0'));
}

void ReadSettings()
{
	QSettings settings{ BasicConfig::SettingsSavePath, QSettings::IniFormat };
	settings.beginGroup("Gereral");
	AppSettings::Startup = settings.value("Startup", true).toBool();
	AppSettings::RunInTray = settings.value("RunInTray", true).toBool();
	AppSettings::AutoCloseSave = settings.value("AutoCloseSave", true).toBool();
	AppSettings::AutoTimerSaveLocal = settings.value("AutoTimerSaveLocal", true).toBool();
	AppSettings::AutoCheckUpdate = settings.value("AutoCheckUpdate", true).toBool();
	AppSettings::ScanHangup = settings.value("ScanHangup", true).toBool();

	AppSettings::SaveLocalInter = settings.value("SaveLocalInter", 20000).toInt();
	AppSettings::ScanFocusInter = settings.value("ScanFocusInter", 500).toInt();
	AppSettings::HangupJudgeTime = settings.value("HangupJudgeTime", 10000).toInt();
	settings.endGroup();

	settings.beginGroup("Advanced");
	AppSettings::ErrLevel = settings.value("ErrLevel", 1).toInt();
	settings.endGroup();
}

void SaveSettings()
{
	QSettings settings{ BasicConfig::SettingsSavePath, QSettings::IniFormat };
	settings.beginGroup("Gereral");
	settings.setValue("Startup", AppSettings::Startup);
	settings.setValue("RunInTray", AppSettings::RunInTray);
	settings.setValue("AutoCloseSave", AppSettings::AutoCloseSave);
	settings.setValue("AutoTimerSaveLocal", AppSettings::AutoTimerSaveLocal);
	settings.setValue("AutoCheckUpdate", AppSettings::AutoCheckUpdate);
	settings.setValue("ScanHangup", AppSettings::ScanHangup);

	settings.setValue("SaveLocalInter", AppSettings::SaveLocalInter);
	settings.setValue("ScanFocusInter", AppSettings::ScanFocusInter);
	settings.setValue("HangupJudgeTime", AppSettings::HangupJudgeTime);
	settings.endGroup();

	settings.beginGroup("Advanced");
	settings.setValue("ErrLevel", AppSettings::ErrLevel);
	settings.endGroup();
}

void InitBasicConfig()
{
	BasicConfig::AppDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	CreateDirIfNoExist(BasicConfig::AppDataDir);
	BasicConfig::SettingsSavePath = JoinPaths({ BasicConfig::AppDataDir, GetSettingsFileName() });
	BasicConfig::TimerDbSavePath = JoinPaths({ BasicConfig::AppDataDir, GetTimerDbFileName() });
	BasicConfig::TempFilePath = JoinPaths({ BasicConfig::AppDataDir, "TEMP" });

	QSettings settings{ BasicConfig::SettingsSavePath, QSettings::IniFormat };
	BasicConfig::IsFirstRunApp = settings.value("IsFirstRunApp", true).toBool();
	settings.setValue("IsFirstRunApp", false);
}

QString GetSettingsFileName()
{
	return "Settings.ini";
}

QString GetUserInfoFileName()
{
	return "User-info.ini";
}

QString GetTimerDbFileName()
{
	return "Timer-Db";
}

qint64 GetCurDateStamp()
{
	return QDateTime::currentDateTime().toSecsSinceEpoch();
}

HDC DrawWindowBorder(HWND hwnd)
{
	// 获取当前窗口的设备上下文
	HDC hdc_window, return_dc;
	HGDIOBJ original_pen, original_brush;
	HRGN window_region;
	RECT window_rect;

	// 获取边界宽度
	int border_thickness_x = ::GetSystemMetrics(SM_CXBORDER);
	int border_thickness_y = ::GetSystemMetrics(SM_CYBORDER);

	hdc_window = ::GetWindowDC(hwnd);
	if (!hdc_window)  // 如果无法获取DC, 直接返回nullptr
		return nullptr;

	window_region = ::CreateRectRgn(0, 0, 0, 0);
	HPEN border_pen = ::CreatePen(PS_INSIDEFRAME, 3 * border_thickness_x, 0);
	original_pen = ::SelectObject(hdc_window, border_pen);
	original_brush = ::SelectObject(hdc_window, ::GetStockObject(NULL_BRUSH));

	// 设置绘图模式为反转
	::SetROP2(hdc_window, R2_NOT);

	if (::GetWindowRgn(hwnd, window_region))
	{
		COLORREF window_frame_color = ::GetSysColor(COLOR_WINDOWFRAME);
		HBRUSH hatch_brush = ::CreateHatchBrush(HS_DIAGCROSS, window_frame_color);
		::FrameRgn(hdc_window, window_region, hatch_brush, 3 * border_thickness_x, 3 * border_thickness_y);
		::DeleteObject(hatch_brush);
	}
	else
	{
		int frame_width = ::GetSystemMetrics(SM_CXFRAME);
		int frame_height = ::GetSystemMetrics(SM_CYFRAME);
		int screen_width = ::GetSystemMetrics(SM_CXSCREEN);
		int screen_height = ::GetSystemMetrics(SM_CYSCREEN);

		::GetWindowRect(hwnd, &window_rect);
		if (::IsZoomed(hwnd))
			::Rectangle(hdc_window, frame_width, frame_height, frame_width + screen_width, screen_height + frame_height);
		else
			::Rectangle(hdc_window, 0, 0, window_rect.right - window_rect.left, window_rect.bottom - window_rect.top);
	}

	// 恢复原始对象并删除我们创建的对象
	::SelectObject(hdc_window, original_brush);
	::SelectObject(hdc_window, original_pen);
	::DeleteObject(border_pen);
	::DeleteObject(window_region);

	return_dc = (HDC)::ReleaseDC(hwnd, hdc_window);

	return return_dc;
}

QString FormatErrCode(QString tip, DWORD err_code)
{
	QString tip_text = tip + "\n失败原因: %1\n错误码: %2\n可根据这个错误码前往[微软官方文档]查询以获取更多信息";
	return tip_text.arg(ErrorCodeToStr(err_code)).arg(err_code);
}

void ShowErrorMsg(QString err, int lv, QWidget* parent)
{
	if (lv <= AppSettings::ErrLevel) {
		QString title;
		switch (lv)
		{
		case 1:
			title = "严重错误";
			break;
		case 2:
			title = "错误";
			break;
		default:
			break;
		}
		QMessageBox::critical(parent, title, err);
	}
}

bool IsSameDayTimeStamps(qint64 stamp1, qint64 stamp2)
{
	auto date1 = QDateTime::fromSecsSinceEpoch(stamp1);
	auto date2 = QDateTime::fromSecsSinceEpoch(stamp2);

	return date1.date() == date2.date();
}

std::string QStrToStl(const QString& str)
{
	return str.toLocal8Bit().constData();
}

QString StlToQStr(const std::string& stl)
{
	return QString::fromLocal8Bit(stl.c_str());
}

QByteArray StlToQBytes(const std::string& stl)
{
	return StlToQStr(stl).toUtf8();
}

void AutoRegistryStartup()
{
	QSettings registry("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	if (AppSettings::Startup) {
		registry.setValue("QSeniorTimer", QCoreApplication::applicationFilePath().replace('/', '\\'));
	}
	else {
		registry.remove("QSeniorTimer");
	}
}

bool IsRunAsAdmin()
{
	BOOL fIsRunAsAdmin = FALSE;
	PSID pAdministratorsGroup = NULL;

	// Allocate and initialize a SID of the administrators group.
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &pAdministratorsGroup)) {
		// Determine whether the SID of administrators group is enabled in
		// the primary access token of the process.
		if (!CheckTokenMembership(NULL, pAdministratorsGroup, &fIsRunAsAdmin)) {
			fIsRunAsAdmin = FALSE;
		}
		FreeSid(pAdministratorsGroup);
	}

	return fIsRunAsAdmin;
}

bool AskForAdmin()
{
	wchar_t szPath[MAX_PATH];
	if (GetModuleFileNameW(NULL, szPath, ARRAYSIZE(szPath))) {
		SHELLEXECUTEINFO sei = { sizeof(sei) };
		sei.lpVerb = L"runas";
		sei.lpFile = szPath;
		sei.hwnd = NULL;
		sei.nShow = SW_NORMAL;

		if (!ShellExecuteEx(&sei)) {
			DWORD dwError = GetLastError();
			if (dwError == ERROR_CANCELLED) {
				return false;
			}
		}
	}
	return true;
}

QString ErrorCodeToStr(DWORD error)
{
	LPTSTR err_msg = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		error,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&err_msg,
		0,
		NULL);
	QString res = TStrToQStr(err_msg);
	LocalFree(err_msg);
	return res;
}

QString TStrToQStr(LPTSTR tstr)
{
#ifdef UNICODE
	return QString::fromWCharArray(tstr);
#else
	return QString::fromLocal8Bit(tstr);
#endif // UNICODE
}

fustd::Result<QString, DWORD> GetProcessName(DWORD pid)
{
	TCHAR buf[MAX_PATH];
	HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hprocess) {
		if (GetModuleBaseName(hprocess, NULL, buf, _countof(buf))) {
			CloseHandle(hprocess);
			return fustd::Ok(TStrToQStr(buf));
		}
		CloseHandle(hprocess);
	}
	return fustd::Err(GetLastError());
}