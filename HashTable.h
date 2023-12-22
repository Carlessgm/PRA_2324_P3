#ifndef HASHTABLE_H
#define HASHTABLE_H

#define DICT_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../../P1/PRA_2324_P1/ListLinked.h"

using namespace std;

template <typename V>
class HashTable : public Dict<V> {
	private:
		int n;		//Número de elementos almacenados en la tabla hash
		int max;	//Tamaño de la tabla hash (núm total de cubetas que puede haber)
		ListLinked<TableEntry<V>> *table;	//Tabla de cubetas, array de punteros a listas enlazadas ListLinked que almacenan pares clave->valor (tipo TableEntry<V>)
		
		int h(string key){                      //Devuelve posición en tabla Hash de la clave
		  int suma = 0;
		  for(int i = 0; i < key.length(); i++){       //for del tamaño del string
		    char c = key.at(i);                        //c = cada letra del string
		    suma += int(c);                            //suma += valor ASCII de c
		  }

		  return suma % max;
		}
		
	public:
		HashTable(int size){
		  n = 0;
		  max = size;

		  table = new ListLinked<TableEntry<V>>[size];   //Array de ListLinked<> tamaño size. Cada elemento es una lista enlazada que almacenará los pares clave-valor (TableEntry<V>)
		  //table[i] representa una cubeta de la tabla hash y contiene una lista enlazada para manejar colisiones
		}

		~HashTable(){
		  delete[] table;
		}

		int capacity(){      //Devuelve Número total de cubetas (Tamaño total)
		  return max;
		}

		friend ostream&operator<<(ostream &out, const HashTable<V> &th){  //Imprime contenido de la tabla Hash
		  out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
		  out << "==============\n";

		  for(int i = 0; i < th.max; i++){
		    out << "\n== Cubeta " << i << " ==\n\n";
		    out << th.table[i] << "\n";
		  }

		  out << "\n==============\n";

		  return out;
		}

		V operator[](string key){   //Devuelve el valor correspondiente a "key"
		  int index = h(key);       //Calculamos el índice de la cubeta usando la función (con key)

		  //Busca la clave en la lista correspondiente a la cubeta
		  int pos = table[index].search(TableEntry<V>(key));        //Llama a la función search() de ListLinked.h y busca el valor correspondiente al objeto TableEntry<V>(key),
		                                                            //es decir, un objeto con this -> key = key y sin value
		  if(pos != -1){  //Su clave se encuentra
		    return table[index][pos].value;   //Devolver valor asociado
		  }else{
		    throw runtime_error("Clave no encontrada en la tabla hash");
		  }
		}

		void insert(string key, V value) override{   //Inserta el par key -> value
		  int index = h(key);      //Calculamos el índice de la cubeta usando la función (con key)

		  //Verifica si la clave ya existe en la lista correspondiente
		  int pos = table[index].search(TableEntry<V>(key));   //pos es la posición en la lista enlazada (Nodos) donde se encuentra la clave especificada
		  if(pos != -1){
		    throw runtime_error("La Clave '" + key + "' ya existe");
		  }

		  //Si la clave no existe, insertar el nuevo par clave -> valor al principio
		  TableEntry<V> NuevaEntrada(key, value);    //Creo un nuevo nodo con key y value
		  table[index].prepend(NuevaEntrada);        //Llama a la función prepend() de ListLinked.h para añadir un nuevo Nodo en la posición correspondiente
		  n++;
		}

		V search(string key) override{    //Devuelve el value asociado si key está en el diccionario
		  int index = h(key);             //Calculamos el índice de la cubeta usando la función (con key)

		  //Busca la clave en la lista correspondiente
		  int pos = table[index].search(TableEntry<V>(key)); //pos es la posición en la lista enlazada (Nodos) donde se encuentra la clave especificada
		  if(pos != -1){
		    return table[index][pos].value;     //Si la clave se encuentra, devolver el valor asociado
		  }else{
		    throw runtime_error("La Clave '" + key + "' no encontrada");
		  }
		}

		V remove(string key) override{   //Elimina el Nodo key-vallue si se encuentra
		  int index = h(key);        //Calculamos el índice de la cubeta usando la función (con key)

		  //Busca la clave en la lista correspondiente
		  int pos = table[index].search(TableEntry<V>(key));
		  if(pos != -1){
		    V value = table[index][pos].value;   //Si se encuentra la clave, guardamos el valor
		    table[index].remove(pos);            //Elimina el Nodo key-value de la lista (función remove() de ListLinked.h)
		    n--;
		    return value;
		  }else{
		    throw runtime_error("La Clave '" + key +"' no encontrada");
		  }
		}

		int entries() override{       //Devuelve número de elementos que tiene el Diccionario
		  return n;
		}
};

#endif
