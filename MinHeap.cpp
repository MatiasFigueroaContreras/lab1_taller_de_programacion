#include "MinHeap.h"
/*
    Descripcion de la clase MinHeap:
    Esta clase representa una cola de prioridad para el valor
    minimo mediante el uso de un heap, el cual tiene la estructura
    de un arbol binario, esto implementado mediante el uso de un arreglo
    en el cual se trabaja mediante sus indices, para obtener los "nodos"
    padres e hijos. Por otra parte, esta clase permite ingresar estados
    con su respectivo puntaje, sacar el estado con menor puntaje, imprimir
    los puntajes mediante la representacion del heap y verificar si el
    heap esta vacio.
*/

/*
    Metodo: Constructor
    Descripcion: este metodo permite crear un heap con prioridad
        para los valores minimos, con un largo inicial dado.
    Parametros:
        -initialMaxLength: largo maximo de partida que tendra el heap.
    Retorno: La direccion del objeto creado.
*/
MinHeap::MinHeap(int initialMaxLength)
{
    maxLength = initialMaxLength;
    length = 0;
    cubesState = (State **)malloc(maxLength * sizeof(State *));
    scores = (int *)malloc(maxLength * sizeof(int));
}

/*
    Metodo: Destructor
    Descripcion: este metodo permite eliminar el heap,
        liberando la memoria en donde se encuentra el
        heap que contiene los puntajes y el de las
        direcciones de los estados.
    Retorno: vacio.
*/
MinHeap::~MinHeap()
{
    free(cubesState);
    free(scores);
}

/*
    Metodo:
    Descripcion: este metodo obtiene la posicion en donde se
        encuentra el hijo izquierdo, a traves del indice del
        padre.
    Parametros:
        -i: indice del valor padre.
    Retorno: la posicion del hijo izquierdo.
*/
int MinHeap::leftChildIndex(int i)
{
    return 2 * i + 1;
}

/*
    Metodo:
    Descripcion: este metodo obtiene la posicion en donde se
        encuentra el hijo derecho, a traves del indice del
        padre.
    Parametros:
        -i: indice del valor padre.
    Retorno: la posicion del hijo derecho.
*/
int MinHeap::rightChildIndex(int i)
{
    return 2 * i + 2;
}

/*
    Metodo:
    Descripcion: este metodo obtiene la posicion en donde se
        encuentra el padre, a traves del indice de alguno de
        sus 2 hijos.
    Parametros:
        -i: indice de uno de sus hijos.
    Retorno: la posicion del padre.
*/
int MinHeap::parentIndex(int i)
{
    return (i - 1) / 2;
}

/*
    Metodo:
    Descripcion: este metodo obtiene el indice del hijo con
        menor puntaje, y en caso de que no tenga hijos
        este devuelve el mismo indice dado.
    Parametros:
        -i: indice del padre.
    Retorno: la posicion del hijo con menor puntaje.
*/
int MinHeap::minChildIndex(int i)
{
    int l = leftChildIndex(i);
    int r = rightChildIndex(i);

    if (l > length)
    {
        return i;
    }
    if (r > length || scores[l] < scores[r])
    {
        return l;
    }
    else
    {
        return r;
    }
}

/*
    Metodo:
    Descripcion: este metodo hace un cambio entre los
        puntajes y estados que se encuentran en los
        indices dados.
    Parametros:
        -i: indice 1 del valor a cambiar.
        -j: indice 2 del valor a cambiar.
    Retorno: vacio.
*/
void MinHeap::swap(int i, int j)
{
    State *rTemp = cubesState[i];
    cubesState[i] = cubesState[j];
    cubesState[j] = rTemp;

    int sTemp = scores[i];
    scores[i] = scores[j];
    scores[j] = sTemp;
}

/*
    Metodo:
    Descripcion: este metodo duplica el espacio del heap
    Retorno: vacio.
*/
void MinHeap::increaseSpace()
{
    maxLength *= 2;
    scores = (int *)realloc(scores, maxLength * sizeof(int));
    cubesState = (State **)realloc(cubesState, maxLength * sizeof(State *));
}

/*
    Metodo:
    Descripcion: permite agregar un estado y el puntaje asociado a este
        al heap, de manera tal que todos los "nodos" padres tendran menor
        puntaje que los hijos.
    Parametros:
        -state: estado del cubo Rubik a ser agregado al heap
        -score: puntaje asociado a ese estado el cual permitira regular el heap.
    Retorno: vacio.
*/
void MinHeap::insert(int score, State *state)
{
    if (length == maxLength)
    {
        increaseSpace();
    }

    cubesState[length] = state;
    scores[length] = score;

    for (int i = length; i > 0 && scores[parentIndex(i)] > scores[i]; i = parentIndex(i))
    {
        swap(i, parentIndex(i));
    }

    length++;
}

/*
    Metodo:
    Descripcion: permite sacar el estado con el menor puntaje.
    Retorno: estado con el menor puntaje.
*/
State *MinHeap::pull()
{
    if (length == 0)
    {
        return nullptr;
    }
    State *min = cubesState[0];
    length--;
    cubesState[0] = cubesState[length];
    scores[0] = scores[length];

    int j;
    for (int i = 0; i < length && scores[minChildIndex(i)] != scores[i]; i = j)
    {
        j = minChildIndex(i);
        swap(i, j);
    }

    return min;
}

/*
    Metodo:
    Descripcion: este metodo permite saber si el heap esta vacio.
    Retorno:
        -true: si el heap esta vacio
        -false: si el heap no esta vacio.
*/
bool MinHeap::isEmpty()
{
    return length == 0;
}

/*
    Metodo:
    Descripcion: este metodo permite imprimir por consola
        una representacion del heap, mostrando los puntajes,
        mediante el uso de recursividad.
    Parametros:
        -i: posicion del puntaje a mostrar.
        -c: cantidad de espacios entre puntajes.
    Retorno: vacio.
*/
void MinHeap::printAux(int i, int c)
{
    if (i >= length)
    {
        return;
    }

    c += 10;
    printAux(rightChildIndex(i), c);
    std::cout << std::endl;
    for (int i = 10; i < c; i++)
    {
        std::cout << " ";
    }

    std::cout << scores[i] << "\n";
    printAux(leftChildIndex(i), c);
}

/*
    Metodo:
    Descripcion: este metodo permite imprimir por consola
        una representacion del heap, con sus puntajes.
    Retorno: vacio.
*/
void MinHeap::print()
{
    std::cout << "-----------HEAP-----------" << std::endl;
    printAux(0, 0);
    std::cout << "--------------------------" << std::endl;
}
