#pragma once

#include <QtWidgets/QMainWindow>
#include <QJsonObject>
#include <QMessageBox>
#include "ui_mainwin.h"
#include "global/event_types.h"
#include "global/utils.h"

class MainWin : public QMainWindow, QEasyEventHandler<ResponsedEvent>, QEasyEventHandler<ConnectedToServerEvent>
{
    Q_OBJECT

public:
    inline static MainWin* Instance = nullptr;

    MainWin(QWidget* parent = nullptr);
    ~MainWin();

private slots:
    void on_btn_view_pwd_clicked(bool checked);

private:
    void OnEvent(const ResponsedEvent& event) override;
    void OnEvent(const ConnectedToServerEvent& event) override;

    Ui::MainWinClass ui;
};
