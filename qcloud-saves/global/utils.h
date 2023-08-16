#pragma once
#include <QDir>
#include <QSettings>
#include <QApplication>
#include <QProcess>
#include "global/config.h"

QString JoinPaths(std::initializer_list<QString> parts);

void InitBasicConfig();

void ReadUserInfo();

void SaveUserInfo();

QByteArray CombineQStrs(std::initializer_list<QString> strs);

void RestartApp();