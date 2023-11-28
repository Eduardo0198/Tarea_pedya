// Jose Eduardo Viveros Escamilla 

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <string>
#include <sstream>

template <typename T>
class Heap {
public:
    // Constructor: Inicializa el montículo y reserva espacio en el vector.
    Heap(int max_size) {
        data.reserve(max_size);
    }

    // Inserta un elemento en el montículo.
    void push(const T& value) {
        // Agrega el elemento al final del vector.
        data.push_back(value);
        int index = data.size() - 1;

        // Mueve el elemento hacia arriba (hacia los ancestros) para mantener la propiedad del montículo.
        while (index > 0) {
            int parent = (index - 1) / 2;
            if (data[index] >= data[parent]) {
                break; // El montículo está ordenado correctamente.
            }
            std::swap(data[index], data[parent]);
            index = parent;
        }
    }

    // Elimina el elemento superior del montículo 
    //(el elemento más pequeño en un min-heap).
    void pop() {
        if (data.empty()) {
            return;  // No se puede hacer pop en un montículo vacío.
        }

        // Reemplaza el elemento superior con el último elemento del vector.
        data[0] = data.back();
        data.pop_back();
        int index = 0;
        int size = data.size();

        // Mueve el elemento hacia abajo (hacia los hijos) 
        // para mantener la propiedad del montículo.
        while (true) {
            int left_child = 2 * index + 1;
            int right_child = 2 * index + 2;
            int smallest = index;

            if (left_child < size && data[left_child] < data[smallest]) {
                smallest = left_child;
            }

            if (right_child < size && data[right_child] < data[smallest]) {
                smallest = right_child;
            }

            if (smallest == index) {
                break; // El montículo está ordenado correctamente.
            }

            std::swap(data[index], data[smallest]);
            index = smallest;
        }
    }

    // Devuelve el elemento superior del montículo (el elemento más pequeño en un min-heap).
    T top() const {
        if (data.empty()) {
            // Puedes lanzar una excepción aquí o manejar el caso de un montículo vacío de otra manera.
            // En este ejemplo, simplemente devolvemos un valor predeterminado 
            //(podría ser un problema si el montículo está vacío).
            return T();
        }

        return data[0];
    }

    // Devuelve el tamaño del montículo.
    int size() const {
        return data.size();
    }

    // Verifica si el montículo está vacío.
    bool empty() const {
        return data.empty();
    }

    // Método para convertir el montículo a una cadena para su impresión.
    std::string toString() const {
        std::stringstream aux;
        aux << "[";
        for (unsigned int i = 0; i < data.size(); i++) {
            if (i != 0) {
                aux << " ";
            }
            aux << data[i];
        }
        aux << "]";
        return aux.str();
    }

private:
    std::vector<T> data;
};

#endif
