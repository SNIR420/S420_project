#include <QCoreApplication>
#include <modbus_srv.h>
#include <QDebug>

int main()
{

    Modbus_SRV*	monserveur = new Modbus_SRV( "S420-6-API.csv" ) ;
    qDebug() << monserveur->getPosazimut() ;

}

