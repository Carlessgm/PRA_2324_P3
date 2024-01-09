#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

using namespace std;

template <typename T>
class BSNode{
 public:
  T elem;                //Elemento de tipo T almacenado en el Nodo
  BSNode<T>* left;       //Puntero al Nodo sucesor izquierdo
  BSNode<T>* right;      //Puntero al Nodo sucesor derecho

  //Método constructor -> Inicializa variables (nulos por defecto)
  BSNode(T elem, BSNode<T>* left = nullptr, BSNode<T>* right = nullptr){
    this -> elem = elem;
    this -> left = left;
    this -> right = right;
  }

  //Imprime el nodo por pantalla
  friend ostream&operator<<(ostream&out, const BSNode<T>&bsn){
    out << bsn.elem;
    return out;
  }
};

#endif
