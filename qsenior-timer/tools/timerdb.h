#pragma once

#include <QObject>

#include <leveldb/db.h>
#include <fustd/generic/result.hpp>
#include <fustd/generic/option.hpp>

#include "global/utils.h"

class TimerDb  : public QObject
{
	Q_OBJECT

public:
	static TimerDb* const Instance;

	~TimerDb();

	bool SaveData(const QString& timer_name, const TimerItemStoreData& data);
	bool ForeachData(std::function<void(const QString&, const TimerItemStoreData&)> callback);
	fustd::Option<QList<TimerItemStoreData::DayTimer>> GetTimerHistory(const QString& timer_name);
	bool ChangeTimerName(const QString& dest_timer_name, const QString& change);
	bool ChangeTimerTags(const QString& dest_timer_name, const QString& change);

	QString LastError();

	bool Open();
	void Close();

private:
	TimerDb();

	QJsonObject TimerItemStoreDataToJsonWithoutToday(const TimerItemStoreData& data);
	TimerItemStoreData JsonToTimerItemStoreDataWithoutToday(const QJsonObject& obj);

	QJsonObject TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer);
	TimerItemStoreData::DayTimer JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj);

	void DbBrokenError();

	fustd::Option<TimerItemStoreData> JsonToTimerItemStoreDataSafed(const QJsonObject& obj);

	fustd::Option<QList<TimerItemStoreData::DayTimer>> JsonToHistroySafed(const QJsonArray& arr);

	fustd::Result<QJsonObject, leveldb::Status> ReadTimerJsonSafed(const QString& timer_name);
	leveldb::Status SaveTimerJsonSafed(const QString& timer_name, const QJsonObject& obj);
	leveldb::Status DelectTimerSafed(const QString& timer_name);

	fustd::Option<QJsonArray> GetHistroyJsonInJsonSafed(const QJsonObject& obj);

	void SetLastErr(const QString& err);

	leveldb::DB* db_;
	QString last_err_;
};