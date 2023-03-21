#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "polaire.h"
int main(int argc, char *argv[])
{
    Polaire polaire_test("/home/projetbateau/Documents/GitHub/S420_project/Class40.pol");
    qDebug() << "Test" <<polaire_test.getMaxSpeed(122, 17);
    qDebug() << "Goblin = J" <<polaire_test.getMaxSpeed(122, 17);

}
