#pragma once
#include <QWidget>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QSettings>
#include <QStandardPaths>
#include <QDateTime>
#include <Windows.h>

#include "global/config.h"

QString JoinPaths(std::initializer_list<QString> parts);

bool CreateDirIfNoExist(const QString& path);
bool CreateFileIfNoExist(const QString& path);

QString FormatSeconds(int sec);

void ReadSettings();
void SaveSettings();

void InitBasicConfig();

QString GetSettingsFileName();
QString GetTimerDbFileName();

qint64 GetCurDateStamp();

HDC DrawWindowBorder(HWND hwnd);

QString FormatErrCode(QString tip, DWORD err_code);

void ShowErrorMsg(QString err, int lv, QWidget* parent=nullptr);
void ShowErrorMsg(std::string err, int lv, QWidget* parent=nullptr);

QJsonObject TimerItemStoreDataToJson(const TimerItemStoreData& data);
TimerItemStoreData JsonToTimerItemStoreData(const QJsonObject& obj);

QJsonObject TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer);
TimerItemStoreData::DayTimer JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj);

bool IsSameDayTimeStamps(qint64 stamp1, qint64 stamp2);

std::string QStrToStl(const QString& str);
QString StlToQStr(const std::string& stl);
QByteArray StlToQBytes(const std::string& stl);

TimerItemStoreData TimerItemBasicInfoToStoreData(const TimerItemBasicInfo& info);

TimerItemBasicInfo TimerItemStoreDataToBasicInfo(const QString& timer_name, const TimerItemStoreData& data);