#include "ihm.h"

#include <QApplication>
#include <QScreen>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHM w;
    w.show();
    return a.exec();
}
