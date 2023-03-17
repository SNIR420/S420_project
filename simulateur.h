#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include "polaire.h"
#include <cmath>
#include <QTimer>
#include <QTime>
#include <QObject>

#define PI 3.14159256
#define envergure 2.0 // mètres
#define Longueur 4.0  // mètres
#define Y 0.0         // mètres

#define vagueAmplitude 3.0 // mètres
#define vaguePeriode 10.0  // secondes

#define vagueVitesse 3 // mètres par secondes

#define TWS 0.1   //noeuds
#define TWA 1.1  //degrés

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

    Polaire m_polaire = Polaire("Class40.pol") ;

    double m_x ;
    double m_y ;

    double m_speed ;

    double m_vagueAmplitude ;
    double m_vagueVitesse ;
    double m_angleAzimut ;


public:
    explicit Simulateur(QObject *parent = nullptr, QString cheminPolaire = "Class404.pol");
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

    void setSpeed() ;


signals:
private slots:
    void calcul() ;
};

#endif // SIMULATEUR_H
