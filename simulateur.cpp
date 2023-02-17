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
    connect(timer, &QTimer::timeout, this, &simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
}

void simulateur::setRoulis(){
    m_t1 = m_t1.currentTime() ;

    /*cout << "result sin : " << sin(2.0*PI*getVaguePeriode() * m_t0.secsTo(t1)
                                   - (2.0*PI / getInterVague()) * (Y + envergure/2.0) * sin(getAngleAzimut())) ;
    cout << "\tdeltaT : " << t0.secsTo(t1) << endl ;*/

    double ze = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y + envergure/2.0) * sin(getAngleAzimut())) ;

    double zd = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y - envergure/2.0) * sin(getAngleAzimut())) ;

    if ((ze - zd)/envergure <= 1 && (ze - zd)/envergure >= -1)
    m_roulis = asin((ze - zd)/envergure) ;
    else m_roulis = PI/2.0 * ((ze - zd)/envergure)/(abs((ze - zd)/envergure)) ;
}

void simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y + Longueur/2.0) * cos(getAngleAzimut())) ;

    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y - Longueur/2.0) * cos(getAngleAzimut())) ;

    if ((zc - za)/Longueur <= 1 && (zc - za)/Longueur >= -1)
    m_tangage = asin((zc - za)/Longueur) ;
    else m_tangage = PI/2.0 * ((zc - za)/Longueur)/(abs((zc - za)/Longueur)) ;
}

void simulateur::setVitesseAzimut(){
    m_vitesseAzimut = 0.0 ;
}

double simulateur::getVagueAmplitude(){
    return vagueAmplitude ;
}

double simulateur::getVaguePeriode(){
    return vaguePeriode ;
}

/*double simulateur::getVagueVitesse(){
    return 4.0 ;
}*/

double simulateur::getAngleAzimut(){
    return angleAzimut ;
}

double simulateur::getInterVague(){
    return interVague ;
}

void simulateur::calcul(){
    setRoulis();
    setTangage();
    setVitesseAzimut();
    cout << "roulis    : " << round(m_roulis*180.0/PI) << "°" << endl
         << "tangage   : " << round(m_tangage*180.0/PI) << "°" << endl ;
    cout << "delta thé : " << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "s\t" << m_t0.msecsTo(m_t1) << "ms" << endl ;
}

void simulateur::setWave(int force){
    m_beaufort = force ;
}

void simulateur::setAngleVentJeu(double twa){
    m_angleVentJeu = twa ;
}

void simulateur::setTws(double tws){
    m_tws = tws ;
}

simulateur::~simulateur(){}
