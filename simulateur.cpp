#include "simulateur.h"
#include <QDebug>

Simulateur::Simulateur(QString pol_location, Modbus_SRV* modbusserver, QObject *parent) : QObject(parent), m_modbusServer(modbusserver), m_polaire(pol_location) // Initialisation de m_modbusserver dans la liste d'initialisation du constructeur
{
    m_x = 0 ;
    m_y = 0 ;
    m_angleAzimut = (m_modbusServer->getAngleAzimut()*PI)/180 ;

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &Simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
    polaire = new Polaire(pol_location);
}

void Simulateur::setRoulis(){
    m_t1 = m_t1.currentTime() ;

    /*qDebug() << "get :" << getAngleAzimut() ;
    qDebug() << "modbus :" << m_modbusServer->getAngleAzimut() ;*/

    double ze = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0) - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + envergure/2.0 * sin(getAngleAzimut()))) ;
    double zd = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0) - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - envergure/2.0 * sin(getAngleAzimut()))) ;

    if ((ze - zd)/envergure <= 1 && (ze - zd)/envergure >= -1)  m_roulis = asin((ze - zd)/envergure) ;
    else m_roulis = PI/2.0 * ((ze - zd)/envergure)/(abs((ze - zd)/envergure)) ;
}

void Simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;

    /*qDebug() << "get :" << getAngleAzimut() ;
    qDebug() << "modbus :" << m_modbusServer->getAngleAzimut() ;*/

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0) - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + Longueur/2.0 * cos(getAngleAzimut()))) ;
    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0) - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - Longueur/2.0 * cos(getAngleAzimut()))) ;

    if ((zc - za)/Longueur <= 1 && (zc - za)/Longueur >= -1)    m_tangage = asin((zc - za)/Longueur) ;
    else m_tangage = PI/2.0 * ((zc - za)/Longueur)/(abs((zc - za)/Longueur)) ;

    //qDebug() << "tangage :" << m_tangage ;
}

void Simulateur::setVitesseAzimut(){

}

double Simulateur::getVagueAmplitude(){
    return m_modbusServer->getHautvague() ;
}

double Simulateur::getVaguePeriode(){
    return m_modbusServer->getIntervague() ;
}

double Simulateur::getVagueVitesse(){
    return m_modbusServer->getVitvague() ;
}

void Simulateur::setSpeed(){ // utilise la classe polaire pour obtenir la vitesse
    if(m_modbusServer->getSwa() < 180){
        m_speed = polaire->getMaxSpeed(getTwa(), getTws()) ;
    }
    else{
        m_speed = polaire->getMaxSpeed(360-getTwa(), getTws()) ;
    }
}

double Simulateur::getAngleAzimut(){
    //return (m_modbusServer->getAngleAzimut()*PI)/180 ;
    return  (m_modbusServer->getAngleAzimut()*PI)/180 ;
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

double Simulateur::getRatio(){
    double bome_reel = m_modbusServer->getBom() - m_modbusServer->getBomError() ;
    //qDebug() << "av:" << bome_reel ;
    double twa = m_modbusServer->getSwa() ;

    double ratio = 0 ;
    //ratio = (twa + 180.0 - bome_reel)/twa ;
    if (bome_reel < 0) bome_reel = 180 - bome_reel ;

    //qDebug() << "ar:" << bome_reel ;

    if (twa >= 90 && twa <= 270){
        if (abs(twa - bome_reel) >= 90){
            ratio = 2 - (abs(twa - bome_reel))/90 ;
        }
        /*else{
            ratio = 1 / ((abs(twa - bome_reel))/90) ;
        }*/
    }
    else{
        if (180 - abs(180 - twa) == 0) ratio = 0 ;
        else ratio = 1 - (180 - bome_reel)/(180 - abs(180 - twa)) ;
    }

    if (ratio < 0) {/* qDebug() << "ratio :" << ratio ;*/ ratio = -1 * ratio ; }
    if (ratio > 1) {/* qDebug() << "ratio :" << ratio ;*/ ratio = ratio - floor(ratio) ; }
    //qDebug() << ratio ;
    //qDebug() << "twa :" << twa << "\t" << "bome :" << bome_reel << "\t" << "ratio :" << ratio ;

    return ratio ;
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
    m_modbusServer->setSpeed(m_speed);

    /*double bome_reel = m_modbusServer->getBom() - m_modbusServer->getBomError() ;
    double twa = m_modbusServer->getSwa() ;
    //qDebug() << "av:" << bome_reel ;
    if (bome_reel < 0) bome_reel = 180 - bome_reel ;*/

}

Simulateur::~Simulateur(){}
