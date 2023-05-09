#include "modbus_srv.h"
#include <QDebug>

Modbus_SRV::Modbus_SRV(const QString& configFile, QObject* parent )
    : QObject{parent}
    , m_configFile(configFile)
{
    // cartographie Modbus
    m_map    = new QamModbusMap( QamModbusMap::ServerMode, this ) ;
    m_map->setVerbose( false ) ;
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
    return m_map->value(m_table, "lect-roulis").toFloat();
}

float Modbus_SRV::getTangage()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "lect-tangage").toFloat();
}

float Modbus_SRV::getVitazimut()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "lect-vitazimut").toFloat();
}

float Modbus_SRV::getHautvague()
{
    return GHautvague;
}

float Modbus_SRV::getBom()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "lect-bome").toFloat();
}

float Modbus_SRV::getIntervague()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "cons-intervague").toFloat();
}

float Modbus_SRV::getTws()
{
    return GTws;
}

float Modbus_SRV::getTwa()
{
    return GTwa;
}
float Modbus_SRV::getVitvague()
{
    return GVitvague;
}

float Modbus_SRV::getSwa()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "cons-swa").toFloat();
}

void Modbus_SRV::setBom(int SBom)
{
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(SBom);
    m_map->setValue(m_table, "lect-bome", value);
}

void Modbus_SRV::setTwa(int STwa)
{
    GTwa=STwa;
}

void Modbus_SRV::setHautvague( float SHautVague)
{
    GHautvague=SHautVague;
}

void Modbus_SRV::setIntervague(float SInterVague)
{
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(SInterVague);
    m_map->setValue(m_table, "cons-intervague", value);
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
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(STanGage);
    m_map->setValue(m_table, "lect-tangage", value);
}

void Modbus_SRV::setTws(float STws)
{
    GTws=STws;
}

void Modbus_SRV::setVitazimut(float SVitAzimut)
{
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(SVitAzimut);
    m_map->setValue(m_table, "lect-vitazimut", value);
}

void Modbus_SRV::setVitvague(float SVitVague)
{
    GVitvague=SVitVague;
}

void Modbus_SRV::setSwa(int SSwa)
{
    m_table = QamModbusMap::HoldingRegister ;
    QString value = QString::number(SSwa);
    m_map->setValue(m_table, "cons-swa", value);
}

void Modbus_SRV::info(const QString& src, const QString& msg )
{
    qDebug() << qPrintable( src ) << ": " << qPrintable( msg )  ;
}

int Modbus_SRV::getClientConnected(){
    return m_server->getClientConnected();
}
