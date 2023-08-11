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
	TimerDb(QWidget *parent);
	~TimerDb();

	bool Open();
	void Close();

	bool SaveDataList(const QMap<QString, TimerItemStoreData>& data_map);
	void ForeachData(std::function<void(const QString&, const TimerItemStoreData&)> callback);

private:
	QJsonObject TimerItemStoreDataToJsonWithoutToday(const TimerItemStoreData& data);
	TimerItemStoreData JsonToTimerItemStoreDataWithoutToday(const QJsonObject& obj);

	QJsonObject TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer);
	TimerItemStoreData::DayTimer JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj);

	void ShowDbBrokenError();

	fustd::Option<TimerItemStoreData> JsonToTimerItemStoreDataSafed(const QJsonObject& obj);

	leveldb::DB* db_;
	QWidget* parent_;
};
