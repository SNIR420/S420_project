#include "simulateur.h"
#include <QDebug>

Simulateur::Simulateur(QString pol_location, Modbus_SRV* modbusserver, QObject *parent) : QObject(parent), m_modbusServer(modbusserver), m_polaire(pol_location) // Initialisation de m_modbusserver dans la liste d'initialisation du constructeur
{
    m_x = 0 ;
    m_y = 0 ;
    m_angleAzimut = 0.785398163 ;

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &Simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
    polaire = new Polaire(pol_location);
}

void Simulateur::setRoulis(){
    m_t1 = m_t1.currentTime() ;

    /*cout << "result sin : " << sin(2.0*PI*getVaguePeriode() * m_t0.secsTo(t1)
                                   - (2.0*PI / getInterVague()) * (Y + envergure/2.0) * sin(getAngleAzimut())) ;
    cout << "\tdeltaT : " << t0.secsTo(t1) << endl ;*/

    double ze = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + envergure/2.0 * sin(getAngleAzimut()))) ;

    double zd = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - envergure/2.0 * sin(getAngleAzimut()))) ;

    if ((ze - zd)/envergure <= 1 && (ze - zd)/envergure >= -1)
    m_roulis = asin((ze - zd)/envergure) ;
    else m_roulis = PI/2.0 * ((ze - zd)/envergure)/(abs((ze - zd)/envergure)) ;
}

void Simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + Longueur/2.0 * cos(getAngleAzimut()))) ;

    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - Longueur/2.0 * cos(getAngleAzimut()))) ;

    if ((zc - za)/Longueur <= 1 && (zc - za)/Longueur >= -1)
    m_tangage = asin((zc - za)/Longueur) ;
    else m_tangage = PI/2.0 * ((zc - za)/Longueur)/(abs((zc - za)/Longueur)) ;
}

void Simulateur::setVitesseAzimut(){

}

double Simulateur::getVagueAmplitude(){
    return m_modbusServer->getHautvague() ;
}

double Simulateur::getVaguePeriode(){
    return vaguePeriode ;
}

double Simulateur::getVagueVitesse(){
    return m_modbusServer->getVitvague() ;
}

void Simulateur::setSpeed(){ // utilise la classe polaire pour obtenir la vitesse
    if(m_modbusServer->getSwa() <= 180){
        m_speed = polaire->getMaxSpeed(getTwa(), m_modbusServer->getTws()) ;
    }
    else{
        m_speed = polaire->getMaxSpeed(180-(getTwa()%180), m_modbusServer->getTws()) ;
    }
    qDebug() << "Speed :" << m_speed;
}

double Simulateur::getAngleAzimut(){
    return m_angleAzimut ;
}

double Simulateur::getInterVague(){
    return getVaguePeriode()*getVagueVitesse() ;
}

double Simulateur::getTws(){
    return m_modbusServer->getTws() ;
}

int Simulateur::getTwa(){
    return m_modbusServer->getSwa();
}

void Simulateur::calcul(){
    m_x += sin(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 1852 et 3600 pour conversion noeuds/mètres
    m_y += cos(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 0.1s soit l'intervalle du timer
    setRoulis();
    setTangage();
    m_modbusServer->setRoulis(m_roulis*180.0/PI);
    m_modbusServer->setTangage(m_tangage*180.0/PI);
    setVitesseAzimut(); // inutile pour l'instant
    setSpeed();
    /*qDebug() << "roulis    : " << round(m_roulis*180.0/PI*10.0)/10.0 << "°";
    qDebug() << "tangage   : " << round(m_tangage*180.0/PI*10.0)/10.0 << "°";
    qDebug() << "vitesse   : " << m_speed << " nd";
    qDebug() << "delta thé : " << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "s  \t" << m_t0.msecsTo(m_t1) << "ms";
    qDebug() << "x = " << m_x << "  y = " << m_y;
    qDebug() << "angle azimut : " << m_angleAzimut*180/PI << "°";*/
}

Simulateur::~Simulateur(){}
