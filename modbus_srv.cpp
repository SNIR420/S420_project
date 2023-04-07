#include "modbus_srv.h"
#include <QTcpSocket>
#include <QDebug>

Modbus_SRV::Modbus_SRV(const QString& configFile, QObject* parent )
    : QObject{parent}
    , m_configFile(configFile)
{
    // cartographie Modbus
    m_map    = new QamModbusMap(QamModbusMap::ServerMode, this ) ;
    m_map->setVerbose(false) ;
    connect( m_map, SIGNAL(info(QString,QString)), this, SLOT(info(QString,QString)) ) ;
    m_map->loadMap( configFile ) ;

    // server TCP

    m_server = new QamTcpServer( m_map, this ) ;
    m_server->start(502);
}

float Modbus_SRV::getPosazimut()
{
    return GPosazimut;
}

float Modbus_SRV::getRoulis(){
    m_table = QamModbusMap::HoldingRegister ;
    QString res = m_map->value(m_table, "lect-roulis");
    return res.toFloat();
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
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(SRouLis);
    m_map->setValue(m_table, "lect-roulis", value);
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

void Modbus_SRV::setSwa(int SSwa)
{
    GSwa=SSwa;
}

int Modbus_SRV::getClientConnected(){
    return m_server->getClientConnected();
}

void Modbus_SRV::info(const QString& src, const QString& msg )
{
    qDebug() << qPrintable( src ) << ": " << qPrintable( msg )  ;
}

