#include "mainwin.h"

MainWin::MainWin(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    timer_table_ = new TimerTableView(ui.central_widget);
    label_timer_info_ = new QLabel(ui.status_bar);
    ui.central_vertical_layout->addWidget(timer_table_);
    ui.status_bar->addWidget(label_timer_info_);

    connect(timer_table_->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWin::OnTimerTableSelectionChanged);
    connect(timer_table_, &QTableView::customContextMenuRequested, this, [this](const QPoint& pos) {
        QMenu menu{ timer_table_ };
        menu.addAction(ui.act_add_timer);
        menu.addAction(ui.act_del_timer);
        menu.exec(QCursor::pos());
        });

    TimerController::Instance->StartNeeded();
}

MainWin::~MainWin()
{}

void MainWin::on_act_add_timer_triggered()
{
    CreateTimerItemDlg dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        timer_table_->model_->InsertTimer(dlg.GetInfo());
    }
}

void MainWin::on_act_settings_triggered()
{
    
}

void MainWin::on_act_save_local_triggered()
{
    timer_table_->model_->SaveTimers();
    QMessageBox::information(this, "提示", "保存成功!");
}

void MainWin::on_act_del_timer_triggered()
{
}

void MainWin::OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    ui.act_del_timer->setEnabled(timer_table_->currentIndex().isValid());
    auto row = selected.indexes()[0].row();
    auto data = timer_table_->model_->GetTimerItemStoreData(row);
    auto timer_name = timer_table_->model_->item(row, kColumnTimerName)->text();
    QString format = "所选计时器: <b>%1</b>\t绑定的进程名: <b>%2</b>";
    label_timer_info_->setText(format.arg(timer_name).arg(data->proc_name));
}
