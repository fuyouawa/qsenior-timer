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

QString GetDefaultDbSavePath()
{
	return JoinPaths({ GetAppDataDir(), kDbConfigDirName, kDbConfigJsonFileName});
}

QString GetDbSavePath()
{
	return JoinPaths({ AppSettings::DbSaveDir, kDbConfigDirName, kDbConfigJsonFileName});
}

QString GetSettingsFilePath()
{
	return JoinPaths({ GetAppDataDir(), kSettingsFileName});
}

QString GetAppDataDir()
{
	return QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
}

bool CheckDbSavePath()
{
	auto dir_path = JoinPaths({ AppSettings::DbSaveDir, kDbConfigDirName });
	auto file_path = JoinPaths({ dir_path, kDbConfigJsonFileName });
	if (!CreateDirIfNoExist(dir_path) || !CreateFileIfNoExist(file_path)) {
		return false;
	}
	return true;
}

QJsonObject TimerItemInfoToJson(const TimerItemInfo& info)
{
	//struct TimerItemInfo
	//{
	//	QString timer_name;
	//	QString proc_name;
	//	int status;
	//	bool can_del;
	//	bool can_pause;
	//	bool can_edit;
	//	bool start_imm;
	//	struct {
	//		int total;
	//		int today;
	//		int continuous;
	//		int max_continuous;
	//	} time;
	//};
	QJsonObject obj;

	obj["tn"] = info.timer_name;
	obj["pn"] = info.proc_name;
	obj["st"] = info.status;

	char flags = 0;
	if (info.can_del) flags |= kTimerItemFlagCanDel;
	if (info.can_pause) flags |= kTimerItemFlagCanPause;
	if (info.can_edit) flags |= kTimerItemFlagCanEdit;
	if (info.start_imm) flags |= kTimerItemFlagStartImm;

	obj["fs"] = flags;

	QJsonObject time_obj;
	time_obj["tl"] = info.time.total;
	time_obj["ty"] = info.time.today;
	time_obj["cs"] = info.time.continuous;
	time_obj["mcs"] = info.time.max_continuous;

	obj["to"] = time_obj;

	return obj;
}

TimerItemInfo JsonToTimerItemInfo(const QJsonObject& obj)
{
	TimerItemInfo item;

	item.timer_name = obj["tn"].toString();
	item.proc_name = obj["pn"].toString();
	item.status = obj["st"].toInt();

	int flags = obj["fs"].toInt();

	item.can_del = flags & kTimerItemFlagCanDel;
	item.can_pause = flags & kTimerItemFlagCanPause;
	item.can_edit = flags & kTimerItemFlagCanEdit;
	item.start_imm = flags & kTimerItemFlagStartImm;

	auto time_obj = obj["to"].toObject();
	item.time.total = time_obj["tl"].toInt();
	item.time.today = time_obj["ty"].toInt();
	item.time.continuous = time_obj["cs"].toInt();
	item.time.max_continuous = time_obj["mcs"].toInt();

	return item;
}

fustd::Option<TimerItemInfo> FindTimerItemInfoInJsonByTimerName(const QJsonArray& arr, const QString& timer_name)
{
	for (auto item : arr) {
		auto obj = item.toObject();
		if (obj["pn"] == timer_name)
			return fustd::Some(JsonToTimerItemInfo(obj));
	}
	return fustd::None();
}

QJsonDocument ReadDbConfigFile(QWidget* parent)
{
	auto file_path = GetDbSavePath();
	if (!CheckDbSavePath()) {
		QMessageBox::critical(parent, "严重错误", "无法创建数据库配置文件!\n" + file_path);
	}
	QFile file{ file_path };
	if (!file.open(QIODevice::ReadOnly)) {
		QMessageBox::critical(parent, "严重错误", "无法打开数据库配置文件以读取!\n" + file_path);
		return QJsonDocument();
	}
	return QJsonDocument::fromJson(file.readAll());
}

void WriteDbConfigFile(const QJsonDocument& doc, QWidget* parent)
{
	QFile file{ GetDbSavePath() };
	if (!file.open(QIODevice::WriteOnly)) {
		QMessageBox::critical(parent, "严重错误", "无法打开数据库配置文件以写入!");
		return;
	}
	file.write(doc.toJson());
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
	QSettings settings{ GetSettingsFilePath(), QSettings::IniFormat };
	AppSettings::Startup = settings.value("Startup", true).toBool();
	AppSettings::RunInBg = settings.value("RunInBg", true).toBool();
	AppSettings::AutoCloseSave = settings.value("AutoCloseSave", true).toBool();
	AppSettings::TimerSaveLocal = settings.value("TimerSaveLocal", true).toBool();
	AppSettings::AutoCheckUpdate = settings.value("AutoCheckUpdate", true).toBool();

	AppSettings::AutoSaveLocalInter = settings.value("AutoSaveLocalInter", 60).toInt();
	AppSettings::ScanFocusInter = settings.value("ScanFocusInter", 1).toInt();

	AppSettings::DbSaveDir = settings.value("DbSaveDir", GetDefaultDbSavePath()).toString();
}

void SaveSettings()
{
	QSettings settings{ GetSettingsFilePath(), QSettings::IniFormat };
	settings.setValue("Startup", AppSettings::Startup);
	settings.setValue("RunInBg", AppSettings::RunInBg);
	settings.setValue("AutoCloseSave", AppSettings::AutoCloseSave);
	settings.setValue("TimerSaveLocal", AppSettings::TimerSaveLocal);
	settings.setValue("AutoCheckUpdate", AppSettings::AutoCheckUpdate);

	settings.setValue("AutoSaveLocalInter", AppSettings::AutoSaveLocalInter);
	settings.setValue("ScanFocusInter", AppSettings::ScanFocusInter);

	settings.setValue("DbSaveDir", AppSettings::DbSaveDir);
}
