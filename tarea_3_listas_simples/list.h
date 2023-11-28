/*
José Eduardo Viveros Escamilla
*/

#ifndef LIST_H
#define LIST_H
#include <sstream>
#include <list>

/* 
Pequeña explicacion de la clase dentro de clase:
 
Cuando hablamos de listas enlazadas hablamos como es que estas 
apuntan a un objeto a otro en una cadena.
como tal la clase list representa una lista enlazada y la clase 
link representa los elementos de la clase , es logico que la clase 
link sea un elemento de la clase list, esto facilita mucho el poder
manipular los nodos desde dentro de la clase

Investigando un poco encontre que las clases internas se usan cuando 
se trata de ocultar ciertos elementos y que estos no se usen en la im-
plentacion o en el main. en este caso en el main solo se usa un clase
lo que nos dice que la clase link deberia que ir interna, aprted de que
una forma mas practica no quetemos que el suario use los nodos manualmente. 

*/

template <class T>
class List {
private:
    template <class S>
    class Link {
    public:
        S value; // valor del nodo
        Link* next; // puntero que al siguiente nodo
        /*
        Constructor y base de link
        el valor y el puntero al siguiente nodo
        */
        Link(S val, Link* nxt = nullptr) : value(val), next(nxt) {}
    };

    Link<T>* head;

public:
    List() : head(nullptr) {}
    ~List() {
        while (head != nullptr) {
            Link<T>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    /*
    la funcion permite meter un elemento al final de la 
    ña lista linkeada
    */
    void insertion(T val) {
        Link<T>* newLink = new Link<T>(val);
        if (head == nullptr) {
            head = newLink;
        } else {
            Link<T>* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newLink;
        }
    }
    /*
    Imprime los elementos de la lista   
    */
    std::string toString() const {
        std::stringstream aux;
        Link<T>* p = head;

        aux << "[";
        while (p != nullptr) {
            aux << p->value;
            if (p->next != nullptr) {
                aux << ", ";
            }
            p = p->next;
        }
        aux << "]";
        return aux.str();
        // Convierte la lista en una cadena formateada
        // [elemento 1, elemento 2]
    }


    
    /*
    Busca el valor especifico en la lista 
    y  devuelve el indice si encuentra el valor si no solo 
    te devuelve -1
    */
    int search(T val) const {
        Link<T>* p = head;
        int index = 0;

        while (p != nullptr) {
            if (p->value == val) {
                return index;
            }
            p = p->next;
            index++;
        }

        return -1;
    }

    /*  
    Actualiza el valor de un elemento en la lista indicado en ña 
    posicion de index, siempre y cuando el indice sea valido 
    */
    void update(int index, T val) {
        Link<T>* p = head;
        int currentIndex = 0; // se inicializa en cero el indice
                              // actual

        while (p != nullptr && currentIndex < index) {
            p = p->next;
            currentIndex++;
        }

        if (p != nullptr) {
            p->value = val;
        }
    }
    /*  
    Elimina el elemento en la posicion de index, siempte cuando 
    esta se valida, en teoria tiene la misma estrcutra que la funcion
    update.
    */
    void deleteAt(int index) {
        if (index == 0) {   // que pasaria si el indice es 0
            if (head != nullptr) {
                Link<T>* temp = head;
                head = head->next;
                delete temp;
            }
        } else {
            Link<T>* p = head;
            int currentIndex = 0;
            // Misma estrcutra que el metedo 
            // update

            while (p != nullptr && currentIndex < index - 1) {
                p = p->next;
                currentIndex++;
            }

            if (p != nullptr && p->next != nullptr) {
                Link<T>* temp = p->next;
                p->next = p->next->next;
                delete temp;
            }
        }
    }
};

#endif /* ** */

