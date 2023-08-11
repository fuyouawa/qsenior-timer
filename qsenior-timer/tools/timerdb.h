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

	bool Open();
	void Close();

	bool SaveData(const QString& timer_name, const TimerItemStoreData& data);
	void ForeachData(std::function<void(const QString&, const TimerItemStoreData&)> callback);
	fustd::Option<QList<TimerItemStoreData::DayTimer>> GetTimerHistory(const QString& timer_name);
	void ChangeTimerName(const QString& origi_timer_name, const QString& timer_name);

	void SetMsgParent(QWidget* msg_parent);

private:
	TimerDb();

	QJsonObject TimerItemStoreDataToJsonWithoutToday(const TimerItemStoreData& data);
	TimerItemStoreData JsonToTimerItemStoreDataWithoutToday(const QJsonObject& obj);

	QJsonObject TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer);
	TimerItemStoreData::DayTimer JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj);

	void ShowDbBrokenError();

	fustd::Option<TimerItemStoreData> JsonToTimerItemStoreDataSafed(const QJsonObject& obj);

	fustd::Option<QList<TimerItemStoreData::DayTimer>> JsonToTimerItemStoreDataDayTimerListSafed(const QJsonArray& arr);

	leveldb::DB* db_;
	QWidget* msg_parent_;
};

#define TimerDbInstanceScope(code) \
    TimerDb::Instance->SetMsgParent(this); \
	code \
	TimerDb::Instance->SetMsgParent(nullptr);

#define TimerDbInstanceScope2(code) \
    TimerDb::Instance->SetMsgParent(msg_parent_); \
	code \
	TimerDb::Instance->SetMsgParent(nullptr);
	