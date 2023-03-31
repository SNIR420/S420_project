#include "modbus_srv.h"
#include "qamtcpserver.h"
#include <QDebug>

Modbus_SRV::Modbus_SRV(const QString& configFile, QObject* parent )
    : QObject{parent}
{
    // cartographie Modbus
    m_configfile = configFile;
    m_map    = new QamModbusMap( QamModbusMap::ServerMode, this ) ;
    m_map->setVerbose( false ) ;
    connect( m_map, SIGNAL(info(QString,QString)), this, SLOT(info(QString,QString)) ) ;
    m_map->loadMap( configFile ) ;

    // server TCP

    m_server = new QamTcpServer( m_map, this ) ;
    m_server->start(502);

    // exemples de lecture de registres

    QString res ;

    qDebug() << "lecture de : lect-roulis,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "lect-roulis" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : lect-tangage,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "lect-tangage" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : lect-bome,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "lect-bome" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : lect-vitazimut,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "lect-vitazimut" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : cons-hautvague,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "cons-hautvague" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : cons-intervague,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "cons-intervague" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : cons-vitvague,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "cons-vitvague" ) ;
    qDebug() << res.toFloat()  ;

    qDebug() << "lecture de : cons-tws,  type : Float <-- " ;
    m_table = QamModbusMap::HoldingRegister ;
    res = m_map->remoteValue(m_table, "cons-tws" ) ;
    qDebug() << res.toFloat()  ;
    // exemples d'écriture de registres


    qDebug() << "écriture de : cons-hautvague,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-hautvague", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-hautvague").toFloat()  ;

    qDebug() << "écriture de : cons-vitvague,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-vitvague", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-vitvague").toFloat() ;

    qDebug() << "écriture de : cons-intervague,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(6) ;
    m_map->setRemoteValue(m_table, "cons-intervague", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-intervague").toFloat()  ;

    qDebug() << "écriture de : cons-roulis,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-roulis", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-roulis").toFloat()  ;

    qDebug() << "écriture de : cons-tangage,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-tangage", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-tangage").toFloat()  ;

    qDebug() << "écriture de : cons-vitazimut,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-vitazimut", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-vitazimut").toFloat()  ;

    qDebug() << "écriture de : cons-tws,  type : Float --> " ;
    m_table = QamModbusMap::HoldingRegister ;
    res.setNum(3) ;
    m_map->setRemoteValue(m_table, "cons-tws", res ) ;
    qDebug() << m_map->localValue(m_table, "cons-tws").toFloat()  ;


    qDebug() << "Ctrl-C to quit..."  ;

}

float Modbus_SRV::getPosazimut()
{
return GPosazimut;
}

float Modbus_SRV::getRoulis()
{
    m_table = QamModbusMap::HoldingRegister ;
    return m_map->value(m_table, "cons-roulis").toFloat();
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
    m_map->setValue(m_table, "cons-roulis", value);
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
void Modbus_SRV::info(const QString& src, const QString& msg )
{
    qDebug() << qPrintable( src ) << ": " << qPrintable( msg )  ;
}

