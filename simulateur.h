// simulateur.h
#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include <QTimer>
#include <QTime>
#include <QObject>
#include <cmath>
#include "modbus_srv.h"
#include "polaire.h"

#define PI 3.14159256
#define envergure 2.0 // mètres
#define Longueur 4.0  // mètres
#define Y 0.0         // mètres

#define vagueAmplitude 3.0 // mètres
#define vaguePeriode 10.0  // secondes
//#define angleAzimut 0.785398163

//#define interVague 30

#define TWS 0.1   //noeuds
#define TWA 1.1  //degrés

class Simulateur : public QObject
{
    Q_OBJECT

private:
    double m_roulis ;
    double m_tangage ;
    double m_vitesseAzimut ; // vitesse de rotation sur le lacet

    QTime m_t0, m_t1 ;

    Modbus_SRV* m_modbusServer;  // Pointeur vers la classe Modbus_SRV
    Simulateur* simulateur;
    Polaire* polaire;
    QString m_polaire;

    double m_x ;
    double m_y ;
    double m_speed ;

    /*double m_vaguePeriode ;
        double m_vagueVitesse ;*/
    double m_angleAzimut ; // radians
    // 0    correspond à un roulis nul     et à un tangage maximum
    // pi/2 correspond à un roulis maximum et à un tangage nul (environ 1.57)
    // pi/4 (environ 0.785398163)

public:
    explicit Simulateur(QString pol_location, Modbus_SRV* modbusserver, QObject *parent = nullptr); // Ajout d'un paramètre de type pointeur vers Modbus_SRV
    ~Simulateur();

    int getTwa();
    double getTws();
    double getAngleBome();
    double getSpeed(); //du bateau

    double getVaguePeriode() ; // T
    double getInterVague() ; // lambda
    double getVagueAmplitude() ; // A0
    double getAngleAzimut() ; // theta

    double getVagueVitesse() ;

    void setRoulis() ;
    void setTangage() ;
    void setVitesseAzimut() ;

    void setSpeed() ;
private slots:
    void calcul() ;
};

#endif // SIMULATEUR_H
