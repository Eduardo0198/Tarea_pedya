/*  
José Eduardo Viveros Escanilla
*/

#ifndef SORTS_H_
#define SORTS_H_

#include <iostream>
#include <vector>
#include <list>

template <class T>

class Sorts {

public:

    // Orndenamiento

    void ordenaSeleccion(std::vector<T> &v);
    void ordenaBurbuja(std::vector<T> &v);
    void ordenaMerge(std::vector<T> &v);
    
    // Busquerdas 

    int busqSecuencial(const std::vector<T> &v, const T &target);
    int busqBinaria(const std::vector<T> &v, const T &target);

};


//Funciones:

//Funcion Selection

template <class T>
void Sorts<T>::ordenaSeleccion(std::vector<T> &v){
    

    int n = v.size();
    for (int i = 0; i < n - 1; i++) {
        int min = i;
    
    // busca el indice del elemeto mas chico en lo que
    // queda del vector 

        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min]) {
                min = j;
            }
        }
        if (min != i) {
            //Voltea los valores
            std::swap(v[i], v[min]);
        }
    }
}

//Funcion Bubble

template <class T>
void Sorts<T>::ordenaBurbuja(std::vector<T> &v) {
    int n = v.size();
    bool swapped;
    do {
        swapped = false;

    // compara los elemtos actualesy hace los cambios
    // si es que son necesarios

        for (int i = 1; i < n; i++) {
            if (v[i - 1] > v[i]) {
                std::swap(v[i - 1], v[i]);
                swapped = true;
            }
        }
    } while (swapped);
}

/////////////////////////////////////////////////////////////////

// Metodos auxiliares
// estos metodos vienen de unos ejemplos de clase

template <class T>
void merge(std::vector<T> &v, int left, int middle, int right) {
    int n1 = middle - left + 1;
    int n2 = right - middle;

    std::vector<T> left_half(n1);
    std::vector<T> right_half(n2);

    for (int i = 0; i < n1; i++) {
        left_half[i] = v[left + i];
    }
    for (int i = 0; i < n2; i++) {
        right_half[i] = v[middle + 1 + i];
    }

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (left_half[i] <= right_half[j]) {
            v[k] = left_half[i];
            i++;
        } else {
            v[k] = right_half[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        v[k] = left_half[i];
        i++;
        k++;
    }

    while (j < n2) {
        v[k] = right_half[j];
        j++;
        k++;
    }
}

template <class T>
void mergeSort(std::vector<T> &v, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        mergeSort(v, left, middle);
        mergeSort(v, middle + 1, right);
        merge(v, left, middle, right);
    }
}


// Funcion Merge

template <class T>
void Sorts<T>::ordenaMerge(std::vector<T> &v) {
    int n = v.size();
    if (n > 1) {

    // llama a la funcion

        mergeSort(v, 0, n - 1);
    }
}


//Busquedas:

//Busqueda Secuencial

template <class T>
int Sorts<T>::busqSecuencial(const std::vector<T> &prueba, const T &val){
	
    // se declaran los valores de mid
    // low y high 

    int mid;
	int low = 0;
	int high = prueba.size() - 1;
    

    // mientras que 0 sea menor o igual al tamaño del arreglo

	while (low <= high) {

    // se parte en dos el arreglo y se hacen las sig 
    // comparaciones

		mid = (high + low) / 2;
		if (val == prueba[mid]) return mid;
		else if (val < prueba[mid]) high = mid - 1;
		else if (val > prueba[mid]) low = mid + 1;
	}
	return -1;
}


//Busqueda Binaria

template <class T>
int Sorts<T>::busqBinaria(const std::vector<T> &V, const T &target){

    // declaramos lo que vamos a usar en right y left

    int left = 0;
    int right = V.size() - 1;

    // se delcara en un vector ordenado

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (V[mid] == target) {

    // devuelve el indice si es que el valor es encontrado     

            return mid;
        }
        if (V[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    // si el valor no se encuentra se retorna el -1

    return -1;
}



#endif