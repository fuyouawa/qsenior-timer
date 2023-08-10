#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qvector.h>
#include <QDir>
#include <array>

enum TimerTableColumn
{
	kTimerTableColomnTimerName,
	kTimerTableColomnTimeCounter,
	kTimerTableColomnTags,
	kTimerTableColomnStatus,
	kTimerTableColomnOperation
};

enum TimerItemDataColumn
{
	kTimerItemDataColumnStoreData,
	kTimerItemDataColumnTags
};

enum TimerItemStatus
{
	kTimerItemStatusPaused,
	kTimerItemStatusRunning,
	kTimerItemStatusStanding
};

enum TimerItemOperatorIndex
{
	kTimerItemOperatorTimer,
	kTimerItemOperatorShowMessage,
	kTimerItemOperatorHidden
};

enum TimerTableHeaderOperatorIndex
{
	kTimerTableHeaderOperatorCutNameMode,
	kTimerTableHeaderOperatorFilterName,
	kTimerTableHeaderOperatorCutTimeCounterMode,
	kTimerTableHeaderOperatorFilterTimeCount,
	kTimerTableHeaderOperatorFilterStatus
};

enum TimerItemFlags
{
	kTimerItemFlagCanDel = 0b0001,
	kTimerItemFlagCanPause = 0b0010,
	kTimerItemFlagCanEdit = 0b0100,
	kTimerItemFlagIsHidden = 0b1000
};

enum TimerItemTags
{
	kTimerItemTagNone,
	kTimerItemTagIsPreviousRunning
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
};

struct TimerItemStoreData
{
	struct DayTimer {
		qint64 run_stamp;			// rs
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