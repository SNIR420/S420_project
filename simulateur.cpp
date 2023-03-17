#include "simulateur.h"

Simulateur::Simulateur(QObject *parent, QString cheminPolaire)
    : QObject{parent}
{
    m_x = 0 ;
    m_y = 0 ;
    m_angleAzimut = 0.785398163 ;
    m_polaire = Polaire(cheminPolaire) ;
    m_vagueAmplitude = vagueAmplitude ;
    m_vagueVitesse = vagueVitesse ;
    m_tws = getTws() ;

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &Simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
}

void Simulateur::setRoulis(){
    m_t1 = m_t1.currentTime() ;
    if (getVagueVitesse() == 0) { m_roulis = 0 ; return ; }

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
    if (getVagueVitesse() == 0) { m_tangage = 0 ; return ; }

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
    return m_vagueAmplitude ;
}

double Simulateur::getVaguePeriode(){
    return vaguePeriode ;
}

double Simulateur::getVagueVitesse(){
    return m_vagueVitesse ;
}

void Simulateur::setSpeed(){ // utilise la classe polaire pour obtenir la vitesse
    int i = 0, j = 0 ;
    while(m_polaire.getPolaireData()[0][i] <= getTws()){
        i++ ;
    }
    while(m_polaire.getPolaireData()[j][0] <= getTwa()){
        j++ ;
    }
    m_speed = m_polaire.getPolaireData()[j][i] ;
    //m_speed = 0.0 ;
}

double Simulateur::getAngleAzimut(){
    return m_angleAzimut ;
}

double Simulateur::getInterVague(){
    return getVaguePeriode()*getVagueVitesse() ;
}

double Simulateur::getTws(){
    return TWS ;
}

double Simulateur::getTwa(){
    return TWA ;
}

void Simulateur::calcul(){
    m_x += sin(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 1852 et 3600 pour conversion noeuds/mètres
    m_y += cos(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 0.1s soit l'intervalle du timer
    setRoulis();
    setTangage();
    setVitesseAzimut(); // inutile pour l'instant
    setSpeed();
    qDebug() << "";
    qDebug() << "roulis    : " << round(m_roulis*180.0/PI*10.0)/10.0 << "°" ;
    qDebug() << "tangage   : " << round(m_tangage*180.0/PI*10.0)/10.0 << "°" ;
    qDebug() << "vitesse   : " << m_speed << " nd" ;
    qDebug() << "temps     : " << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "s  \t" << m_t0.msecsTo(m_t1) << "ms" ;
    qDebug() << "x = " << m_x << "  y = " << m_y ;
    qDebug() << "angle azimut : " << m_angleAzimut*180/PI << "°" ;
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
