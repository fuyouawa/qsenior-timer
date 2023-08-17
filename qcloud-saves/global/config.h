﻿#pragma once
#include <QString>
#include <QStandardPaths>
#include <limits>
#include <fustd/generic/result.hpp>

using buf_size_t = quint32;
inline constexpr auto kMaxBufSize = (std::numeric_limits<quint16>::max)();

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
	kSignin,
	kLogin,
	kGetUserProperty
};

enum ResponseCode
{
	kSuccess,
	kUserNameErr,
	kPasswordErr,
	kUserNameRepeat
};

struct PacketBuffer
{
	buf_size_t size;
	char data[1];
};

struct Packet
{
	RequestType req_type;
	QByteArray data;
};