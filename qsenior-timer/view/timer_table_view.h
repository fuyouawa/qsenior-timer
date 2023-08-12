#pragma once
#include <qtableview.h>
#include <qstandarditemmodel.h>
#include <QAction>
#include <qmenu.h>
#include <qcursor.h>
#include "timer_table_header_view.h"
#include "delegate/timer_item_delegrate.h"
#include "model/timer_table_model.h"
#include "global/config.h"
#include "frame/timer_info_dlg.h"
#include "frame/edit_timer_dlg.h"

class TimerTableView : public QTableView
{
	Q_OBJECT

public:
	TimerTableView(QWidget* parent);
	~TimerTableView();

	TimerTableModel* Model() const;

private slots:
	void OnOperBtnClicked(int row);
	void OnViewTimerDetails();
	void OnHideTimer();
	void OnEditTimer();
	void OnControlTimer();

private:
	TimerTableHeaderView* hori_header_view_;
	TimerTableModel* model_;
	QAction* act_view_details_;
	QAction* act_hidden_;
	QAction* act_edit_;
	QAction* act_control_;

	int oper_btn_clicked_row_;
};
