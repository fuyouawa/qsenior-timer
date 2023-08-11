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
			json_doc_tmp = QJsonDocument::fromJson(StlToQBytes(stlstr_tmp));
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
				if (first_histroy_day_timer.julian_date == iter.value().today.julian_date) {
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
		json_obj_tmp = TimerItemStoreDataToJsonWithoutToday(iter.value());
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
	QJsonDocument json_doc_tmp;

	auto iter = db_->NewIterator(leveldb::ReadOptions());
	for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
		json_doc_tmp = QJsonDocument::fromJson(StlToQBytes(iter->value().ToString()));
		if (!json_doc_tmp.isObject())
			goto _err;
		if (auto opt = JsonToTimerItemStoreDataSafed(json_doc_tmp.object()); opt.IsSome())
			callback(StlToQStr(iter->key().ToString()), opt.SomeVal());
		else goto _err;
	}
_suc:
	delete iter;
	return;
_err:
	ShowDbBrokenError();
	QMessageBox::warning(parent_, "提示", "由于出现异常, 已停止加载计时器!");
	delete iter;
}

QJsonObject TimerDb::TimerItemStoreDataToJsonWithoutToday(const TimerItemStoreData& data)
{
	QJsonObject obj;

	obj["pn"] = data.proc_name;
	obj["ts"] = data.tags;
	obj["ss"] = data.status == kStatusRunning ? kStatusStanding : data.status;
	obj["tt"] = data.total_time;

	int flags = 0;
	if (data.can_del) {
		flags |= kFlagCanDel;
	}
	if (data.can_pause) {
		flags |= kFlagCanPause;
	}
	if (data.can_edit) {
		flags |= kFlagCanEdit;
	}
	if (data.is_hidden) {
		flags |= kFlagIsHidden;
	}
	obj["fs"] = flags;

	return obj;
}

TimerItemStoreData TimerDb::JsonToTimerItemStoreDataWithoutToday(const QJsonObject& obj)
{
	TimerItemStoreData data{};

	data.proc_name = obj["pn"].toString();
	data.tags = obj["ts"].toString();
	data.status = static_cast<char>(obj["ss"].toInt());
	data.total_time = obj["tt"].toInt();

	int flags = obj["fs"].toInt();
	data.can_del = flags & kFlagCanDel;
	data.can_pause = flags & kFlagCanPause;
	data.can_edit = flags & kFlagCanEdit;
	data.is_hidden = flags & kFlagIsHidden;

	return data;
}

QJsonObject TimerDb::TimerItemStoreDataDayTimerToJson(const TimerItemStoreData::DayTimer& timer)
{
	QJsonObject day_timer_obj{};
	day_timer_obj["jd"] = timer.julian_date;
	day_timer_obj["dt"] = timer.day_time;
	day_timer_obj["lcs"] = timer.last_continuous;
	day_timer_obj["mcs"] = timer.max_continuous;
	return day_timer_obj;
}

TimerItemStoreData::DayTimer TimerDb::JsonToTimerItemStoreDataDayTimer(const QJsonObject& obj)
{
	TimerItemStoreData::DayTimer timer{};
	timer.julian_date = obj["jd"].toVariant().toLongLong();
	timer.day_time = obj["dt"].toVariant().toLongLong();
	timer.last_continuous = obj["lcs"].toVariant().toLongLong();
	timer.max_continuous = obj["mcs"].toVariant().toLongLong();
	return timer;
}

void TimerDb::ShowDbBrokenError()
{
	ShowErrorMsg("从数据库中读取计时器失败!\n原因: 数据库文件损坏!\n路径: " + QStrToStl(BasicConfig::TimerDbSavePath), 1, parent_);
}

fustd::Option<TimerItemStoreData> TimerDb::JsonToTimerItemStoreDataSafed(const QJsonObject& obj)
{
	auto data = JsonToTimerItemStoreDataWithoutToday(obj);
	auto histroy = obj["his"].toArray();
	if (histroy.isEmpty())
		return fustd::None();
	auto first_his = histroy.begin()->toObject();
	if (first_his.isEmpty())
		return fustd::None();
	if (QDate::currentDate().toJulianDay() == first_his["jd"].toVariant().toULongLong()) {
		data.today = JsonToTimerItemStoreDataDayTimer(first_his);
	}
	else {
		data.today.julian_date = QDate::currentDate().toJulianDay();
	}
	return fustd::Some(data);
}