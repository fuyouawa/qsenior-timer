#pragma once

#include <QtWidgets/QMainWindow>
#include <QJsonObject>
#include <QMessageBox>
#include <QMenu>
#include "ui_mainwin.h"
#include "global/event_types.h"
#include "global/utils.h"
#include "global/socket_manager.h"
#include "global/local_client.h"

class MainWin : public QMainWindow,
    qteasylib::EventHandler<LocalServerResponsedEvent>
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

    void AppendLog(const QString& msg);
    void AppendErrLog(const QString& msg);

private:
    void OnEvent(const LocalServerResponsedEvent& event);

    void EnableSavesOperBtns(bool enable);

    SocketManager socket_;
    Ui::MainWinClass ui;
    QByteArray temp_;
    bool is_upload_;
};
