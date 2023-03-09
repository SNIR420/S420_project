#include "ihm.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    IHM w;
    w.show();

    QRect availableScreenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    w.setGeometry(0, 0, availableScreenGeometry.width(), availableScreenGeometry.height());

    return a.exec();
}
