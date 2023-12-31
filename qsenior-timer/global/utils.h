﻿#pragma once
#include <QWidget>
#include <QJsonDocument>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QSettings>
#include <QStandardPaths>
#include <QDateTime>
#include <Windows.h>
#include <shellapi.h>
#include <Psapi.h>

#include <fustd/generic/result.hpp>

#include "global/config.h"

QString JoinPaths(std::initializer_list<QString> parts);

bool CreateDirIfNoExist(const QString& path);
bool CreateFileIfNoExist(const QString& path);

QString FormatSeconds(int sec);

void ReadSettings();
void SaveSettings();

void InitBasicConfig();

QString GetSettingsFileName();
QString GetUserInfoFileName();
QString GetTimerDbFileName();

qint64 GetCurDateStamp();

HDC DrawWindowBorder(HWND hwnd);

QString FormatErrCode(QString tip, DWORD err_code);

void ShowErrorMsg(QString err, int lv, QWidget* parent=nullptr);

std::string QStrToStl(const QString& str);
QString StlToQStr(const std::string& stl);
QByteArray StlToQBytes(const std::string& stl);

void AutoRegistryStartup();

bool IsRunAsAdmin();

bool AskForAdmin();

QString ErrorCodeToStr(DWORD error);

QString TStrToQStr(LPTSTR tstr);

fustd::Result<QString, DWORD> GetProcessName(DWORD pid);