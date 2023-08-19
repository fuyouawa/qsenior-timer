#pragma once

#include <QtWidgets/QMainWindow>
#include <QJsonObject>
#include <QMessageBox>
#include <QMenu>
#include "ui_mainwin.h"
#include "global/event_types.h"
#include "global/utils.h"
#include "global/client_manager.h"
#include "global/local_client.h"

class MainWin : public QMainWindow,
    qteasylib::EventHandler<ResponsedEvent>,
    qteasylib::EventHandler<ConnectedToServerEvent>,
    qteasylib::EventHandler<LocalServerResponsedEvent>,
    qteasylib::EventHandler<ConnectErrorEvent>
{
    Q_OBJECT

public:
    inline static MainWin* Instance = nullptr;
    inline static constexpr int kMaxBackups = 3;

    MainWin(qint64 registry_stamp, QWidget* parent = nullptr);
    ~MainWin();

private slots:
    void on_btn_view_pwd_clicked(bool checked);
    void on_btn_upload_saves_clicked();
    void on_btn_download_saves_clicked();

private:
    void OnEvent(const ResponsedEvent& event) override;
    void OnEvent(const ConnectedToServerEvent& event) override;
    void OnEvent(const LocalServerResponsedEvent& event) override;
    void OnEvent(const ConnectErrorEvent& event) override;

    void ErrorOccurred();
    void AppendLog(const QString& msg);

    bool is_upload_;

    Ui::MainWinClass ui;
};
