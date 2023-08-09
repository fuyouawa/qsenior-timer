#pragma once
#include <QWidget>
#include <QJsonDocument>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include <QApplication>
#include <QSettings>
#include <QStandardPaths>
#include "global/config.h"
#include <fustd/generic/option.hpp>

QString JoinPaths(std::initializer_list<QString> parts);

QString GetDefaultDbSavePath();
QString GetDbSavePath();
QString GetSettingsFilePath();

QString GetAppDataDir();

bool CheckDbSavePath();

QJsonObject TimerItemInfoToJson(const TimerItemInfo& info);

TimerItemInfo JsonToTimerItemInfo(const QJsonObject& obj);
fustd::Option<TimerItemInfo> FindTimerItemInfoInJsonByTimerName(const QJsonArray& arr,const QString& timer_name);

QJsonDocument ReadDbConfigFile(QWidget* parent=nullptr);

void WriteDbConfigFile(const QJsonDocument& doc, QWidget* parent = nullptr);

bool CreateDirIfNoExist(const QString& path);
bool CreateFileIfNoExist(const QString& path);

QString FormatSeconds(int sec);

void ReadSettings();
void SaveSettings();