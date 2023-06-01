#ifndef MODBUS_SRV_H
#define MODBUS_SRV_H

#include <QObject>
#include "qammodbusmap.h"
#include "qamtcpserver.h"

class Modbus_SRV : public QObject
{
    Q_OBJECT
public:
    explicit Modbus_SRV(const QString& configFile, QObject* parent = nullptr) ;
    void stopServer();
    float getVitazimut();
    float getRoulis();
    float getTangage();
    float getPosazimut();
    float getHautvague();
    float getVitvague();
    float getIntervague();
    float getTws();
    float getSwa();
    float getTwa();
    float getBom();
    float getSafran();
    float getSpeed();
    float getBomError();
    void setHautvague( float SHautvague);
    void setVitvague(float SVitvague);
    void setIntervague(float SIntervague);
    void setRoulis(float SRoulis);
    void setTangage(float STangage);
    void setVitazimut(float SVitazimut);
    void setTws(float STws);
    void setPosazimut(float SPosazimut);
    void setSwa(int SSwa);
    void setTwa(int STwa);
    void setBom(int SBom);
    void setSpeed(float SSpeed);
    int getClientConnected();

public slots:
    void info(const QString& src, const QString& msg ) ;

private:
    float GVitAzimut;
    float GTangage;
    float GPosazimut;
    float GHautvague;
    float GVitvague;
    float GIntervague;
    float GTws;
    float GSpeed;
    int GSwa;
    int GTwa;
    int GBom;
    QamModbusMap*				m_map ;
    QamModbusMap::PrimaryTable	m_table ;
    QamTcpServer*				m_server ;
    QString m_configFile;
};

#endif // MODBUS_SRV_H
