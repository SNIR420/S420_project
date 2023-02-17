// simulateur.h
#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include <QWidget>
#include <QObject>
#include <cmath>
#include <QTimer>
#include <QTime>
#include "modbus_srv.h"

#define PI 3.14159256
#define envergure 2.0
#define Longueur 4.0
#define Y 1.0

#define vagueAmplitude 0.5
#define vaguePeriode 10.0
#define angleAzimut 0.785
#define interVague 4.0

class Simulateur : public QObject
{
    Q_OBJECT

private:
    double m_angleVentJeu ; // System Wind Angle
    double m_tws ;
    int m_beaufort ;  // de 0 à 12

    double m_roulis ;
    double m_tangage ;
    double m_vitesseAzimut ; // vitesse de rotation sur le lacet

    QTime m_t0, m_t1 ;

    Modbus_SRV* m_modbusServer;  // Pointeur vers la classe Modbus_SRV
    Simulateur* simulateur;

public:
    explicit Simulateur(Modbus_SRV* modbusserver, QObject *parent = nullptr); // Ajout d'un paramètre de type pointeur vers Modbus_SRV
    ~Simulateur();

    double getTwa();
    double getTws();
    double getAngleBome();
    double getSpeed(); //du bateau

    double getVaguePeriode() ; // T
    double getInterVague() ; // lambda
    double getVagueAmplitude() ; // A0
    double getAngleAzimut() ; // theta

    double getVagueVitesse() ;

    void setAngleVentJeu(double twa); // System Wind Angle
    void setTws(double tws);
    void setWave(int force); // échelle de beaufort

    void setRoulis() ;
    void setTangage() ;
    void setVitesseAzimut() ;

private slots:
    void calcul() ;

signals:
    // déclaration des signaux utilisés pour communiquer avec l'IHM
    void someSignal(int arg1, bool arg2);
};

#endif // SIMULATEUR_H
