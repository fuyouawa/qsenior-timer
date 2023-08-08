#pragma once

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QtEasyLib/QEasyEventSystem>
#include "ui_mainwin.h"
#include "view/timer_table_view.h"
#include "global/event_types.h"
#include "global/focus_detector.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget* parent = nullptr);
    ~MainWin();

private slots:
    void on_act_del_timer_triggered();
    void on_act_add_timer_triggered();

private:
    Ui::MainWin ui;
    TimerTableView* timer_table_;
    void OnTimerTableSelectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
};
