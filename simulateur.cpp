#include "simulateur.h"
#include "iostream"
using namespace std ;

simulateur::simulateur(QWidget *parent, QString cheminPolaire /* adresse modbus */)
    : QMainWindow(parent)
{
    setupUi(this);
    m_x = 0 ;
    m_y = 0 ;
    m_angleAzimut = 0.785398163 ;
    m_polaire = Polaire(cheminPolaire) ;

    cout << "Polaire Data Size (outside) : " << m_polaire.getPolaireData()[30][17] << endl ;

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
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + envergure/2.0 * sin(getAngleAzimut()))) ;

    double zd = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - envergure/2.0 * sin(getAngleAzimut()))) ;

    if ((ze - zd)/envergure <= 1 && (ze - zd)/envergure >= -1)
    m_roulis = asin((ze - zd)/envergure) ;
    else m_roulis = PI/2.0 * ((ze - zd)/envergure)/(abs((ze - zd)/envergure)) ;
}

void simulateur::setTangage(){
    m_t1 = m_t1.currentTime() ;

    double zc = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 + Longueur/2.0 * cos(getAngleAzimut()))) ;

    double za = getVagueAmplitude() * sin(2.0*PI/getVaguePeriode() * (m_t0.msecsTo(m_t1)/1000.0)
        - (2.0*PI / getInterVague()) * (cos(getAngleAzimut()) * m_speed * 1852.0 / 3600.0 * m_t0.msecsTo(m_t1)/1000.0 - Longueur/2.0 * cos(getAngleAzimut()))) ;

    if ((zc - za)/Longueur <= 1 && (zc - za)/Longueur >= -1)
    m_tangage = asin((zc - za)/Longueur) ;
    else m_tangage = PI/2.0 * ((zc - za)/Longueur)/(abs((zc - za)/Longueur)) ;
}

void simulateur::setVitesseAzimut(){

}

double simulateur::getVagueAmplitude(){
    return vagueAmplitude ;
}

double simulateur::getVaguePeriode(){
    return vaguePeriode ;
}

double simulateur::getVagueVitesse(){
    return vagueVitesse ;
}

void simulateur::setSpeed(){ // utilise la classe polaire pour obtenir la vitesse
    int i = 0, j = 0 ;
    while(m_polaire.getPolaireData()[0][i] <= getTws()){
        i++ ;
    }
    while(m_polaire.getPolaireData()[j][0] <= getTwa()){
        j++ ;
    }
    m_speed = m_polaire.getPolaireData()[j][i] ;
    //m_speed = 0.0 ;
    //m_speed = -m_speed ; // pour l'instant, à enlever plus tard
}

double simulateur::getAngleAzimut(){
    return m_angleAzimut ;
}

double simulateur::getInterVague(){
    return getVaguePeriode()*getVagueVitesse() ;
}

double simulateur::getTws(){
    return TWS ;
}

double simulateur::getTwa(){
    return TWA ;
}

void simulateur::calcul(){
    m_x += sin(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 1852 et 3600 pour conversion noeuds/mètres
    m_y += cos(getAngleAzimut()) * m_speed * 1852 / 3600 * 0.1 ; // 0.1s soit l'intervalle du timer
    setRoulis();
    setTangage();
    setVitesseAzimut(); // inutile pour l'instant
    setSpeed();
    cout << endl ;
    cout << "roulis    : " << round(m_roulis*180.0/PI*10.0)/10.0 << "°" << endl
         << "tangage   : " << round(m_tangage*180.0/PI*10.0)/10.0 << "°" << endl
         << "vitesse   : " << m_speed << " nd" << endl ;
    cout << "delta thé : " << round(m_t0.msecsTo(m_t1)/100.0)/10.0 << "s  \t" << m_t0.msecsTo(m_t1) << "ms" << endl ;
    cout << "x = " << m_x << "  y = " << m_y << endl ;
    cout << "angle azimut : " << m_angleAzimut*180/PI << "°" << endl ;
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
