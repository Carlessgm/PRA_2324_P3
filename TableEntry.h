#ifndef TABLEENTRY_H
#define	TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V>
class TableEntry{
	public:
		string key;
		V value;

		//Método constructor de Clave y Valor
		TableEntry(string key, V value){
			this -> key = key;
			this -> value = value;
		}

		//Crea una entrada solo con clave (sin valor)
		TableEntry(string key){
			this -> key = key;
		}

		//Crea una entrada con la clave siendo una cadena vacía (sin valor)
		TableEntry(){
			key = "";
		}

		//Devuelve 1 si las claves son iguales o 0 si no lo son
		friend bool operator==(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key == te2.key){
				return 1;
			}else{
				return 0;
			}
		}

		//Devuelve 1 si las claves son diferentes o 0 si no lo son
		friend bool operator!=(const TableEntry<V> &te1, const TableEntry<V> &te2){
			if(te1.key != te2.key){
				return 1;
			}else{
				return 0;
			}
		}

		//Imprime por pantalla la Clave y el Valor del "par" (te)
		friend ostream&operator<<(ostream &out, const TableEntry<V> &te){
			out << "(Clave -> '" << te.key << "' => Valor ->  " << te.value << ")";
			return out;
		}
};

#endif
