#include <QtGui/QApplication>
#include "mainwindow.h"

#include "support/alarm.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}


void mtk::AlarmMsg(const mtk::Alarm &error)
{
    std::cout << error << std::endl;
}
