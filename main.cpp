#include "widget.h"
#include <QtDebug>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    QStringList drivers=QSqlDatabase::drivers();
    foreach(QString drive,drivers){
        qDebug()<<drive;
    }
    return a.exec();
}
