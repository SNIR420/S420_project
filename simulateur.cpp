#include "simulateur.h"

Simulateur::Simulateur(QObject *parent, QString cheminPolaire)
    : QObject{parent}
{
    m_x = 0 ;
    m_y = 0 ;
    m_angleAzimut = 0.785398163 ;
    m_polaire = Polaire(cheminPolaire) ;
    m_vagueVitesse = vagueVitesse ;
    m_vaguePeriode = vaguePeriode ;
    m_bome = 145 ;
    m_bome = getTwa() + 180 % 360 ;
    setBeaufort();
    //setWave(m_beaufort);
    m_vagueAmplitude = 2.0 ;

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &Simulateur::calcul) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(100) ;
    m_t0 = m_t0.currentTime() ;
}

void Simulateur::setRoulis(){
    m_t1 = m_t1.currentTime() ;
    if (getVagueVitesse() == 0) { m_roulis = 0 ; return ; }

    double ze = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (m_y + envergure/2.0 * sin(getAngleAzimut()*PI/180.0))) ;

    double zd = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (m_y - envergure/2.0 * sin(getAngleAzimut()*PI/180.0))) ;

    if ((ze - zd)/envergure <= 1 && (ze - zd)/envergure >= -1)
    m_roulis = asin((ze - zd)/envergure) ;
    else m_roulis = PI/2.0 * ((ze - zd)/envergure)/(abs((ze - zd)/envergure)) ;
}

void Simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;
    if (getVagueVitesse() == 0) { m_tangage = 0 ; return ; }

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (m_y + Longueur/2.0 * cos(getAngleAzimut()*PI/180.0))) ;

    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (m_y - Longueur/2.0 * cos(getAngleAzimut()*PI/180.0))) ;

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
    double l_vaguePeriode = m_vaguePeriode ;

    if (l_vaguePeriode < 10.0) l_vaguePeriode = 10.0 ;

    return l_vaguePeriode ;
}

double Simulateur::getVagueVitesse(){
    double l_vagueVitesse = m_vagueVitesse ;

    if (l_vagueVitesse < 2.0 && l_vagueVitesse != 0) l_vagueVitesse = 2.0 ;

    return l_vagueVitesse ;
}

void Simulateur::setSpeed(){ // utilise la classe polaire pour obtenir la vitesse
    m_speed = m_polaire.getSpeedRatio(getTwa(), getTws(), getRatio()) ;
}

double Simulateur::getAngleAzimut(){
    return m_angleAzimut ;
}

double Simulateur::getInterVague(){
    return getVaguePeriode()*getVagueVitesse() ;
}

int Simulateur::getTws(){
    if (TWS >= 70) return 69 ;
    return TWS ;
}

int Simulateur::getTwa(){
    int twa = TWA ;
    if (twa > 360) twa = twa % 360 ;
    if (twa > 180) twa = 360 - twa ;
    return twa ;
}

double Simulateur::getRatio(){
    if (getTwa() < 90 || getTwa() > 270){
        return 1-(180.0-m_bome)/(180.0-abs(180.0-getTwa())) ;
    }
    else{
        return (90.0-abs(abs(getTwa()-180.0)+90.0-m_bome))/90.0 ;
    }
}

void Simulateur::calcul(){
    setSpeed();
    m_x += sin(getAngleAzimut()*PI/180.0) * m_speed * 1852 / 3600 * 0.1 ; // 1852 et 3600 pour conversion noeuds/mètres
    m_y += cos(getAngleAzimut()*PI/180.0) * m_speed * 1852 / 3600 * 0.1 ; // 0.1s soit l'intervalle du timer
    setRoulis();
    setTangage();
    setVitesseAzimut(); // inutile pour l'instant
    qDebug() << "";
    /*qDebug() << "roulis    :" << round(m_roulis*180.0/PI*10.0)/10.0 << "°" ;
    qDebug() << "tangage   :" << round(m_tangage*180.0/PI*10.0)/10.0 << "°" ;
    qDebug() << "vitesse   :" << m_speed << "nd" ;
    qDebug() << "temps     :" << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "s  \t" << m_t0.msecsTo(m_t1) << "ms" ;
    qDebug() << "x =" << m_x << "  y =" << m_y ;
    qDebug() << "angle azimut :" << m_angleAzimut << "°" ;*/
    //qDebug() << "vagueAmplitude :" << getVagueAmplitude() ;
    //qDebug() << "ratio :" << getRatio() ;
    //qDebug() << "beaufort :" << m_beaufort ;
    //qDebug() << "vagueAmplitude :" << getVagueAmplitude() ;
    //qDebug() << "vagueVitesse :" << getVagueVitesse() << "/ vaguePeriode :" << getVaguePeriode() ;
    qDebug() << "twa :" << getTwa()  << "°" ;
    qDebug() << "tws :" << getTws()  << "°" ;
        qDebug() << "ratio :" << getRatio() ;
        qDebug() << "gite max :" << m_polaire.getMaxGite(getTwa(), getTws()) ;
    qDebug() << "gite ratio :" << m_polaire.getGiteRatio(getTwa(), getTws(), getRatio()) ;
    //qDebug() << "angle bome :" << m_bome << "°" ;
    //qDebug() << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "\t" << round(m_tangage*180.0/PI*10.0)/10.0 << "°" << "\t" << m_t0.msecsTo(m_t1) ;
}

void Simulateur::setAngleVentJeu(double twa){
    m_angleVentJeu = twa ;
}

void Simulateur::setTws(double tws){
    m_tws = tws ;
}

void Simulateur::setWave(int force){
    double vitInf, vitSup ;
    double vagInf, vagSup ;
    if (force == 0){
        m_vagueAmplitude = 0.0 ;
    }
    else if (force == 1){
        m_vagueAmplitude = 0.1 ;
    }
    else if (force == 2){
        vitInf = 4 ;
        vitSup = 6 ;
        vagInf = 0.2 ;
        vagSup = 0.5 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 3){
        vitInf = 7.0 ;
        vitSup = 10.0 ;
        vagInf = 0.6 ;
        vagSup = 0.9 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
        qDebug() << m_vagueAmplitude ;
    }
    else if (force == 4){
        vitInf = 11 ;
        vitSup = 16 ;
        vagInf = 1.0 ;
        vagSup = 1.5 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 5){
        vitInf = 17 ;
        vitSup = 21 ;
        vagInf = 2.0 ;
        vagSup = 2.5 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 6){
        vitInf = 22 ;
        vitSup = 27 ;
        vagInf = 3.0 ;
        vagSup = 4.0 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 7){
        vitInf = 28 ;
        vitSup = 33 ;
        vagInf = 4.0 ;
        vagSup = 5.5 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 8){
        vitInf = 34 ;
        vitSup = 40 ;
        vagInf = 5.5 ;
        vagSup = 7.0 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 9){
        vitInf = 41 ;
        vitSup = 47 ;
        vagInf = 7.5 ;
        vagSup = 10.0 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 10){
        vitInf = 48 ;
        vitSup = 55 ;
        vagInf = 10.0 ;
        vagSup = 12.5 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 11){
        vitInf = 56 ;
        vitSup = 63 ;
        vagInf = 12.5 ;
        vagSup = 14.0 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else if (force == 12){
        vitInf = 64 ;
        vitSup = 70 ;
        vagInf = 16.0 ;
        vagSup = 18.0 ;
        m_vagueAmplitude = vagInf+((vagSup-vagInf)/(vitSup-vitInf)*(getTws()-vitInf))  ;
    }
    else m_vagueAmplitude = 0.1 ;
}

void Simulateur::setBeaufort(){
    if (getTws() <= 1) m_beaufort = 0 ;
    else if (getTws() <= 3) m_beaufort = 1 ;
    else if (getTws() <= 6) m_beaufort = 2 ;
    else if (getTws() <= 10) m_beaufort = 3 ;
    else if (getTws() <= 16) m_beaufort = 4 ;
    else if (getTws() <= 21) m_beaufort = 5 ;
    else if (getTws() <= 27) m_beaufort = 6 ;
    else if (getTws() <= 33) m_beaufort = 7 ;
    else if (getTws() <= 40) m_beaufort = 8 ;
    else if (getTws() <= 47) m_beaufort = 9 ;
    else if (getTws() <= 55) m_beaufort = 10 ;
    else if (getTws() <= 63) m_beaufort = 11 ;
    else if (getTws() <= 70) m_beaufort = 12 ;
    else m_beaufort = 0 ;
}

Simulateur::~Simulateur(){}
