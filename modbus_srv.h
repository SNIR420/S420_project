#ifndef MODBUS_SRV_H
#define MODBUS_SRV_H

#include <QObject>

class Modbus_SRV : public QObject
{
    Q_OBJECT
public:
    explicit Modbus_SRV(QObject *parent = nullptr);
    void stopServer();
    float getVitazimut( );
    float getRoulis();
    float getTangage( );
    float getPosazimut();
    float getHautvague();
    float getVitvague();
    float getIntervague();
    float getTws();
    int getSwa();
    void setHautvague( float SHautvague);
    void setVitvague(float SVitvague);
    void setIntervague(float SIntervague);
    void setRoulis(float SRoulis);
    void setTangage(float STangage);
    void setVitazimut(float SVitazimut);
    void setTws(float STws);
    void setPosazimut(float SPosazimut);
    void setSwa(float SSwa);
signals:

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
};

#endif // MODBUS_SRV_H
