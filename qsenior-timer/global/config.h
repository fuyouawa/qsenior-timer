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
	kTimerTableColomnStatus,
	kTimerTableColomnOperation
};

enum TimerItemDataColumn
{
	kTimerItemDataColumnInfo,
	kTimerItemDataColumnTags
};

enum TimerItemStatus
{
	kTimerItemStatusInit,
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
	kTimerItemFlagNone = 0,
	kTimerItemFlagCanDel = 0b0001,
	kTimerItemFlagCanPause = 0b0010,
	kTimerItemFlagCanEdit = 0b0100,
	kTimerItemFlagStartImm = 0b1000
};

enum TimerItemTags
{
	kTimerItemTagNone,
	kTimerItemTagIsPreviousRunning
};

struct TimerItemInfo
{
	QString timer_name;
	QString proc_name;
	int status;
	bool can_del;
	bool can_pause;
	bool can_edit;
	bool start_imm;
	struct {
		int total;
		int today;
		int continuous;
		int max_continuous;
	} time;
};

inline const QStringList kTimerItemOperationsText = { "定时", "详细", "隐藏" };
inline const QStringList kTimerTableHorizontalHeaderLabels = { "计时器名称", "总时间", "状态", "操作" };
inline const QStringList kTimerItemStatusText = { "初始化中", "暂停中", "计时中", "待命中" };

inline static const char* kSettingsFileName = "settings.ini";
inline static const char* kDbConfigJsonFileName = "config.json";
inline static const char* kDbConfigDirName = "db";

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

	inline static QString DbSaveDir;
};