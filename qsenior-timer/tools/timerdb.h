#pragma once

#include <QObject>

#include <leveldb/db.h>
#include <fustd/generic/result.hpp>

#include "global/utils.h"

class TimerDb  : public QObject
{
	Q_OBJECT

public:
	TimerDb(QWidget *parent);
	~TimerDb();

	bool Open();
	void Close();

	fustd::Result<TimerItemStoreData, QString> GetData(const QString& timer_name);
	bool SaveDataList(const QMap<QString, TimerItemStoreData>& data_map);
	void ForeachData(std::function<void(const QString&, const TimerItemStoreData&)> callback);

private:
	leveldb::DB* db_;
	QWidget* parent_;
};
