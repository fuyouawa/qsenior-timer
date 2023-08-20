#include "frame/loginwin.h"
#include <QSharedMemory>
#include <QSystemSemaphore>
#include "frame/connect_server_win.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSystemSemaphore semaphore{ "QSystemSemaphore\\QTimerCloud\\SingleApp", 1 };
    semaphore.acquire();

    QSharedMemory shared_memory("QSharedMemory\\QTimerCloud\\SingleApp");
    bool is_running = false;
    if (shared_memory.attach()) {
        is_running = true;
    }
    else {
        shared_memory.create(1);
        is_running = false;
    }

    semaphore.release();

    if (is_running) {
        return -1;
    }

    InitBasicConfig(argv);
    ReadUserInfo();
    LoginWin* login_win = nullptr;
    ConnectServerWin* connect_server_win = nullptr;
    if (UserInfo::UserName.isEmpty()) {
        login_win = new LoginWin();
        login_win->show();
    }
    else {
        connect_server_win = new ConnectServerWin();
        connect_server_win->show();
    }
    auto res = a.exec();
    return res;
}
