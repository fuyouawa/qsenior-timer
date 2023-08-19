#include "timerdb.h"

TimerDb* const TimerDb::Instance = new TimerDb();

TimerDb::TimerDb()
	: QObject(nullptr),
	db_(nullptr)
{

}

TimerDb::~TimerDb()
{
}

bool TimerDb::SaveData(const QString& timer_name, const TimerItemStoreData& data)
{
	QJsonObject json_obj_tmp;
	QJsonArray histroy;

	auto today_timer_obj = TimerItemStoreDataDayTimerToJson(data.today);

	if (auto res = ReadTimerJsonSafed(timer_name); res.IsOk()) {
		if (auto opt = GetHistroyJsonInJsonSafed(res.OkVal()); opt.IsSome()) {
			histroy = opt.SomeVal();
			json_obj_tmp = histroy.begin()->toObject();
			if (json_obj_tmp.isEmpty())
				goto _broken_item;
			auto first_histroy_day_timer = JsonToTimerItemStoreDataDayTimer(json_obj_tmp);
			if (first_histroy_day_timer.julian_date == data.today.julian_date)
				histroy.replace(0, today_timer_obj);
			else
				histroy.insert(histroy.begin(), today_timer_obj);
		}
		else goto _broken_item;
	}
	else {
	_broken_item:
		histroy = QJsonArray();
		histroy.append(today_timer_obj);
	}
	json_obj_tmp = TimerItemStoreDataToJsonWithoutToday(data);
	json_obj_tmp["his"] = histroy;
	auto status = SaveTimerJsonSafed(timer_name, json_obj_tmp);
	if (!status.ok()) {
		SetLastErr("保存数据失败! 原因: " + StlToQStr(status.ToString()));
		return false;
	}
	return true;
}

bool TimerDb::ForeachData(const std::function<void(const QString&, const TimerItemStoreData&)>& callback)
{
	return ForeachBuffer([this, &callback](const QString& timer_name, const QByteArray& data) {
		QJsonParseError parse_err;
		auto doc = QJsonDocument::fromJson(data, &parse_err);
		if (parse_err.error != QJsonParseError::NoError) {
			SetLastErr("从数据库中读取计时器失败!\n原因: " + parse_err.errorString());
			return false;
		}
		if (!doc.isObject()) {
			DbBrokenError();
			return false;
		}
		if (auto opt = JsonToTimerItemStoreDataSafed(doc.object()); opt.IsSome())
			callback(timer_name, opt.SomeVal());
		else {
			DbBrokenError();
			return false;
		}
		return true;
		});
}

fustd::Option<QList<TimerItemStoreData::DayTimer>> TimerDb::GetTimerHistory(const QString& timer_name)
{
	std::string stlstr_tmp;
	auto status = db_->Get(leveldb::ReadOptions(), QStrToStl(timer_name), &stlstr_tmp);
	if (status.ok()) {
		auto doc = QJsonDocument::fromJson(StlToQBytes(stlstr_tmp));
		if (doc.isEmpty() || !doc.isObject()) {
			DbBrokenError();
			return fustd::None();
		}
		if (auto opt = GetHistroyJsonInJsonSafed(doc.object()); opt.IsSome()) {
			return JsonToHistroySafed(opt.SomeVal());
		}
	}
	SetLastErr("计时器: " + timer_name + "的历史记录从数据库中读取失败!\n原因: " + StlToQStr(status.ToString()));
	return fustd::None();
}

bool TimerDb::ChangeTimerName(const QString& dest_timer_name, const QString& change)
{
	leveldb::Status status;
	if (auto res = ReadTimerJsonSafed(dest_timer_name); res.IsOk()) {
		status = DelectTimerSafed(dest_timer_name);
		if (status.ok()) {
			status = SaveTimerJsonSafed(change, res.OkVal());
			if (status.ok())
				return true;
		}
	}
	else {
		status = res.ErrVal();
	}
	SetLastErr("计时器: " + dest_timer_name + "的名称在数据库中修改失败!\n原因: " + StlToQStr(status.ToString()));
	return false;
}

bool TimerDb::ChangeTimerTags(const QString& dest_timer_name, const QString& change)
{
	leveldb::Status status;
	if (auto res = ReadTimerJsonSafed(dest_timer_name); res.IsOk()) {
		auto obj = res.OkVal();
		obj["ts"] = change;
		status = SaveTimerJsonSafed(change, obj);
		if (status.ok())
			return true;
	}
	else {
		status = res.ErrVal();
	}
	SetLastErr("计时器: " + dest_timer_name + "的名称在数据库中修改失败!\n原因: " + StlToQStr(status.ToString()));
	return false;
}

bool TimerDb::ForeachBuffer(const std::function<bool(const QString&, const QByteArray&)>& callback)
{
	bool suc = true;
	auto iter = db_->NewIterator(leveldb::ReadOptions());
	for (iter->SeekToFirst(); iter->Valid(); iter->Next()) {
		if (!callback(StlToQStr(iter->key().ToString()), StlToQBytes(iter->value().ToString()))) {
			suc = false;
			break;
		}
	}
	delete iter;
	return false;
}

QString TimerDb::LastError()
{
	return last_err_;
}

bool TimerDb::Open()
{
	leveldb::Options opts{};
	opts.create_if_missing = true;
	auto status = leveldb::DB::Open(opts, QStrToStl(BasicConfig::TimerDbSavePath), &db_);
	if (!status.ok()) {
		ShowErrorMsg("数据库打开失败, 错误原因: " + StlToQStr(status.ToString()), 1);
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

QJsonObject TimerDb::TimerItemStoreDataToJsonWithoutToday(const TimerItemStoreData& data)
{
	QJsonObject obj;

	obj["pn"] = data.proc_name;
	obj["ts"] = data.tags;
	obj["ss"] = data.status == kStatusPaused ? kStatusPaused : kStatusStanding;
	obj["tt"] = data.total_time;
	obj["hn"] = data.is_hidden ? 1 : 0;

	return obj;
}

TimerItemStoreData TimerDb::JsonToTimerItemStoreDataWithoutToday(const QJsonObject& obj)
{
	TimerItemStoreData data{};

	data.proc_name = obj["pn"].toString();
	data.tags = obj["ts"].toString();
	data.status = obj["ss"].toInt();
	data.total_time = obj["tt"].toInt();

	data.is_hidden = obj["hn"].toInt() == 0 ? false : true;

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

void TimerDb::DbBrokenError()
{
	last_err_ = "从数据库中读取计时器失败!\n原因: 数据库文件损坏!\n路径: " + BasicConfig::TimerDbSavePath;
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
	return fustd::Some(std::move(data));
}

fustd::Option<QList<TimerItemStoreData::DayTimer>> TimerDb::JsonToHistroySafed(const QJsonArray& arr)
{
	if (arr.isEmpty())
		return fustd::None();
	QList<TimerItemStoreData::DayTimer> total;
	for (auto& item : arr) {
		if (!item.isObject())
			return fustd::None();
		total.append(JsonToTimerItemStoreDataDayTimer(item.toObject()));
	}
	return fustd::Some(std::move(total));
}

fustd::Result<QJsonObject, leveldb::Status> TimerDb::ReadTimerJsonSafed(const QString& timer_name)
{
	std::string stlstr_tmp;
	auto status = db_->Get(leveldb::ReadOptions(), QStrToStl(timer_name), &stlstr_tmp);
	if (status.ok()) {
		auto doc = QJsonDocument::fromJson(StlToQBytes(stlstr_tmp));
		if (doc.isEmpty() || !doc.isObject()) {
			return fustd::Err(std::move(status));
		}
		return fustd::Ok(doc.object());
	}
	return fustd::Err(std::move(status));
}

leveldb::Status TimerDb::SaveTimerJsonSafed(const QString& timer_name, const QJsonObject& obj)
{
	return db_->Put(leveldb::WriteOptions(), QStrToStl(timer_name), QStrToStl(QJsonDocument(obj).toJson(QJsonDocument::Compact)));
}

leveldb::Status TimerDb::DelectTimerSafed(const QString& timer_name)
{
	return db_->Delete(leveldb::WriteOptions(), QStrToStl(timer_name));
}

fustd::Option<QJsonArray> TimerDb::GetHistroyJsonInJsonSafed(const QJsonObject& obj)
{
	if (obj.isEmpty())
		return fustd::None();
	auto arr = obj["his"].toArray();
	if (arr.isEmpty())
		return fustd::None();
	return fustd::Some(std::move(arr));
}

void TimerDb::SetLastErr(const QString& err)
{
	last_err_ = err;
}
