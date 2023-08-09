#include "frame/mainwin.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ReadSettings();
    MainWin w;
    w.show();
    return a.exec();
}
