#include "HashTable.h"
/*
    Metodo: Constructor
    Descripcion: este metodo permite crear una tabla de hash
        con el largo dado.
    Parametros:
        -maxLenght: largo maximo que tendra la tabla de hash.
    Retorno: La direccion del objeto creado.
*/
HashTable::HashTable(int maxLenght){
    table = (LinkedList **)malloc(maxLenght * sizeof(LinkedList *));
    for (int i = 0; i < maxLenght; i++){
        table[i] = new LinkedList();
    }
    length = maxLenght;
}

/*
    Metodo: Destructor
    Descripcion: este metodo permite eliminar la tabla de hash,
        liberando la memoria en donde se encuentra esta.
    Retorno: vacio.
*/
HashTable::~HashTable(){
    for (int i = 0; i < length; i++){
        delete table[i];
    }
    free(table);
}

/*
    Metodo: 
    Descripcion: este metodo calcula la posicion en la tabla,
        de hash en base a una llave.
    Parametros:
        -key: llave numerica que permite calcular la posicion
            en la tabla de hash.
    Retorno: posicion en la table de hash.
*/
int HashTable::hashFunction(int key){
    return key % length;
}

/*
    Metodo:
    Descripcion: permite agregar la direccion de un cubo Rubik
        a la tabla de hash, obteniendo el valor entero de este.
    Parametros:
        -cube: cubo a ser agregado a la tabla de hash.
    Retorno: vacio.
*/
void HashTable::add(Rubik *cube){
    int code = cube->getValue();
    int i = hashFunction(code);
    table[i]->insert(cube, code);
}

/*
    Metodo:
    Descripcion: permite saber si el cubo dado esta en la
        tabla de hash.
    Parametros:
        -cube: cubo a revisar en la tabla de hash.
    Retorno:
        -true: si el cubo esta en la tabla de hash.
        -false: si el cubo no esta en la tabla de hash.
*/
bool HashTable::isInTable(Rubik *cube){
    int code = cube->getValue();
    int i = hashFunction(code);
    return table[i]->isInList(cube, code);
}
