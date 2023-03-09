
#ifndef POLAIRE_H
#define POLAIRE_H

#include <QObject>

class Polaire : public QObject
{
private:
    Polaire(){}
    Q_OBJECT
public:
    explicit Polaire(QObject *parent = nullptr);
    Polaire(QObject polFilePath);
    double getSpeedRatio(double twa, double tws, double ratio);
    double getMaxSpeed(double twa, double tws);
    double getGiteRatio(double twa, double tws, double ratio);
    double getMaxRatio(double twa, double tws);

signals:

};

#endif // POLAIRE_H
