#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qvector.h>
#include <QDir>
#include <array>

enum TimerTableColumn
{
	kColumnTimerName,
	kColumnTimeCounter,
	kColumnTags,
	kColumnStatus,
	kColumnOperations
};

enum TimerItemDataColumn
{
	kDataStore,
	kDataTags
};

enum TimerItemStatus
{
	kStatusPaused,
	kStatusRunning,
	kStatusStanding
};

enum TimerItemOperIndex
{
	kOperIndexTimer,
	kOperIndexShowMessage,
	kOperIndexHidden
};

enum TimerTableHeaderOperatorIndex
{
	kOperIndexCutNameMode,
	kOperIndexFilterName,
	kOperIndexCutTimeCounterMode,
	kOperIndexFilterTimeCount,
	kOperIndexFilterStatus
};

enum TimerItemFlags
{
	kFlagCanDel = 0b0001,
	kFlagCanPause = 0b0010,
	kFlagCanEdit = 0b0100,
	kFlagIsHidden = 0b1000
};

enum TimerItemTags
{
	kTagNone,
	kTagIsPreviousRunning
};

enum TimerTableHeaderTimeCounterViewModel
{
	kViewModelTotalTime,
	kViewModelTodayTime,
	kViewModelTodayContinuous
};

struct TimerItemBasicInfo
{
	QString timer_name;
	QString proc_name;
	QString tags;
	bool can_del;
	bool can_pause;
	bool can_edit;
	bool start_imm;
	qint64 julian_data;
};

struct TimerItemStoreData
{
	struct DayTimer {
		qint64 julian_date;			// jd
		qint64 day_time;			// dt
		qint64 last_continuous;		// lcs
		qint64 max_continuous;		// mcs
	};
	QString proc_name;				// pn
	QString tags;					// ts
	bool can_del;					// fs
	bool can_pause;
	bool can_edit;
	bool is_hidden;
	int status;						// ss
	int total_time;					// tt
	DayTimer today;					// ty
};

inline const QStringList kTextTimerItemOperations = { "定时", "详细", "隐藏" };
inline const QStringList kTextTimerTableHorizontalHeader = { "计时器名称", "总时间", "标签", "状态", "操作" };
inline const QStringList kTextTimerItemStatus = { "暂停中", "计时中", "待命中" };

class AppSettings
{
public:
	inline static bool Startup;
	inline static bool RunInBg;
	inline static bool AutoCloseSave;
	inline static bool TimerSaveLocal;
	inline static bool AutoCheckUpdate;

	inline static int AutoSaveLocalInter;
	inline static int ScanFocusInter;

	inline static int ErrLevel;
};

class BasicConfig {
public:
	inline static QString SettingsSavePath;
	inline static QString TimerDbSavePath;
	inline static QString AppDataDir;
};


class ViewSettings
{
public:
	inline static TimerTableHeaderTimeCounterViewModel TimeCounterModel;
};