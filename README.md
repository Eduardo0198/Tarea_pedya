# Tarea_pedya

## Tarea 8

Error en la compilacion
´´´
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

´´´
1. Tenia dos errores de sintaxis en la funcion find en la clase TreeNode<T>
´´´
return (left != && left->find(val));.
´´´
La comparación != requiere un operando a la izquierda y a la derecha, pero aquí falta el operando a la izquierda. La condición debería ser:
´´´
return (left != nullptr && left->find(val));
´´´
Sin embargo hubo otro error ya que right o left parecia que no que maneja de forma correcta el nullptr asi que decidi omitirlo y dejarlo con solo con el left->find(val), por lo tanto tendria que cambiar las declaraciones de find y add que estaban trabajando con el left != nullptr, quedando:
´´´
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

´´´




















