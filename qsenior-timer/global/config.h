#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qvector.h>
#include <QDir>
#include <QMainWindow>
#include <array>

inline const QString kAppVersion = "v1.0.0-beta";

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
	kStatusStanding,
	kStatusHangup
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
	kFlagNone,
	kFlagIsPreviousRunning
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
	bool is_hidden;
	int status;						// ss
	int total_time;					// tt
	DayTimer today;					// ty
};

inline const QStringList kTextTimerTableHorizontalHeader = { "计时器名称", "总使用时间", "标签", "状态", "" };
inline const QStringList kTextTimerItemStatus = { "暂停中", "计时中", "待命中", "挂机中"};

inline QMainWindow* MainWinPtr = nullptr;

class AppSettings
{
public:
	inline static bool Startup;
	inline static bool RunInTray;
	inline static bool AutoCloseSave;
	inline static bool AutoTimerSaveLocal;
	inline static bool AutoCheckUpdate;
	inline static bool ScanHangup;

	inline static int SaveLocalInter;
	inline static int ScanFocusInter;
	inline static int HangupJudgeTime;

	inline static int ErrLevel;
};

class BasicConfig {
public:
	inline static QString SettingsSavePath;
	inline static QString TimerDbSavePath;
	inline static QString TempFilePath;
	inline static QString AppDataDir;

	inline static bool IsFirstRunApp;
};


class ViewSettings
{
public:
	inline static TimerTableHeaderTimeCounterViewModel TimeCounterModel;
};