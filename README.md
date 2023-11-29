# Tarea_pedya

## Tarea 5 (BST)

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
Tenia dos errores de sintaxis en la funcion find en la clase TreeNode<T>
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
        if (left != 0) {
            left->add(val);
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

## Tarea 9 (SPLAY TREE)

Esta vez no hay problemas en la compilacion, sin embargo hay unos casos que no estan saliendo como el caso 5B y el 6B, en los que podemos ver que los metodos estan mal y no el formato pues la salida es diferente a la que en teoria deberiamos que recibir:
```
5.- esperada [15 7 10 16 17]
 programa [17 16 15 7 10]
fail

6.- esperada [15 7 10 17]
 programa [17 15 7 10]
fail
```
Al inicio crei que el problema se podria encontar en el preorder, sin embargo en la retro de la tarea me marcaba como error en un caso del remove. 
```
add success
find success
find success
find success
find success
find success
find success
remove success
 remove fail
remove success
remove success
```
Al ver los casos 5 y 6 podemos notar que se implementan de la misma manera en el main, por lo que mi funcion de remove no esta mal del todo, sin embargo en la forma de implementarlo es donde habia problemas.
Ahora sabes que...

 ### Caso 5:
*Se llama a remove(13), y se identifica el nodo con valor 13 para su eliminación.
*El sucesor (el siguiente valor en orden) de 13 es el nodo 15.
*Se realiza la operación remove en el nodo 13, y el sucesor (15) reemplaza al nodo eliminado.
*La operación splay se realiza para asegurar que el nodo recién insertado o manipulado (en este caso, el nodo 15) esté en la raíz.

#### Caso 6:
*Se llama a remove(16), y se identifica el nodo con valor 16 para su eliminación.
*El sucesor (el siguiente valor en orden) de 16 es el nodo 17.
*Se realiza la operación remove en el nodo 16, y el sucesor (17) reemplaza al nodo eliminado.
*La operación splay se realiza para asegurar que el nodo recién insertado o manipulado (en este caso, el nodo 17) esté en la raíz.

### Comportamiento de remove corregida
Si el valor a eliminar (val) es menor que el valor del nodo actual (value):

Se verifica si el hijo izquierdo (left) existe.
Si el hijo izquierdo tiene el valor que se va a eliminar, se procede a reemplazar el nodo con su sucesor (si tiene ambos hijos) o con su hijo derecho o izquierdo, según corresponda.
Se ajustan las conexiones para mantener la estructura del árbol.
Si no hay hijo izquierdo, no hay nada que hacer.
Si el valor a eliminar (val) es mayor que el valor del nodo actual (value):
```
if (val < value) {
      if (left != 0) {
        if (left->value == val) { //verifica que el hijo exista
          old = left;
          if (old->left != 0 && old->right != 0) {
            succ = left->succesor();
            succ->left = old->left;
            succ->left->parent = succ;
            succ->right = old->right;
            succ->right->parent = succ;
          } else if (old->right != 0) {
            old->right->parent = left->parent;
            left = old->right;
            return this;
          } else if (old->left != 0) {
            old->left->parent = left->parent;
            left = old->left;
            return this;
          } else {
            left = 0;
            return this;
          }
        } else {
          return left->remove(val);
        }
      }
```
Se verifica si el hijo derecho (right) existe.
Si el hijo derecho tiene el valor que se va a eliminar, se procede de manera similar a la lógica anterior.
Se ajustan las conexiones para mantener la estructura del árbol.
Si no hay hijo derecho, no hay nada que hacer.
Si el valor a eliminar es igual al valor del nodo actual, significa que se ha encontrado el nodo a eliminar.
```
else if (val > value) {
      if (right != 0) {
        if (right->value == val) { //verifica si el hijo derecho existe
          old = right;
          if (old->left != 0 && old->right != 0) {
            succ = right->succesor();
            succ->left = old->left;
            succ->left->parent = succ;
            succ->right = old->right;
            succ->right->parent = succ;
          } else if (old->right != 0) {
            old->right->parent = right->parent;
            right = old->right;
            return this;
          } else if (old->left != 0) {
            old->left->parent = right->parent;
            right = old->left;
            return this;
          } else {
            right = 0;
            return this;
          }
        } else {
          return right->remove(val);
        }
      }
    }
```
Basicamente el codigo esta hecho para encontrar el sucesor y reemplazar el nodo actual con el sucesor (si tiene ambos hijos) o con su hijo derecho o izquierdo, según corresponda.
Se ajustan las conexiones para mantener la estructura del árbol.
Al final, la función retorna el nodo actual (que puede haber sido modificado durante la operación), con un:
```
return this;
```
Con este cambio en el metodo remove de Node hace que el caso 5By 6B corran con success :D
