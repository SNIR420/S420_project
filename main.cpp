#include <QCoreApplication>
#include "simulateur.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    simulateur smltr(nullptr , "Class40.pol") ;
    return a.exec();
}
