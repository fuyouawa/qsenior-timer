#include "utils.h"

void ReadUserInfo() {
	QSettings settings{ BasicConfig::UserInfoFilePath, QSettings::IniFormat };
	UserInfo::UserName = settings.value("UserName", "").toString();
	UserInfo::Password = settings.value("Password", "").toString();
}

void SaveUserInfo() {
	QSettings settings{ BasicConfig::UserInfoFilePath, QSettings::IniFormat };
	settings.setValue("UserName", UserInfo::UserName);
	settings.setValue("Password", UserInfo::Password);
}

QByteArray CombineQStrs(std::initializer_list<QString> strs)
{
	QByteArray buf{};
	for (auto& str : strs) {
		buf.append(str.toUtf8());
		buf.append('\0');
	}
	return buf;
}

void RestartApp()
{
	// Start a new instance of the application
	QProcess::startDetached(QCoreApplication::applicationFilePath());

	// Quit the current instance
	QApplication::quit();
}

void InitBasicConfig() {
	BasicConfig::AppDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	BasicConfig::UserInfoFilePath = JoinPaths({ BasicConfig::AppDataDir, "Userinfo.ini" });
}

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