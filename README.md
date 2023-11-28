# Tarea_pedya

## Tarea 5

Error en la compilacion
```
In file included from main.cpp:11:0:
bst.h: In member function 'bool TreeNode<T>::find(T)':
bst.h:68:27: error: expected ')' before '->' token
   return (left !=  && left->find(val));
                           ^~
bst.h: In instantiation of 'bool TreeNode<T>::find(T) [with T = int]':
bst.h:235:32:   required from 'bool BST<T>::find(T) const [with T = int]'
bst.h:325:11:   required from 'std::__cxx11::string BST<T>::ancestors(T) const [with T = int; std::__cxx11::string = std::__cxx11::basic_string<char>]'
main.cpp:42:78:   required from here
bst.h:68:20: error: label 'left' used but not defined
   return (left !=  && left->find(val));
                    ^~~~~~~ 
zip/test/bst.h:45:15: error: âTâ was not declared in this scope
   45 | void TreeNode<T>::add(T val) {
      |               ^
zip/test/bst.h:45:16: error: template argument 1 is invalid
   45 | void TreeNode<T>::add(T val) {
      |                ^
zip/test/bst.h:45:6: error: variable or field âaddâ declared void
   45 | void TreeNode<T>::add(T val) {
      |      ^~~~~~~~~~~
zip/test/bst.h:45:23: error: âTâ was not declared in this scope
   45 | void TreeNode<T>::add(T val) {
```
1. Tenia dos errores de sintaxis en la funcion find en la clase TreeNode<T>
```
return (left != && left->find(val));.
```
La comparación != requiere un operando a la izquierda y a la derecha, pero aquí falta el operando a la izquierda. La condición debería ser:
```
return (left != nullptr && left->find(val));
```
Sin embargo hubo otro error ya que right o left parecia que no que maneja de forma correcta el nullptr asi que decidi omitirlo y dejarlo con solo con el left->find(val), por lo tanto tendria que cambiar las declaraciones de find y add que estaban trabajando con el left != nullptr, en el caso de add en las condiciones le puse 0 y si la condicion se cumple te regresa left->add(val) quedando:
```
FIND
template <class T>
bool TreeNode<T>::find(T val) {
    if (val == value) {
        return true;
    } else if (val < value && left != nullptr) {
        return left->find(val);
    } else if (val > value && right != nullptr) {
        return right->find(val);
    }
    return false;
}

ADD
template <class T>
void TreeNode<T>::add(T val) {
    if (val < value) {
        if (left != nullptr) {
            left->add(val);
        } else {
            left = new TreeNode<T>(val);
        }
    } else if (val > value) {
        if (right != nullptr) {
            right->add(val);
        } else {
            right = new TreeNode<T>(val);
        }
    }
    // Si val es igual a value, no hacemos nada ya que no permitimos duplicados.
}
```
Otro que pude notar fue la salida del programa en los casos 1 y 3, el cual ocupan la funcion de visit, la cual esta conformada por preorder, inorder, postorder y level by level.
```
template <class T>
std::string BST<T>::visit() const {
    std::stringstream ss;    
    ss << preorder() << "\n";
	 ss << inorder() << "\n";
    ss << postorder() << "\n";
    ss << levelbylevelstring();

    return ss.str();
}
```
Como tal la logica de la funciones no estaba mal hecha, es decir que la salida era correcta, sin embargo el formato no lo era pues me hacian falta las []:
```
CASO 1
1.- esperada [10]
[10]
[10]
[10]
 programa 10
 10
[10]
 10
fail

CASO 2
3.- esperada [10 8 12 110 18 112]
[8 10 12 18 110 112]
[8 18 112 110 12 10]
[10 8 12 110 18 112]
 programa 10 8 12 110 18 112
 8 10 12 18 110 112
[8 18 112 110 12 10]
 10 8 12 110 18 112
fail
```
Lo unico que tuve que hacer fue agregar los [] en los metodos del BST, en el codigo es se visualiza de manera mas sencilla, sin embargo les muestro un ejemplo de como quedo el preorder:
```
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
```
Una vez con estas correcciones el bst.h hace que corra bien el main con todos los casos como success :)

## Tarea 9

Esta vez no hay problemas en la compilacion, sin embargo hay unos casos que no estan saliendo como el caso 5 y el 6B, en los que podemos ver que los metodos estan mal y no el formato pues la salida es diferente a la que en teoria deberiamos que recibir:
```
5.- esperada [15 7 10 16 17]
 programa [17 16 15 7 10]
fail

6.- esperada [15 7 10 17]
 programa [17 15 7 10]
fail
```
