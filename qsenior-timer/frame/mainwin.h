#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <QProcess>
#include "ui_mainwin.h"
#include "view/timer_table_view.h"
#include "global/event_types.h"
#include "global/timer_controller.h"
#include "frame/settingsdlg.h"
#include "frame/create_timer_item_dlg.h"
#include "global/local_server.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget* parent = nullptr);
    ~MainWin();

    void CheckUpdate(bool show_msg);

protected:
    void closeEvent(QCloseEvent* event) override;

private slots:
    void on_act_add_timer_triggered();
    void on_act_settings_triggered();
    void on_act_save_local_triggered();
    void on_act_check_update_triggered();
    void on_act_cloud_store_triggered();

    void OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
    void OnUpdateCheckFinished(QNetworkReply* reply);

private:
    void InitTray();

    Ui::MainWinClass ui;
    TimerTableView* timer_table_;
    QLabel* label_timer_info_;
    QSystemTrayIcon* tray_icon_;

    bool show_check_update_msg_;
};
