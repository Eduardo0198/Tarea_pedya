/*  
José Eduardo Viveros Escanilla
*/

#ifndef FUCIONES_H_
#define FUCIONES_H_

#include "funciones.h"
#include <iostream>


class Funciones {

public:

long sumaIterativa(int a){
    
    int acum = 0;
    for (int i = 1; i <= a; i++){
        acum += i;
    }
    return acum;
}

long sumaRecursiva(int a){
    
    if (a == 0){
        return 0;
    }
    else {
        return a + sumaRecursiva(a - 1);
    }
}

long sumaDirecta (int a){
    return ((a * (a + 1)) / 2);
}

};

#endif
