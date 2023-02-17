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

#include <QMainWindow>

class simulateur : public QMainWindow, private Ui::simulateur{
    Q_OBJECT

private:
    double angleVentJeu ; // System Wind Angle
    double tws ;
    int beaufort ;  // de 0 à 12

    double roulis ;
    double tangage ;
    double vitesseAzimut ; // vitesse de rotation sur le lacet

    QTime t0, t1 ;

    /*double vaguePeriode ;
    double vagueVitesse ;
    double angleAzimut ;*/

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
