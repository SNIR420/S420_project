#ifndef MODBUS_SRV_H
#define MODBUS_SRV_H

#include <QObject>
#include <QamModbusMap.h>
#include <qamtcpserver.h>

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
    void setHautvague( float SHautvague);
    void setVitvague(float SVitvague);
    void setIntervague(float SIntervague);
    void setRoulis(float SRoulis);
    void setTangage(float STangage);
    void setVitazimut(float SVitazimut);
    void setTws(float STws);
    void setPosazimut(float SPosazimut);
    void setSwa(int SSwa);

public slots:
    void info(const QString& src, const QString& msg ) ;

private:
    float GVitAzimut;
    float GRoulis;
    float GTangage;
    float GPosazimut;
    float GHautvague;
    float GVitvague;
    float GIntervague;
    float GTws;
    int GSwa;
    float SHautvague;
    float SVitvague;
    float SIntervague;
    float SRoulis;
    float STangage;
    float SVitazimut;
    float STws;
    float SPosazimut;
    int SSwa;
    QamModbusMap*				m_map ;
    QamModbusMap::PrimaryTable	m_table ;
    QamTcpServer*				m_server ;
    QString m_configFile;

};

#endif // MODBUS_SRV_H
