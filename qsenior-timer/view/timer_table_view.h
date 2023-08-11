#pragma once
#include <qtableview.h>
#include <qstandarditemmodel.h>
#include <qmenu.h>
#include <qcursor.h>
#include "timer_table_header_view.h"
#include "delegate/timer_item_delegrate.h"
#include "model/timer_table_model.h"
#include "global/config.h"

class TimerTableView : public QTableView
{
	Q_OBJECT

public:
	TimerTableView(QWidget* parent);
	~TimerTableView();

	TimerTableModel* model_;

private slots:
	void OnOperBtnClicked(int row, TimerItemOperIndex oper_idx);
};
