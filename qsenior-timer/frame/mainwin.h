#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include "ui_mainwin.h"
#include "view/timer_table_view.h"
#include "global/event_types.h"
#include "global/timer_controller.h"
#include "frame/settingsdlg.h"
#include "frame/create_timer_item_dlg.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget* parent = nullptr);
    ~MainWin();

private slots:
    void on_act_del_timer_triggered();
    void on_act_add_timer_triggered();
    void on_act_settings_triggered();
    void on_act_save_local_triggered();

    void OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

private:
    Ui::MainWin ui;
    TimerTableView* timer_table_;
    QLabel* label_timer_info_;
};
