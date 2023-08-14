#include "mainwin.h"

MainWin::MainWin(QWidget* parent)
    : QMainWindow(parent),
    show_check_update_msg_(true)
{
    ui.setupUi(this);

    InitTray();

    timer_table_ = new TimerTableView(ui.central_widget);
    label_timer_info_ = new QLabel(ui.status_bar);
    ui.central_vertical_layout->addWidget(timer_table_);
    ui.status_bar->addWidget(label_timer_info_);

    connect(timer_table_->selectionModel(), &QItemSelectionModel::selectionChanged, this, &MainWin::OnTimerTableSelectionChanged);
    connect(timer_table_, &QTableView::customContextMenuRequested, this, [this](const QPoint& pos) {
        QMenu menu{ timer_table_ };
        menu.addAction(ui.act_add_timer);
        menu.exec(QCursor::pos());
        });

    TimerController::Instance->AutoStartOrClose();

#ifndef _DEBUG
    CheckUpdate(false);
#endif // !_DEBUG
}

MainWin::~MainWin()
{
}

void MainWin::CheckUpdate(bool show_msg)
{
    show_check_update_msg_ = show_msg;
    QNetworkAccessManager* manager = new QNetworkAccessManager(this);

    connect(manager, &QNetworkAccessManager::finished, this, &MainWin::OnUpdateCheckFinished);

    manager->get(QNetworkRequest(QUrl("https://api.github.com/repos/fuyouawa/qsenior-timer/releases/latest")));
}

void MainWin::OnUpdateCheckFinished(QNetworkReply* reply)
{
    if (reply->error() != QNetworkReply::NoError) {
        if (show_check_update_msg_) {
            ShowErrorMsg("版本更新检查失败!\n原因: " + reply->errorString(), 1, this);
        }
        return;
    }
    auto response_data = reply->readAll();
    auto doc = QJsonDocument::fromJson(response_data);
    auto obj = doc.object();

    QString latest_version = obj["tag_name"].toString();
    if (latest_version != kAppVersion) {
        if (QMessageBox::question(this, "提示", "发现新的版本! 是否前往下载页面?") == QMessageBox::Yes) {
            QDesktopServices::openUrl(QUrl("https://github.com/fuyouawa/qsenior-timer/releases/latest"));
        }
    }
    else {
        if (show_check_update_msg_) {
            QMessageBox::information(this, "提示", "当前已是最新版本!");
        }
    }

    reply->deleteLater();
}

void MainWin::closeEvent(QCloseEvent* event)
{
    if (QSystemTrayIcon::isSystemTrayAvailable() && AppSettings::RunInTray) {
        if (tray_icon_->isVisible()) {
            hide();
            event->ignore();
        }
    }
    else {
        event->accept();
    }
}

void MainWin::on_act_add_timer_triggered()
{
    CreateTimerItemDlg dlg{ this };
    if (dlg.exec() == QDialog::Accepted) {
        auto info = dlg.GetInfo();
        TimerItemStoreData tmp{};
        tmp.is_hidden = false;
        tmp.proc_name = info.proc_name;
        tmp.status = info.start_imm ? kStatusStanding : kStatusPaused;
        tmp.tags = info.tags;
        tmp.today.julian_date = info.julian_data;
        timer_table_->Model()->InsertTimer(info.timer_name, tmp);
        if (!TimerDb::Instance->SaveData(info.timer_name, tmp)) {
            ShowErrorMsg(TimerDb::Instance->LastError(), 1, this);
            ShowErrorMsg("新计时器保存失败!", 1, this);
        }
    }
}

void MainWin::on_act_settings_triggered()
{
    SettingsDlg dlg{ this };
    dlg.exec();
}

void MainWin::on_act_save_local_triggered()
{
    
    if (timer_table_->Model()->SaveTimers()) {
        QMessageBox::information(this, "提示", "保存成功!");
    }
}

void MainWin::on_act_check_update_triggered()
{
    CheckUpdate(true);
}

void MainWin::on_act_cloud_store_triggered()
{

}

void MainWin::OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected)
{
    auto row = selected.indexes()[0].row();
    auto data = timer_table_->Model()->GetTimerItemStoreData(row);
    auto timer_name = timer_table_->Model()->item(row, kColumnTimerName)->text();
    QString format = "所选计时器: <b>%1</b>\t绑定的进程名: <b>%2</b>";
    label_timer_info_->setText(format.arg(timer_name).arg(data->proc_name));
}

void MainWin::InitTray()
{
    if (QSystemTrayIcon::isSystemTrayAvailable())
    {
        tray_icon_ = new QSystemTrayIcon(this);
        tray_icon_->setIcon(windowIcon());
        tray_icon_->setToolTip("QSeniorTimer");

        auto tray_menu = new QMenu();
        auto show_active = new QAction("显示窗口", this);
        auto quit_active = new QAction("退出程序", this);

        connect(show_active, &QAction::triggered, this, &MainWin::show);
        connect(quit_active, &QAction::triggered, qApp, &QApplication::quit);

        tray_menu->addAction(show_active);
        tray_menu->addAction(quit_active);

        tray_icon_->setContextMenu(tray_menu);

        tray_icon_->show();

        connect(tray_icon_, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason) {
            switch (reason)
            {
            case QSystemTrayIcon::Unknown:
                break;
            case QSystemTrayIcon::Context:
                break;
            case QSystemTrayIcon::DoubleClick:
                showNormal();
                break;
            case QSystemTrayIcon::Trigger:
                break;
            case QSystemTrayIcon::MiddleClick:
                break;
            default:
                break;
            }
            });
    }
}
