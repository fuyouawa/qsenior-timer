#include "mainwin.h"

MainWin::MainWin(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    timer_table_ = new TimerTableView(ui.central_widget);
    ui.central_vertical_layout->addWidget(timer_table_);

    connect(timer_table_->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWin::OnTimerTableSelectionChanged);
    connect(timer_table_, &QTableView::customContextMenuRequested, this, [this](const QPoint& pos) {
        QMenu menu{ timer_table_ };
        menu.addAction(ui.act_add_timer);
        menu.addAction(ui.act_del_timer);
        menu.exec(QCursor::pos());
        });

    QTimer::singleShot(1000, [this]() {
        QEasyEventBus::Emit(SecondUpdateEvent());
        });

    FocusDetector::Instance->StartScanning();
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

void MainWin::on_act_del_timer_triggered()
{
}

void MainWin::OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    ui.act_del_timer->setEnabled(timer_table_->currentIndex().isValid());
}