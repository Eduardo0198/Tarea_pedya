/*
José Eduardo Viveros Escamilla
*/

#ifndef QUADRATIC_H
#define QUADRATIC_H

#include <string>
#include <sstream>


template <class Key, class Value>
class Quadratic {
	private:
		// Puntero a función para la función hash
		unsigned int (*func)(const Key);
		// Tamaño de la tabla hash
		unsigned int size;
		// Número de elementos en la tabla hash
		unsigned int count;

		// Arreglos para almacenar claves y valores
		Key *keys;
		Key initialValue;
		Value *values;

		// Método privado para encontrar el índice de una clave en la tabla hash
		long indexOf(const Key) const;

	public:
		// Constructor
		Quadratic(unsigned int, Key, unsigned int (*f) (const Key));
		// Destructor
		~Quadratic();

		// Métodos
		void clear(); // Limpiar la tabla hash

		bool full() const; // Verificar si la tabla hash está llena
		bool put(Key, Value); // Insertar un par clave-valor en la tabla hash
		Value get(const Key); // Recuperar el valor asociado con una clave

		std::string toString() const; // Convertir la tabla hash a una cadena de texto
};

// Implementación del constructor
template <class Key, class Value>
Quadratic<Key, Value>::Quadratic(unsigned int sze, Key init, unsigned int (*f) (const Key)) {
	// Inicializamos el tamaño, los arreglos de claves y valores
	size = sze;
	keys = new Key[size];

	// Verificamos si la asignación de memoria es exitosa
	if (keys == 0) {
		return;
	}
    	if (keys == 0) {
		return;
	}

	// Inicializamos las claves con el valor inicial
	initialValue = init;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = init;
	}
	
	// Inicializamos el arreglo de valores
	values = new Value[size];

	// Verificamos si la asignación de memoria es exitosa
	if (values == 0) {
		return;
	}

	// Inicializamos los valores con cero
	for (int i = 0; i  < sze; i++){
		values[i] = 0;
	}

	// Asignamos la función hash
	func = f;
	count = 0;
}

// Implementación del destructor
template <class Key, class Value>
Quadratic<Key, Value>::~Quadratic() {
	// Liberamos la memoria de los arreglos
	delete[] keys;
	keys = nullptr;
	delete[] values;
	values = nullptr;
	size = 0;
	func = nullptr;
	count = 0;
}

// Método para verificar si la tabla hash está llena
template <class Key, class Value>
bool Quadratic<Key, Value>::full() const {
	return (count > size);
}

// Método para encontrar el índice de una clave en la tabla hash
template <class Key, class Value>
long Quadratic<Key, Value>::indexOf(const Key k) const {
	unsigned int i, start;

	start = i = func(k) % size;
	do {
		if (keys[i] == k) {
			return i;
		}
		i = (i + 1) % size;
	} while (start != i);
	return -1;
}

// Método para insertar una clave-valor en la tabla hash
template <class Key, class Value>
bool Quadratic<Key, Value>::put(Key k, Value v) {
	unsigned int i, start, c = 1;
	long pos;

	if (full()) {
		return false;
	}

	pos = indexOf(k);
	if (pos != -1) {
		values[pos] = v;
		return true;
	}

	start = i = func(k) % size;
	do {
		if (keys[i] == initialValue) {
			keys[i] = k;
			values[i] = v;
			count++;
			return true;
		}
		i = (start + c * c) % size;
		c++;
	} while (start != i);
	return false;
}

// Método para recuperar el valor asociado con una clave
template <class Key, class Value>
Value Quadratic<Key, Value>::get(const Key k) {
	long pos = indexOf(k);

	if (pos != -1) {
		return values[pos];
	}
	return -1;
}

// Método para limpiar la tabla hash
template <class Key, class Value>
void Quadratic<Key, Value>::clear() {
	count = 0;
	for (unsigned int i = 0; i < size; i++) {
		keys[i] = initialValue;
	}
}

// Método para convertir la tabla hash a una cadena de texto
template <class Key, class Value>
std::string Quadratic<Key, Value>::toString() const {
	std::stringstream aux;

	for (unsigned int i = 0; i < size; i++) {
		if(keys[i] != initialValue)
			aux << "(" << i << " " << keys[i] << " : " << values[i] << ") ";
	}

	return aux.str();
}

#endif


	