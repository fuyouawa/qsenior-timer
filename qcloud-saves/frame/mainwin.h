#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_mainwin.h"
#include "global/utils.h"

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

private:
    Ui::MainWinClass ui;
};
