#ifndef POLAIRE_H
#define POLAIRE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

class Polaire : public QObject
{
    Q_OBJECT
private:
    Polaire(){}
    QString m_polFilePath;
    QVector<QVector<double>> m_polaireData;
    double vitesseMax = 0.0;
    //TODO Vitesse Max a recuperer dans le constructeur
public:
    explicit Polaire(QObject *parent = nullptr);
    Polaire(QString polFilePath);
    double getSpeedRatio(double twa, double tws, double ratio);
    double getMaxSpeed(double twa, double tws);
    double getGiteRatio(double twa, double tws, double ratio);
    double getMaxGite(double twa, double tws); // formule a appliquer
    double getAbsoluteMaxSpeed();


signals:

};

#endif // POLAIRE_H
