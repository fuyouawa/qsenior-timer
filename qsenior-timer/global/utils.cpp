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
	AppSettings::Startup = settings.value("Startup", true).toBool();
	AppSettings::RunInBg = settings.value("RunInBg", true).toBool();
	AppSettings::AutoCloseSave = settings.value("AutoCloseSave", true).toBool();
	AppSettings::TimerSaveLocal = settings.value("TimerSaveLocal", true).toBool();
	AppSettings::AutoCheckUpdate = settings.value("AutoCheckUpdate", true).toBool();

	AppSettings::AutoSaveLocalInter = settings.value("AutoSaveLocalInter", 20).toInt();
	AppSettings::ScanFocusInter = settings.value("ScanFocusInter", 1).toInt();

	AppSettings::ErrLevel = settings.value("ErrLevel", 1).toInt();
}

void SaveSettings()
{
	QSettings settings{ BasicConfig::SettingsSavePath, QSettings::IniFormat };
	settings.setValue("Startup", AppSettings::Startup);
	settings.setValue("RunInBg", AppSettings::RunInBg);
	settings.setValue("AutoCloseSave", AppSettings::AutoCloseSave);
	settings.setValue("TimerSaveLocal", AppSettings::TimerSaveLocal);
	settings.setValue("AutoCheckUpdate", AppSettings::AutoCheckUpdate);

	settings.setValue("AutoSaveLocalInter", AppSettings::AutoSaveLocalInter);
	settings.setValue("ScanFocusInter", AppSettings::ScanFocusInter);

	settings.setValue("ErrLevel", AppSettings::ErrLevel);
}

void InitBasicConfig()
{
	BasicConfig::AppDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	CreateDirIfNoExist(BasicConfig::AppDataDir);
	BasicConfig::SettingsSavePath = JoinPaths({ BasicConfig::AppDataDir, GetSettingsFileName() });
	BasicConfig::TimerDbSavePath = JoinPaths({ BasicConfig::AppDataDir, GetTimerDbFileName() });
}

QString GetSettingsFileName()
{
	return "Settings.ini";
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
	LPTSTR err_msg = nullptr;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		err_code,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&err_msg,
		0,
		NULL);
	QString tip_text = tip + "\n失败原因: %1\n错误码: %2\n可根据这个错误码前往[微软官方文档]查询以获取更多信息";
	if (err_msg)
		tip_text = tip_text.arg(err_msg).arg(err_code);
	else
		tip_text = tip_text.arg("无法分析失败原因").arg(err_code);
	return tip_text;
}

void ShowErrorMsg(QString err, int lv, QWidget* parent)
{
	if (lv <= AppSettings::ErrLevel) {
		QMessageBox::critical(parent, "严重错误", err);
	}
}

void ShowErrorMsg(std::string err, int lv, QWidget* parent)
{
	ShowErrorMsg(QString::fromStdString(err), lv, parent);
}

QJsonObject TimerItemStoreDataToJson(const TimerItemStoreData& data)
{
	QJsonObject obj;

	obj["pn"] = data.proc_name;
	obj["ts"] = data.tags;
	obj["ss"] = data.status;
	obj["tt"] = data.total_time;

	obj["ty"] = TimerItemStoreDataDayTimerToJson(data.today);

	int flags = 0;
	if (data.can_del) {
		flags |= kTimerItemFlagCanDel;
	}
	if (data.can_pause) {
		flags |= kTimerItemFlagCanPause;
	}
	if (data.can_edit) {
		flags |= kTimerItemFlagCanEdit;
	}
	if (data.is_hidden) {
		flags |= kTimerItemFlagIsHidden;
	}
	obj["fs"] = flags;

	return obj;
}

TimerItemStoreData JsonToTimerItemStoreData(const QJsonObject& obj)
{
	TimerItemStoreData data;

	data.proc_name = obj["pn"].toString();
	data.tags = obj["ts"].toString();
	data.status = static_cast<char>(obj["ss"].toInt());
	data.total_time = obj["tt"].toInt();

	data.today = JsonToTimerItemStoreDataDayTimer(obj["ty"].toObject());

	int flags = obj["fs"].toInt();
	data.can_del = flags & kTimerItemFlagCanDel;
	data.can_pause = flags & kTimerItemFlagCanPause;
	data.can_edit = flags & kTimerItemFlagCanEdit;
	data.is_hidden = flags & kTimerItemFlagIsHidden;

	return data;
}

QJsonObject TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer)
{
	QJsonObject day_timer_obj;
	day_timer_obj["rs"] = timer.run_stamp;
	day_timer_obj["dt"] = timer.day_time;
	day_timer_obj["lcs"] = timer.last_continuous;
	day_timer_obj["mcs"] = timer.max_continuous;
	return day_timer_obj;
}

TimerItemStoreData::DayTimer JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj)
{
	TimerItemStoreData::DayTimer timer;
	timer.run_stamp = obj["rs"].toVariant().toLongLong();
	timer.day_time = obj["dt"].toVariant().toLongLong();
	timer.last_continuous = obj["lcs"].toVariant().toLongLong();
	timer.max_continuous = obj["mcs"].toVariant().toLongLong();
	return timer;
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
	auto b = QByteArray::fromStdString(stl);
	return QByteArray::fromStdString(stl);
}

TimerItemStoreData TimerItemBasicInfoToStoreData(const TimerItemBasicInfo& info)
{
	TimerItemStoreData store{};
	store.proc_name = info.proc_name;
	store.tags = info.tags;
	store.can_del = info.can_del;
	store.can_edit = info.can_edit;
	store.can_pause = info.can_pause;
	return store;
}

TimerItemBasicInfo TimerItemStoreDataToBasicInfo(const QString& timer_name, const TimerItemStoreData& data)
{
	TimerItemBasicInfo info{};
	info.proc_name = data.proc_name;
	info.can_del = data.can_del;
	info.can_edit = data.can_edit;
	info.can_pause = data.can_pause;
	info.tags = data.tags;
	info.timer_name = timer_name;
	return info;
}
