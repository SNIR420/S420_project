#ifndef SIMULATEUR_H
#define SIMULATEUR_H

#include "ui_simulateur.h"
#include <cmath>
#include <QTimer>
#include <QTime>

#define PI 3.14159256
#define envergure 2.0
#define Longueur 4.0
#define Y 1.0

#define vagueAmplitude 0.5
#define vaguePeriode 10.0
#define angleAzimut 0.785
#define interVague 4.0

#include <QMainWindow>

class simulateur : public QMainWindow, private Ui::simulateur{
    Q_OBJECT

private:
    double m_angleVentJeu ; // System Wind Angle
    double m_tws ;
    int m_beaufort ;  // de 0 à 12

    double m_roulis ;
    double m_tangage ;
    double m_vitesseAzimut ; // vitesse de rotation sur le lacet

    QTime m_t0, m_t1 ;

    /*double m_vaguePeriode ;
    double m_vagueVitesse ;
    double m_angleAzimut ;*/

public:
    explicit simulateur(QWidget *parent = nullptr);
    ~simulateur();

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

public slots:
    //void info(const QString& src, const QString& msg ) ;

private slots:
    void calcul() ;
};
#endif // SIMULATEUR_H
