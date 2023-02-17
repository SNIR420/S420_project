#include "simulateur.h"
#include <QDebug>

Simulateur::Simulateur(Modbus_SRV* modbusserver, QObject *parent) : QObject(parent), m_modbusServer(modbusserver) // Initialisation de m_modbusserver dans la liste d'initialisation du constructeur
{
    //création de l'object de type polaire
    //connection modbus

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &Simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
}

void Simulateur::setRoulis(){
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

void Simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y + Longueur/2.0) * cos(getAngleAzimut())) ;

    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (Y - Longueur/2.0) * cos(getAngleAzimut())) ;

    if ((zc - za)/Longueur <= 1 && (zc - za)/Longueur >= -1)
    m_tangage = asin((zc - za)/Longueur) ;
    else m_tangage = PI/2.0 * ((zc - za)/Longueur)/(abs((zc - za)/Longueur)) ;
}

void Simulateur::setVitesseAzimut(){
    m_vitesseAzimut = 0.0 ;
}

double Simulateur::getVagueAmplitude(){
    return m_modbusServer->getHautvague() ;
}

double Simulateur::getVaguePeriode(){
    return vaguePeriode ;
}

/*double simulateur::getVagueVitesse(){
    return 4.0 ;
}*/

double Simulateur::getAngleAzimut(){
    return angleAzimut ;
}

double Simulateur::getInterVague(){
    return interVague ;
}

void Simulateur::calcul(){
    setRoulis();
    setTangage();
    setVitesseAzimut();
    m_modbusServer->setRoulis(round(m_roulis*180.0/PI));
    m_modbusServer->setTangage(round(m_tangage*180.0/PI));
}

void Simulateur::setWave(int force){
    m_beaufort = force ;
}

void Simulateur::setAngleVentJeu(double twa){
    m_angleVentJeu = twa ;
}

void Simulateur::setTws(double tws){
    m_tws = tws ;
}

Simulateur::~Simulateur(){}
