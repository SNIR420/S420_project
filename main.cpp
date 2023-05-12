#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include "polaire.h"
int main(int argc, char *argv[])
{
    Polaire polaire_test("C:/Users/PC/Documents/GitHub/S420_project/Class40.pol");
    qDebug() << "Test" <<polaire_test.getMaxSpeed(102, 15);
    qDebug() << "Test2" <<polaire_test.getMaxSpeed(103, 12);
    qDebug() << "vitesseMax:" <<polaire_test.getAbsoluteMaxSpeed();
    qDebug() << "gite:" <<polaire_test.getMaxGite(122, 17);
    qDebug() << "giteRatio:" <<polaire_test.getGiteRatio(122, 17, 0.7);
}
