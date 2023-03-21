  #ifndef POLAIRE_H
#define POLAIRE_H

#include <QObject>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

class Polaire : public QObject
{
private:
    Polaire(){}
    QString m_polFilePath;
    QVector<QVector<double>> m_polaireData;
    Q_OBJECT
public:
    explicit Polaire(QObject *parent = nullptr);
    Polaire(QString polFilePath);
    double getSpeedRatio(double twa, double tws, double ratio);
    double getMaxSpeed(double twa, double tws);
    double getGiteRatio(double twa, double tws, double ratio);
    double getMaxRatio(double twa, double tws);

signals:

};

#endif // POLAIRE_H
