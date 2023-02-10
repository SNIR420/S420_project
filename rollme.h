/*
point O = centre du repère
point B = centre du bateau
point C = avant du bateau 
point A = arrière du bateau
point D = droite du bateau
point E = gauche du bateau
repère de l'espace XYZ
repère du bateau xyz
angle θ (thêta) entre X et x (ou Y et y)

OB = (X ; Y)
OC = (X + L/2 sinθ ; Y + L/2 cosθ)
OA = (X - L/2 sinθ ; Y - L/2 cosθ)
OE = (X - e/2 cosθ ; Y + e/2 sinθ)
OD = (X + e/2 cosθ ; Y - e/2 sinθ)

ze = A0 sin(ωt + φ - k(Y + e/2 sinθ))
zd = A0 sin(ωt + φ - k(Y - e/2 sinθ))

α = arcsin((ze - zd)/e)  //roulis

zc = A0 sin(ωt + φ - k(Y + L/2 cosθ))
za = A0 sin(ωt + φ - k(Y - L/2 cosθ))

β = arcsin((zc - za)/L)  //tangage


*/
#include <cmath>
#include <ctime>

#define envergure 2.0 //donnée fixe
#define Longueur 4.0  //donnée fixe
#define phi 1.57       //vaut 0
#define omega 0.628  //fréquence de la vague * 2pi (liée à la distance entre deux vagues)
#define X 0.0       //distance du bateau par rapport au centre du repère sur l'axe X
                    //obtenu par calcul (varie en fonction du temps)
#define Y 0.0       //distance du bateau par rapport au centre du repère sur l'axe Y
                    //obtenu par calcul (varie en fonction du temps)
#define A0 0.5      //hauteur de la vague (à fournir, peut varier)
#define k 0.25       //vitesse de la vague (à fournir ?, peut varier ?)
#define theta 1.57  //angle du bateau par rapport au sens de la vague

//#define t 2.0

class CRollme {
    double m_roulis ; // alpha α
    double m_tangage ; // beta β
    double m_vitesseAzimut ;

    time_t m_t_ini = time(0) ;
    time_t m_t_actu ; 

    public:
        CRollme() ;

        void setRoulis() ;
        void setTangage() ;
        void setVitesseAzimut() ;

        double getRoulis() ;
        double getTangage() ;
        double getVitesseAzimut() ;

        time_t get_t() { return m_t_actu - m_t_ini ; }
        void set_t(time_t t) { m_t_actu = t ; }


        
} ;