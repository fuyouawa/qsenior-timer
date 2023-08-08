#pragma once
#include <qstring.h>
#include <qrect.h>
#include <qvector.h>
#include <array>

enum TimerItemColumn
{
	kTimerItemColomnTimerName,
	kTimerItemColomnDuration,
	kTimerItemColomnStatus,
	kTimerItemColomnOperation
};

enum TimerItemDataColumn
{
	kTimerItemDataColomnProcessName,
	kTimerItemDataColomnFlags,
	kTimerItemDataColomnStatus,
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
	kTimerItemOperatorStart,
	kTimerItemOperatorShowMessage,
	kTimerItemOperatorHidden
};

struct TimerItemInfo
{
	QString timer_name;
	QString proc_name;
	bool can_del;
	bool can_pause;
	bool start_imm;
};

struct CustomButtonInfo {
	size_t column;
	size_t row;
	bool is_pressed;
	QRect rect;
};

inline const QStringList kTimerItemOperationsText = { "开始计时", "详细信息", "隐藏" };
inline const QStringList kTimerTableHorizontalHeaderLabels = { "计时器名称", "时间", "状态", "操作" };

inline constexpr char kFlagTimerItemCanDel = 0b0001;
inline constexpr char kFlagTimerItemCanPause = 0b0010;
inline constexpr char kFlagTimerItemStartImm = 0b0100;

class Settings
{
public:
	inline static int ScanFocusInter = 1;
};