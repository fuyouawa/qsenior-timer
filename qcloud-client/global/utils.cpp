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
	QProcess::startDetached(QCoreApplication::applicationFilePath());
	QApplication::quit();
}

void SetUserNameAndPassword(const QString& user_name, const QString password)
{
	UserInfo::UserName = user_name;
	UserInfo::Password = password;
}

void InitBasicConfig(char* argv[]) {
	BasicConfig::AppDataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
	BasicConfig::UserInfoFilePath = JoinPaths({ BasicConfig::AppDataDir, "Userinfo.ini" });
	//BasicConfig::TempFilePath = argv[1];
	BasicConfig::TempFilePath = "C:\\Users\\29071\\AppData\\Roaming\\QSeniorTimer\\TEMP";
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