#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H


class modbusserver
{
public:
    modbusserver();
    void stopServer();
    float getVitazimut();
    float getRoulis();
    float getTangage();
    float getPosazimut();
    void setHautvague();
    void setVitvague();
    void setIntervague();
    void setRoulis();
    void setTangage();
    void setVitazimut();
    void setTws();
    void setPosazimut();
private:

};

#endif // MODBUSSERVER_H
