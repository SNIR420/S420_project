#include <QCoreApplication>
#include <modbus_srv.h>
#include <QDebug>
int main(int argc, char *argv[])
{
    Modbus_SRV monserveur;
    monserveur.setPosazimut(45);
    qDebug() << monserveur.getPosazimut() ;

}
