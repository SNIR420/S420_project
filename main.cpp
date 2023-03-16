#include "simulateur.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    simulateur smltr(nullptr , "Class40.pol") ;

    //w.show();
    return a.exec();
}
