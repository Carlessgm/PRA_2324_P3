#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#define DICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

using namespace std;

template <typename V>
class BSTreeDict: public Dict<V>{    //Clase intermediaria entre BSTree y Dict

 private:
  BSTree<TableEntry<V>>* tree;    //ABB con elementos tipo TableEntry<V>
  
 public:
  //Método constructor: crea un ABB vacío con memoria dinámica
  BSTreeDict(){
    tree = new BSTree<TableEntry<V>>;
  }

  //Método destructor
  ~BSTreeDict(){
    delete tree;
  }

  //Imprimir el contenido del Diccionario por pantalla
  friend ostream& operator<<(ostream &out, const BSTreeDict<V> &bs){
    out << *bs.tree;
    return out;
  }

  //Actúa como interfaz al método de interfaz heredado search(string)
  V operator[](string key){
    return tree -> search(TableEntry<V>(key)).value;  //Devolvemos valor de la key
  }

  //Métodos de la interfaz Dict<V> delegando en las operaciones de la clase BSTree<V> (BSTree.h)
  void insert(string key, V value) override{
    TableEntry<V> entry(key, value); //Crea una entrada con la clave y el valor
    tree -> insert(entry); //Inserta la entrada en el ABB (usa el método insert() del fichero BSTree.h)
  }

  V search(string key) override{
    TableEntry<V> entry(key);
    return tree -> search(entry).value;
  }

  V remove(string key) override{
    V valor = tree -> search(TableEntry<V>(key)).value;
    TableEntry<V> entry(key);
    tree -> remove(entry);
    return valor;
  }

  int entries() override{
    return tree -> size();
  }
  
};

#endif
