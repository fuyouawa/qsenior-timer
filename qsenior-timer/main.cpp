#include "frame/mainwin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    TimerDb::Instance->Open();

    QApplication a(argc, argv);
    InitBasicConfig();
    ReadSettings();
    int res = 0;
    {
        MainWin w;
        w.show();
        res = a.exec();
    }

    TimerDb::Instance->Close();
    return res;
}
