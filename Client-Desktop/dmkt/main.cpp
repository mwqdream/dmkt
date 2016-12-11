#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setWindowFlags(Qt::FramelessWindowHint|Qt::WindowStaysOnTopHint);
    w.setAttribute(Qt::WA_TranslucentBackground,true);
    w.show();

    //test driverlist of sql
    qDebug()<<"Available drivers:";
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString driver,drivers)
    {
        qDebug()<<driver;
    }

    return a.exec();
}
