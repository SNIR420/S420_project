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

#define vagueAmplitude 3.0 // mètres
#define vaguePeriode 10.0  // secondes

#define vagueVitesse 3.0 // mètres par secondes

#define TWS 10   //noeuds
#define TWA 150  //degrés

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

    double m_vagueVitesse ;
    double m_vaguePeriode ;

    int m_angleAzimut ;

    int m_bome ;

    double m_ratio ;


public:
    explicit Simulateur(QObject *parent = nullptr, QString cheminPolaire = "Class404.pol");
    ~Simulateur();

    int getTwa();
    int getTws();
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

    void setVagueVitesse(double s_vagueVitesse){ m_vagueVitesse = s_vagueVitesse ; }
    void setVaguePeriode(double s_vaguePeriode){ m_vaguePeriode = s_vaguePeriode ; }

    double getRatio();


signals:
private slots:
    void calcul() ;
};

#endif // SIMULATEUR_H
