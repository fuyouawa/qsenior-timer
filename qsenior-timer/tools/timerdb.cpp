#include "timerdb.h"

TimerDb::TimerDb(QWidget *parent)
	: QObject((QObject*)parent),
	db_(nullptr),
	parent_(parent)
{
}

TimerDb::~TimerDb()
{
	Close();
}

bool TimerDb::Open()
{
	leveldb::Options opts;
	opts.create_if_missing = true;
	auto status = leveldb::DB::Open(opts, QStrToStl(BasicConfig::TimerDbSavePath), &db_);
	if (!status.ok()) {
		ShowErrorMsg("数据库打开失败, 错误原因: " + status.ToString() + "\n路径: " + QStrToStl(BasicConfig::TimerDbSavePath), 1, parent_);
		return false;
	}
	return true;
}

void TimerDb::Close()
{
	if (db_)
		delete db_;
	db_ = nullptr;
}

fustd::Result<TimerItemStoreData, QString> TimerDb::GetData(const QString& timer_name)
{
	std::string tmp;
	auto status = db_->Get(leveldb::ReadOptions(), QStrToStl(timer_name), &tmp);
	if (status.ok()) {
		auto doc = QJsonDocument::fromJson(QByteArray::fromStdString(tmp));
		if (!doc.isObject()) {
			return fustd::Err("从数据库中读取计时器[" + timer_name + "]失败! 原因: 数据库文件损坏! 路径: " + BasicConfig::TimerDbSavePath);
		}
		return fustd::Ok(JsonToTimerItemStoreData(doc.object()));
	}
	auto err = QString::fromStdString(status.ToString());
	return fustd::Err("从数据库中读取计时器[" + timer_name + "]失败! 原因: " + err + "! 路径: " + BasicConfig::TimerDbSavePath);
}

bool TimerDb::SaveDataList(const QMap<QString, TimerItemStoreData>& data_map)
{
	std::string stlstr_tmp;
	QJsonDocument json_doc_tmp;
	QJsonObject json_obj_tmp;

	QJsonArray histroy;
	QJsonObject today_timer_obj;
	TimerItemStoreData::DayTimer first_histroy_day_timer;
	leveldb::Status status;
	std::string timer_stl_name;

	for (auto iter = data_map.begin(); iter != data_map.end(); iter++) {
		today_timer_obj = TimerItemStoreDataDayTimerToJson(iter.value().today);
		timer_stl_name = QStrToStl(iter.key());

		status = db_->Get(leveldb::ReadOptions(), timer_stl_name, &stlstr_tmp);
		if (status.ok()) {
			json_doc_tmp = QJsonDocument::fromJson(QByteArray::fromStdString(stlstr_tmp));
			json_obj_tmp = json_doc_tmp.object();
			histroy = json_obj_tmp["his"].toArray();
			if (histroy.isEmpty()) {
				goto _broken_item;
			}
			else {
				json_obj_tmp = histroy.begin()->toObject();
				if (json_obj_tmp.isEmpty())
					goto _broken_item;
				first_histroy_day_timer = JsonToTimerItemStoreDataDayTimer(json_obj_tmp);
				if (IsSameDayTimeStamps(first_histroy_day_timer.run_stamp, iter.value().today.run_stamp)) {
					histroy.replace(0, today_timer_obj);
				}
				else {
					histroy.insert(histroy.begin(), today_timer_obj);
				}
			}
		}
		else {
		_broken_item:
			histroy = QJsonArray();
			histroy.append(today_timer_obj);
		}
		json_obj_tmp = TimerItemStoreDataToJson(iter.value());
		json_obj_tmp["his"] = histroy;
		status = db_->Put(leveldb::WriteOptions(), timer_stl_name, QStrToStl(QJsonDocument(json_obj_tmp).toJson(QJsonDocument::Compact)));
		if (!status.ok()) {
			ShowErrorMsg("保存数据失败! 原因: " + status.ToString(), 1, parent_);
			return false;
		}
	}
	return true;
}

void TimerDb::ForeachData(std::function<void(const QString&, const TimerItemStoreData&)> callback)
{
	auto iter = db_->NewIterator(leveldb::ReadOptions());
	for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
		auto doc = QJsonDocument::fromJson(StlToQBytes(iter->value().ToString()));
		if (!doc.isObject()) {
			ShowErrorMsg("从数据库中读取计时器[" + iter->key().ToString() + "]失败! 原因: 数据库文件损坏! 路径: " + QStrToStl(BasicConfig::TimerDbSavePath), 1, parent_);
			QMessageBox::warning(parent_, "提示", "由于出现异常, 已停止继续加载计时器!");
			return;
		}
		callback(StlToQStr(iter->key().ToString()), JsonToTimerItemStoreData(doc.object()));
	}
	delete iter;
}
