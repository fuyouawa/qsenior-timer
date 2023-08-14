#pragma once
#include <QString>
#include <QStandardPaths>

class UserInfo
{
public:
	inline static QString UserName;
	inline static QString Password;
};

class BasicConfig
{
public:
	inline static QString UserInfoFilePath;
	inline static QString AppDataDir;
};

enum RequestType
{
	kSignin
};

enum ResponseCode
{
	kSuccess,
	kNonUserName,
	kErrPassword
};