#include "create_timer_item_dlg.h"

CreateTimerItemDlg::CreateTimerItemDlg(QWidget* parent):
	QDialog(parent),
	is_pessing_(false),
	prev_hwnd_(nullptr)
{
	ui.setupUi(this);
	setMouseTracking(true);
	aim_icon_ = ui.btn_aim_process->icon();
}

CreateTimerItemDlg::~CreateTimerItemDlg()
{
}

TimerItemBasicInfo CreateTimerItemDlg::GetInfo()
{
	TimerItemBasicInfo info{};
	info.timer_name = ui.edit_timer_name->text().trimmed();
	info.proc_name = ui.edit_proc_name->text().trimmed();
	info.tags = ui.edit_tags->text().trimmed();
	info.start_imm = ui.chk_start_imm->isChecked();
	info.julian_data = QDate::currentDate().toJulianDay();
	return info;
}

void CreateTimerItemDlg::mouseReleaseEvent(QMouseEvent* event)
{
	EndScan();
}

void CreateTimerItemDlg::mouseMoveEvent(QMouseEvent* event)
{
	if (is_pessing_) {
		POINT point;
		GetCursorPos(&point);
		HWND hWnd = ::WindowFromPoint(point);
		if (!prev_hwnd_) {
			DrawWindowBorder(hWnd);
			prev_hwnd_ = hWnd;
			SetProcName(hWnd);
		}
		if (prev_hwnd_ != hWnd) {
			DrawWindowBorder(prev_hwnd_);
			DrawWindowBorder(hWnd);
			prev_hwnd_ = hWnd;
			SetProcName(hWnd);
		}
	}
}

void CreateTimerItemDlg::SetProcName(HWND hwnd)
{
	char buf[MAX_PATH];
	DWORD pid;
	GetWindowThreadProcessId(hwnd, &pid);
	HANDLE hprocess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pid);
	if (hprocess) {
		DWORD size = MAX_PATH;
		if (QueryFullProcessImageNameA(hprocess, 0, buf, &size)) {
			ui.edit_proc_name->setText(buf);
			return;
		}
	}
	ui.edit_proc_name->setText("自动获取进程名失败!");
}

void CreateTimerItemDlg::BeginScan()
{
	QApplication::setOverrideCursor(QCursor(QPixmap(":/pictures/aim.cur")));
	is_pessing_ = true;
	ui.btn_aim_process->setIcon(QIcon());
}

void CreateTimerItemDlg::EndScan()
{
	QApplication::restoreOverrideCursor();
	is_pessing_ = false;
	ui.btn_aim_process->setIcon(aim_icon_);
	if (prev_hwnd_) {
		DrawWindowBorder(prev_hwnd_);
		prev_hwnd_ = nullptr;
	}
}

void CreateTimerItemDlg::on_btn_aim_process_pressed()
{
	BeginScan();
}

void CreateTimerItemDlg::on_btn_ok_clicked()
{
	if (ui.edit_timer_name->text().trimmed().isEmpty() ||
		ui.edit_proc_name->text().trimmed().isEmpty() ||
		ui.edit_tags->text().trimmed().isEmpty()
		)
	{
		QMessageBox::warning(this, "警告", "您还有项没填写!");
	}
	else if (QMessageBox::question(this, "询问", "你确定要创建吗, [要绑定的进程名称]一经创建无法修改!\n并且计时器无法被删除, 新计时器也会立即存入缓存, 无法撤销!") == QMessageBox::Yes) {
		accept();
	}
}