#include "rollme.h"
#include <iostream>
using namespace std ;

//double t = 2.0 ;

CRollme::CRollme(){
    set_t(time(0)) ;
    setRoulis() ;
    setTangage() ;
    setVitesseAzimut() ;
}

void CRollme::setRoulis(){
    set_t(time(0)) ;
    double ze = A0 * sin(omega * get_t() + phi - k * (Y + envergure/2 ) * sin(theta)) ;
    double zd = A0 * sin(omega * get_t() + phi - k * (Y - envergure/2 ) * sin(theta)) ;
    m_roulis = asin((ze - zd)/envergure) ;
    //cout << "temps ini : " << getTruc1() << endl ;
}

void CRollme::setTangage(){
    set_t(time(0)) ;
    double zc = A0 * sin(omega * get_t() + phi - k * (Y + Longueur/2) * cos(theta)) ;
    double za = A0 * sin(omega * get_t() + phi - k * (Y - Longueur/2) * cos(theta)) ;
    m_tangage = asin((zc - za)/Longueur) ;
    //cout << "temps actu : " << getTruc2() << endl ;
}

void CRollme::setVitesseAzimut(){
    m_vitesseAzimut = 0.0 ;
}

double CRollme::getRoulis(){
    return m_roulis ;
}

double CRollme::getTangage(){
    return m_tangage ;
}

double CRollme::getVitesseAzimut(){
    return m_vitesseAzimut ;
}