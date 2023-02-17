#include "modbus_srv.h"

Modbus_SRV::Modbus_SRV(QObject *parent)
    : QObject{parent}
{
}

float Modbus_SRV::getPosazimut()
{
return GPosazimut;
}

float Modbus_SRV::getRoulis()
{
return GRoulis;
}

float Modbus_SRV::getTangage()
{
return GTangage;
}

float Modbus_SRV::getVitazimut()
{
return GVitAzimut;
}

float Modbus_SRV::getHautvague()
{
return GHautvague;
}

float Modbus_SRV::getIntervague()
{
return GIntervague;
}

float Modbus_SRV::getTws()
{
return GTws;
}

float Modbus_SRV::getVitvague()
{
return GVitvague;
}

float Modbus_SRV::getSwa()
{
return GSwa;
}

void Modbus_SRV::setHautvague( float SHautVague)
{
GHautvague=SHautVague;
}

void Modbus_SRV::setIntervague(float SInterVague)
{
GIntervague=SInterVague;
}

void Modbus_SRV::setPosazimut(float SPosAzimut)
{
GPosazimut=SPosAzimut;
}

void Modbus_SRV::setRoulis(float SRouLis)
{
 GRoulis = SRouLis;
}

void Modbus_SRV::setTangage(float STanGage)
{
GTangage=STanGage;
}

void Modbus_SRV::setTws(float STws)
{
GTws=STws;
}

void Modbus_SRV::setVitazimut(float SVitAzimut)
{
GVitAzimut=SVitAzimut;
}

void Modbus_SRV::setVitvague(float SVitVague)
{
GVitvague=SVitVague;
}

void Modbus_SRV::setSwa(float SSwa)
{
GSwa=SSwa;
}
