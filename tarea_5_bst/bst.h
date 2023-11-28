/*
* José Eduardo Viveros Escamilla
* A01710605
* Tarea BST (Corregida)
*/

#ifndef BST_H
#define BST_H

#include <string>
#include <sstream>

template <class T> class BST;

template <class T>
class TreeNode {
private:
	T value;
	TreeNode *left, *right;

public:
	TreeNode(T);
	TreeNode(T, TreeNode<T>*, TreeNode<T>*);

	void add(T);
	bool find(T);
	void removeChilds();
	void ancestors(std::stringstream&, T) const;
	void inorder(std::stringstream&) const;
	void preorder(std::stringstream&) const;
	void postorder(std::stringstream&) const;
	void levelbylevel(std::stringstream&, const TreeNode<T>*, int) const;

	friend class BST<T>;
};
// el template se usa para poder validar el T valor 
template <class T>
TreeNode<T>::TreeNode(T val) : value(val), left(0), right(0){}


template <class T>
TreeNode<T>::TreeNode(T val, TreeNode<T> *le, TreeNode<T> *ri) : value(val), left(le), right(ri) {}

/*
*Funcion add corregida
*/

template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != 0) {
            left->add(val);  // en caso de que la condicion se cumpla no tenemos que agregar 
			                // una condicion extra, solo devolvemos add con su argumento val
        } else {
            left = new TreeNode<T>(val);
        }
    } else if (val > value) {
        if (right != 0) {
            right->add(val);
        } else {
            right = new TreeNode<T>(val);
        }
    }
    // Si val es igual a value, no hacemos nada ya que no permitimos duplicados.
}

/*
*Funcion Find corregida
*/

template <class T>
bool TreeNode<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value && left != nullptr) {
		return left->find(val); // solo retornamos left y right aputnado a find con su argumento
		                        // sin agregar un condicion extra

    } else if (val > value && right != nullptr) {
		return right->find(val);
    }
    return false;
}



template <class T>
void TreeNode<T>::removeChilds() {
	if (left != 0) {
		left->removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right->removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
void TreeNode<T>::ancestors(std::stringstream &aux, T val) const {
    if (value != val) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << value;

        if (val < value && left != nullptr) {
            left->ancestors(aux, val);
        }
        if (val > value && right != nullptr) {
            right->ancestors(aux, val);
        }
    }
}

template <class T>
void TreeNode<T>::inorder(std::stringstream &aux) const {
	if (left != 0) {
		left->inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right->inorder(aux);
	}
}
//Método inorder, recibe un stringstream y lo llena con los valores del árbol en orden.

template <class T>
void TreeNode<T>::preorder(std::stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left->preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right->preorder(aux);
	}
}
//Método preorder, recibe un stringstream y lo llena con los valores del árbol en preorden.

template <class T>
void TreeNode<T>::postorder(std::stringstream &aux) const {
	if (left != 0) {
		left->postorder(aux);
	}
	if (right != 0) {
		right->postorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
}
//Método postorder, recibe un stringstream y lo llena con los valores del árbol en postorden.

template <class T>
void TreeNode<T>::levelbylevel(std::stringstream &aux, const TreeNode<T>* node, int level) const {
    if (level == 1) {
        if (aux.tellp() != 1) {
            aux << " ";
        }
        aux << node->value;
    } else if (level > 1) {
        if (node->left != nullptr) {
            levelbylevel(aux, node->left, level - 1);
        }
        if (node->right != nullptr) {
            levelbylevel(aux, node->right, level - 1);
        }
    }


};



//********************************************************************************************************/

template <class T>
class BST {
private:
	TreeNode<T> *root;

public:
	BST();
	~BST();

	bool empty() const;
	void add(T);
	bool find(T) const;
	void removeAll();
	std::string preorder() const;
	std::string inorder() const;
	std::string postorder() const;
	std::string levelbylevelstring() const;
	std::string visit() const;
	int height() const;
	int heightAux(const TreeNode<T>*) const;
	std::string ancestors(T) const;
	int whatlevelamI(T) const;
	int findLevel(TreeNode<T>*, T, int) const;
};

template <class T>
BST<T>::BST() : root(0) {}

template <class T>
BST<T>::~BST() {
    removeAll();
}

template <class T>
void BST<T>::removeAll() {
	if (root != 0) {
		root->removeChilds();
	}
	delete root;
	root = 0;
}

template <class T>
bool BST<T>::empty() const {
	return (root == 0);
}

// Agrega un elemento al árbol
template <class T>
void BST<T>::add(T value) {
    if (empty()) {
        root = new TreeNode<T>(value);
    } else {
        root->add(value);
    }
}

// Busca un elemento en el árbol
template <class T>
bool BST<T>::find(T value) const {
    if (empty()) {
        return false;
    } else {
        return root->find(value);
    }
}

/*
* Funciones corregidas
* Agregue [] en la salidas de preorder, postorder, inorder y
* level by level
*/

// Recorrido en preorden
template <class T>
std::string BST<T>::preorder() const {
    std::stringstream ss;
    if (empty()) {
        return "";
    } else {
		ss << "[";  // Agregados
        root->preorder(ss);
    }
	ss << "]"; // Agregados
	return ss.str();
}

// Recorrido en orden (inorden)
template <class T>
std::string BST<T>::inorder() const {
    std::stringstream ss;
	if (empty()) {
        return "";
    } else {
	    ss << "["; // Agregados
        root->inorder(ss);
    }
	ss << "]"; // Agregados
	return ss.str();
}

template <class T>
std::string BST<T>::postorder() const {
	std::stringstream ss;

	ss << "["; // Agregados
	if (!empty()) {
		root->postorder(ss);
	}
	ss << "]";// Agregados
	return ss.str();
}

// Recorrido nivel por nivel
template <class T>
std::string BST<T>::levelbylevelstring() const {
    std::stringstream ss;
    if (empty()) {
        return "";
    } else {
        int height = this->height();
        ss << "[";  // Agregados
        for (int i = 1; i <= height; i++) {
			root->levelbylevel(ss, root, i);
        }
		ss << "]"; // Agregados
        return ss.str();
    }
}

template <class T>
std::string BST<T>::visit() const {
    std::stringstream ss;    
    ss << preorder() << "\n";
	ss << inorder() << "\n";
    ss << postorder() << "\n";
    ss << levelbylevelstring();

    return ss.str();
}



// Función de utilidad para calcular la altura
template <class T>
int BST<T>::heightAux(const TreeNode<T>* node) const {
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = heightAux(node->left);
    int rightHeight = heightAux(node->right);

    return std::max(leftHeight, rightHeight) + 1;
}

template <class T>
int BST<T>::height() const {
    return heightAux(root);
}

template <class T>
std::string BST<T>::ancestors(T val) const {
    std::stringstream aux;
	if (!find(val)) {
		return "[]";
	}
    aux << "[";
    root->ancestors(aux, val);
    aux << "]";
    return aux.str();
}

template <class T>
int BST<T>::whatlevelamI(T val) const {
    return findLevel(root, val, 1);
}

template <class T>
int BST<T>::findLevel(TreeNode<T>* node, T val, int level) const {
    if (node == nullptr) {
        return -1;
    }

    if (val == node->value) {
        return level;
    } else if (val < node->value) {
        return findLevel(node->left, val, level + 1);
    } else {
        return findLevel(node->right, val, level + 1);
    }
}

#endif