#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree{
 private:
  int nelem;            //Número de elementos almacenados en el ABB
  BSNode<T> *root;      //Nodo raíz del ABB

  //Método recursivo que busca el elemento "e" en el ABB
  BSNode<T>* search(BSNode<T>* n, T e) const{
    if(n == nullptr){
        throw runtime_error("Elemento no encontrado en el ABB");
    } else if(n -> elem < e){            //Si "e" es mayor que n->elem, se busca hacia la derecha
        return search(n -> right, e);
    } else if(n -> elem > e){            //Si "e" es mayor que n->elem, se busca hacia la izquierda
        return search(n -> left, e);
    } else{
        return n;
    }
  }

  //Método recursivo que inserta el elemento "e" en el ABB
  BSNode<T>* insert(BSNode<T>* n, T e){
    if(n == nullptr){            //Al llegar al Nodo final, ya sea por derecha o izquierda, insertamos nuevo Nodo con el elemento "e"
        nelem++;
        return new BSNode<T>(e);
    } else if(n -> elem == e){   //Si el elemento "e" ya se encuentra en el ABB, envío error
        throw runtime_error("Elemento duplicado en el ABB");
    } else if(n -> elem < e){    //Si "e" es mayor que n->elem vamos por la derecha
        n -> right = insert(n -> right, e);
    } else{                      //Si "e" es menor que n->elem vamos por la izquierda
        n -> left = insert(n -> left, e);
    }

    return n;                   //Devuelve el Nodo raíz del Nodo donde se encuentra el elemento "e"
  }

  //Método recursivo para el recorrido inorden para mostrar a través de "out" los elementos del ABB
  void print_inorder(ostream &out, BSNode<T>* n) const{
    if(n != nullptr){
      print_inorder(out, n -> left);
      out << n -> elem << " ";
      print_inorder(out, n -> right);
    }
  }

  //Método recursivo para la eliminación de elementos
  BSNode<T>* remove(BSNode<T>* n, T e){
    if(n == nullptr){
        throw runtime_error("Elemento no encontrado en el ABB");
    } else if(n -> elem < e){
        n -> right = remove(n -> right, e);
    } else if(n -> elem > e){
        n -> left = remove(n -> left, e);
    } else{
        if(n -> left != nullptr && n -> right != nullptr){       //Tiene 2 descendientes
	    n -> elem = max(n -> left);
	    n -> left = remove_max(n -> left);
        } else{                                                  //Tiene 1 o 0 descendientes
	    BSNode<T>* temp = (n -> left != nullptr) ? n -> left : n -> right;
	    delete n;
	    return temp;
	}
    }
    return n;
  }

  //Método recursivo que devuelve el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n
  T max(BSNode<T>* n) const{
    if(n == nullptr){
        throw runtime_error("Elemento no encontrado en el ABB");
    } else if(n -> right != nullptr){
        return max(n -> right);
    } else{
      return n -> elem;
    }
  }

  //Método recursivo que elimina el elemento de máximo valor contenido en el (sub-)árbol cuya raíz es n
  BSNode<T>* remove_max(BSNode<T>* n){
    if(n -> right == nullptr){
        BSNode <T>* temp = n -> left;
        delete n;
        return temp;
    } else{
        n -> right = remove_max(n -> right);
        return n;
    }
  }

  //Método recursivo para liberación de la memoria dinámica ocupada por los objetos de tipo BSNode<T> que conforman el (sub-)árbol cuya raíz es n
  void delete_cascade(BSNode<T>* n){
    if(n != nullptr){
      delete_cascade(n -> left);
      delete_cascade(n -> right);
      delete n;
    }
  }
  
 public:
  
  BSTree(){             //Crea un ABB vacío
    nelem = 0;
    root = nullptr;
  }

  int size() const{     //Devuelve el número de elementos del ABB
    return nelem;
  }

  //Función lanzadera (Simplemente llama a la función que busca el elemento)
  T search(T e) const{
    return search(root, e) -> elem; //La función search privada devuelve el Nodo donde se encuentra "e", por eso, de esa función nos tenemos que queda con el elemento (que será "e" si se ha encontrado)
  }

  //Función que actúa como interfaz al método search(T e), una manera más cómoda de llamarla
  T operator[](T e) const{
    return search(e);
  }

  //Función lanzadera (Simplemente llama a la función que inserta el elemento "e")
  void insert(T e){
    root = insert(root, e);
  }

  //Sobrecarga del operador << para mostrar a través de "out" los contenidos del ABB realizando recorrido inorden
  friend ostream& operator<<(ostream &out, const BSTree<T> &bst){
    bst.print_inorder(out, bst.root);
    return out;
  }

  //Función lanzadera (Llama a la función para eliminar un elemento)
  void remove(T e){
    root = remove(root, e);
    nelem--;
  }

  //Método destructor
  ~BSTree(){
    delete_cascade(root);
  }
  
};

#endif
