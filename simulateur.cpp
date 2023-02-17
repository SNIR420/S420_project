#include "simulateur.h"
#include "iostream"
using namespace std ;

simulateur::simulateur(QWidget *parent /* fichier .pol ; adresse modbus */)
    : QMainWindow(parent)
{
    setupUi(this);
    //création de l'object de type polaire
    //connection modbus

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &simulateur::calcul) ;    //connect le timeout() du timer à un truc
    timer->start(100) ;
    t0 = t0.currentTime() ;
}

void simulateur::setRoulis(){
    t1 = t1.currentTime() ;

    /*cout << "result sin : " << sin(2.0*PI*getVaguePeriode() * t0.secsTo(t1)
                                   - (2.0*PI / getInterVague()) * (Y + envergure/2.0) * sin(getAngleAzimut())) ;
    cout << "\tdeltaT : " << t0.secsTo(t1) << endl ;*/

    double ze = getVagueAmplitude() * sin(2*PI*getVaguePeriode() * (t0.msecsTo(t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y + envergure/2.0) * sin(getAngleAzimut())) ;

    double zd = getVagueAmplitude() * sin(2*PI*getVaguePeriode() * (t0.msecsTo(t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y - envergure/2.0) * sin(getAngleAzimut())) ;

    roulis = asin((ze - zd)/envergure) ;
}

void simulateur::setTangage(){
    t1 = t1.currentTime() ;

    double zc = getVagueAmplitude() * sin(2.0*PI*getVaguePeriode() * (t0.msecsTo(t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y + Longueur/2.0) * cos(getAngleAzimut())) ;

    double za = getVagueAmplitude() * sin(2.0*PI*getVaguePeriode() * (t0.msecsTo(t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y - Longueur/2.0) * cos(getAngleAzimut())) ;

    tangage = asin((zc - za)/Longueur) ;
}

void simulateur::setVitesseAzimut(){

}

double simulateur::getVagueAmplitude(){
    return 0.5 ;
}

double simulateur::getVaguePeriode(){
    return 0.1 ;
}

/*double simulateur::getVagueVitesse(){
    return 4.0 ;
}*/

double simulateur::getAngleAzimut(){
    return 0.785 ;
}

double simulateur::getInterVague(){
    return 4.0 ;
}

void simulateur::calcul(){
    setRoulis();
    setTangage();
    setVitesseAzimut();
    /*cout << "roulis : " << roulis*180.0/PI << "°" << endl
         << "tangage : " << tangage*180.0/PI << "°" << endl ;
    //cout << "t : " << t0.second() << ' ' << t1.second() << endl ;
    cout << "delta thé : " << t0.msecsTo(t1) << "ms\t" << t0.msecsTo(t1)/1000.0 << 's' <<  endl ;*/
}

simulateur::~simulateur(){}
