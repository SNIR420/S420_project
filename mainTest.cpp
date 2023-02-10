#include "rollme.h"

#include <iostream>
using namespace std ;

#include <unistd.h>

int main(int argc, char** argv){
    CRollme variable ;
    cout << "roulis : " << variable.getRoulis() * 360 / 6.28318512 << endl ;
    cout << "tangage : " << variable.getTangage() * 360 / 6.28318512 << endl ;

    for (int i = 0 ; i < 5 ; i++){
    cout << "sleep de 1" << endl ;
    sleep(1) ;
    variable.setRoulis() ;
    variable.setTangage() ;
    cout << "roulis : " << variable.getRoulis() * 360 / 6.28318512 << endl ;
    cout << "tangage : " << variable.getTangage() * 360 / 6.28318512 << endl ;
    }

}