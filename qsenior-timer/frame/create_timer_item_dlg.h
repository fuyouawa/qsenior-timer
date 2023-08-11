#pragma once
#include <qdialog.h>
#include <qmessagebox.h>
#include <QMouseEvent>
#include <QCursor>
#include "ui_create_timer_item_dlg.h"
#include "global/utils.h"

class CreateTimerItemDlg : public QDialog
{
	Q_OBJECT

public:
	CreateTimerItemDlg(QWidget* parent);
	~CreateTimerItemDlg();

	TimerItemBasicInfo GetInfo();

protected:
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

private:
	void SetProcName(HWND hwnd);
	void BeginScan();
	void EndScan();
	HWND prev_hwnd_;
	bool is_pessing_;
	QIcon aim_icon_;
	Ui::CreateTimerItemDlgClass ui;

private slots:
	void on_btn_ok_clicked();
	void on_btn_aim_process_pressed();
};