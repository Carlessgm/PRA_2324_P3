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
		int max;	//Tamaño de la tabla hash (núm total de cubetas (cada cubeta puede contener un par clave->valor) que puede haber)
		ListLinked<TableEntry<V>> *table;	//Tabla de cubetas, array de punteros a listas enlazadas ListLinked que almacenan pares clave->valor (tipo TableEntry<V>)

		//Función hash -> Devuelve posición en tabla Hash de la clave
		int h(string key){
		  int suma = 0;
		  for(int i = 0; i < key.length(); i++){       //for del tamaño del string
		    char c = key.at(i);                        //c = cada letra del string
		    suma += int(c);                            //suma += valor ASCII de c
		  }

		  return suma % max;
		}
		
	public:
		//Método constructor -> Inicializa n y max y reserva memoria dinámica para crear una tabla "table" de tamaño size
		HashTable(int size){           
		  n = 0;
		  max = size;
		  table = new ListLinked<TableEntry<V>>[size];   //Array de ListLinked<> tamaño size. Cada elemento es una lista enlazada (puntero que apunta al siguiente) que almacenará los pares clave-valor (TableEntry<V>)
		  //table[i] representa una cubeta de la tabla hash y contiene una lista enlazada para manejar colisiones
		}

		//Método destructor
		~HashTable(){
		  delete[] table;
		}

		//Devuelve Número total de cubetas (Tamaño/Capacidad Tabla Hash)
		int capacity(){
		  return max;
		}

		//Imprime contenido de la tabla Hash
		friend ostream&operator<<(ostream &out, const HashTable<V> &th){
		  out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
		  out << "==============\n";

		  for(int i = 0; i < th.max; i++){
		    out << "\n== Cubeta " << i << " ==\n\n";
		    out << th.table[i] << "\n";
		  }

		  out << "\n==============\n";

		  return out;
		}

		//Devuelve el valor correspondiente a "key"
		 V operator[](string key){
		  int index = h(key);       //Calculamos el índice de la cubeta usando la función h (con key)

		  //Busca la clave en la lista correspondiente a la cubeta
		  int pos = table[index].search(TableEntry<V>(key));        //Llama a la función search() de ListLinked.h y busca el valor correspondiente al objeto TableEntry<V>(key), en la cubeta table[index]
		                                                           
		  if(pos != -1){  //Si clave se encuentra (search() de ListLinked.h devuelve != -1)
		    return table[index][pos].value;   //Devolver valor asociado (de la cubeta table[index], el nodo pos, su valor (será "key" en número))
		  }else{          //search() de ListLinked.h devuelve -1
		    throw runtime_error("Clave no encontrada en la tabla hash");
		  }
		}

		//Inserta el par key -> value en la cubeta correspondiente de la TablaHash
		void insert(string key, V value) override{
		  int index = h(key);      //Calculamos el índice de la cubeta usando la función h (con key)

		  //Verifica si la clave ya existe en la lista correspondiente
		  int pos = table[index].search(TableEntry<V>(key));   //pos es la posición en la lista enlazada (Nodos) donde se encuentra la clave especificada
		  if(pos != -1){
		    throw runtime_error("La Clave '" + key + "' ya existe");
		  }

		  //Si la clave no existe, insertar el nuevo par clave -> valor al principio
		  TableEntry<V> NuevaEntrada(key, value);    //Creo un nuevo nodo con key y value
		  table[index].prepend(NuevaEntrada);        //Llama a la función prepend() de ListLinked.h para añadir un nuevo Nodo al principio
		  n++;      //Número de elementos almecenados en la Tabla +1
		}

		//Devuelve el value asociado si key está en la Tabla Hash (Literalmente igual que la función V operator[](string key))
		V search(string key) override{
		  int index = h(key);         //Calculamos el índice de la cubeta usando la función (con key)

		  //Busca la clave en la lista correspondiente
		  int pos = table[index].search(TableEntry<V>(key)); //pos es la posición en la lista enlazada (Nodos) donde se encuentra la clave especificada
		  //Llama a la función search() de ListLinked.h y busca el valor correspondiente al objeto TableEntry<V>(key), en la cubeta table[index]
		  if(pos != -1){    //Si clave se encuentra (search() de ListLinked.h devuelve != -1)
		    return table[index][pos].value;     //Devolver valor asociado (de la cubeta table[index], el nodo pos, su valor (será "key" en número))
		  }else{        //search() de ListLinked.h devuelve -1
		    throw runtime_error("La Clave '" + key + "' no encontrada");
		  }
		}

		//Elimina el Nodo key-value si se encuentra en la Tabla Hash
		V remove(string key) override{
		  int index = h(key);        //Calculamos el índice de la cubeta usando la función h(con key)

		  //Busca la clave en la lista correspondiente, su posición = pos
		  int pos = table[index].search(TableEntry<V>(key));
		  if(pos != -1){
		    V value = table[index][pos].value;   //Si se encuentra la clave, guardamos el valor
		    table[index].remove(pos);            //Elimina el Nodo key-value de la lista (función remove() de ListLinked.h), en la cubeta table[index] se elimina el nodo correspondiente a la posición "pos"
		    n--;
		    return value;
		  }else{
		    throw runtime_error("La Clave '" + key +"' no encontrada");
		  }
		}

		int entries() override{       //Devuelve número de elementos almacenados que tiene la Tabla Hash
		  return n;
		}
};

#endif
