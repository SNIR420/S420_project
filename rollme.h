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

θ = arcsin((ze - zd)/2)

*/

#define envergure e
#define Longueur L

class CRollme {

    public:
        
} ;