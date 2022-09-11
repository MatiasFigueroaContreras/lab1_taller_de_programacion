#include "RubikSolver.h"
/*
    Descripcion de la clase RubikSolver:
    Esta clase busca resolver un cubo Rubik mediante
    el algoritmo A* de una forma eficiente.
*/

RubikSolver::RubikSolver()
{
}

RubikSolver::~RubikSolver()
{
}

/*
    Metodo:
    Descripcion: este metodo permite resolver un cubo Rubik dado,
        aplicando el algoritmo A*, y imprimiendo por consola los
        pasos que tomo para resolverlo.
    Parametros:
        -startingCube: Rubik a resolver.
    Retorno: vacio.
*/
void RubikSolver::solve(Rubik *startingCube)
{
    State *current, *neighborState;
    char faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    int cws[2] = {1, -1};               // Sentidos del reloj para los movimientos.
    MinHeap *open = new MinHeap(10000); // Heap del cual se obtendran los estados de cubo Rubik más cercanos a la solucion.
    HashTable *openHash = new HashTable(100000);
    HashTable *closed = new HashTable(10000); // Tabla de Hash en la cual se consultaran los cubos Rubik ya visitados.
    State *startingState = new State(startingCube, nullptr, 0, ' ', 0);
    open->insert(0, startingState);
    while (!open->isEmpty())
    {
        current = open->pull();

        if (current->cube->isSolved())
        {
            current->printPath();
            return;
        }

        for (int i = 0; i < 6; i++)
        {
            // Se iteran los posibles movimientos
            for (int j = 0; j < 2; j++)
            {
                // Se itera el sentido de los movimientos
                if (current->move != faces[i] || current->cw == cws[j])
                {
                    Rubik *neighborCube = current->cube->rotate(cws[j], faces[i]);
                    if (!closed->isInTable(neighborCube) && !openHash->isInTable(neighborCube))
                    {
                        neighborState = new State(neighborCube, current, current->depth + 1, faces[i], cws[j]);
                        open->insert(current->depth + 1, neighborState); // Falta agregarle el valor heuristico
                        openHash->add(neighborCube);
                    }
                    else
                    {
                        delete neighborCube;
                    }
                }
            }
        }
        closed->add(current->cube);
    }
}

/*

*/
State *RubikSolver::partialSolve(State *startingState, int step)
{
    State *current, *neighborState;
    char faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    int cws[2] = {1, -1};                // Sentidos del reloj para los movimientos.
    MinHeap *open = new MinHeap(100000); // Heap del cual se obtendran los estados de cubo Rubik más cercanos a la solucion.
    HashTable *openHash = new HashTable(100000);
    HashTable *closed = new HashTable(1000000); // Tabla de Hash en la cual se consultaran los cubos Rubik ya visitados.
    open->insert(0, startingState);

    while (!open->isEmpty())
    {
        current = open->pull();

        if (stopPoint(current->cube, step))
        {
            return current;
        }

        for (int i = 0; i < 6; i++)
        {
            // Se iteran los posibles movimientos
            for (int j = 0; j < 2; j++)
            {
                // Se itera el sentido de los movimientos
                if (current->move != faces[i] || current->cw == cws[j])
                {
                    Rubik *neighborCube = current->cube->rotate(cws[j], faces[i]);
                    if (!closed->isInTable(neighborCube) && !openHash->isInTable(neighborCube))
                    {
                        neighborState = new State(neighborCube, current, current->depth + 1, faces[i], cws[j]);
                        int h = heuristicValue(neighborCube, step);
                        // std::cout << "Valor Heuristico: " << h << " Profundidad: " << current->depth + 1 << std::endl; 
                        open->insert(current->depth + 1 + h, neighborState);
                        openHash->add(neighborCube);
                    }
                    else
                    {
                        delete neighborCube;
                    }
                }
            }
        }
        closed->add(current->cube);
    }

    return nullptr;
}

bool RubikSolver::stopPoint(Rubik *cube, int step)
{
    switch (step)
    {
    case 1:
        return whiteCross(cube);
        break;
    case 2:
        return whiteComplete(cube);
        break;
    case 3:
        return middleComplete(cube) && whiteComplete(cube);
    case 4:
        return middleComplete(cube) && whiteComplete(cube) && yellowCross(cube);
    default:
        return false;
        break;
    }
}

bool RubikSolver::whiteCross(Rubik *cube)
{
    return cube->D[0][1] == 37 &&
           cube->D[1][0] == 37 &&
           cube->D[1][2] == 37 &&
           cube->D[2][1] == 37 &&
           cube->F[2][1] == 31 &&
           cube->R[2][1] == 32 &&
           cube->B[2][1] == 35 &&
           cube->L[2][1] == 34;
}

bool RubikSolver::whiteComplete(Rubik *cube)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (cube->D[i][j] != 37)
            {
                return false;
            }
        }
        if (cube->F[2][i] != 31 ||
            cube->R[2][i] != 32 ||
            cube->B[2][i] != 35 ||
            cube->L[2][i] != 34)
        {
            return false;
        }
    }
    return true;
}

bool RubikSolver::middleComplete(Rubik *cube)
{
    for (int i = 0; i < 3; i++)
    {
        if (cube->F[1][i] != 31 ||
            cube->R[1][i] != 32 ||
            cube->B[1][i] != 35 ||
            cube->L[1][i] != 34)
        {
            return false;
        }
    }

    return true;
}

bool RubikSolver::yellowCross(Rubik *cube)
{
    return cube->U[0][1] == 33 &&
           cube->U[1][0] == 33 &&
           cube->U[1][2] == 33 &&
           cube->U[2][1] == 33;
}

int RubikSolver::heuristicValue(Rubik *cube, int step)
{
    switch (step)
    {
    case 1:
        return whiteCrossHeuristic(cube);
        break;
    case 2:
        return whiteCrossHeuristic(cube) + whiteCompleteHeuristic(cube);
        break;
    case 3:
        return 0;
    case 4:
        return 0;
    default:
        return 0;
        break;
    }
}

int RubikSolver::whiteCrossHeuristic(Rubik *cube)
{
    int i, j, dist;
    int value = 0;
    int count = 4;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int ***mFaces = new int **[2];
    mFaces[0] = cube->D;
    mFaces[1] = cube->U;

    int colors[4] = {31, 32, 35, 34};
    for (int k = 0; k < 4 && count != 0; k++)
    {
        if (facesH[k][0][1] == 37 || facesH[k][2][1] == 37)
        {
            value += 3;
            count--;
        }

        if (facesH[k][1][0] == 37)
        {
            i = leftFaceIndex(k);
            j = getIndex(colors, facesH[i][1][2]);
            dist = distance(i, j);
            value += dist + 1;
            count--;
        }

        if (facesH[k][1][2] == 37)
        {
            i = rightFaceIndex(k);
            j = getIndex(colors, facesH[k][1][0]);
            dist = distance(i, j);
            value += dist + 1;
            count--;
        }
    }

    for (int k = 0; k < 2 && count != 0; k++)
    {
        if (mFaces[k][0][1] == 37)
        {
            j = getIndex(colors, facesH[0][2 - 2 * k][1]);
            dist = distance(0, j);
            value += dist + 2 * k;
            count--;
        }

        if (mFaces[k][1][2] == 37)
        {
            j = getIndex(colors, facesH[1][2 - 2 * k][1]);
            dist = distance(1, j);
            value += dist + 2 * k;
            count--;
        }

        if (mFaces[k][2][1] == 37)
        {
            j = getIndex(colors, facesH[2][2 - 2 * k][1]);
            dist = distance(2, j);
            value += dist + 2 * k;
            count--;
        }

        if (mFaces[k][1][0] == 37)
        {
            j = getIndex(colors, facesH[3][2 - 2 * k][1]);
            dist = distance(3, j);
            value += dist + 2 * k;
            count--;
        }
    }

    delete[] facesH;
    delete[] mFaces;

    return value;
}

int RubikSolver::whiteCompleteHeuristic(Rubik *cube)
{
    int left, right, dist, color, colorFace;
    int value = 0;
    int count = 4;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {31, 32, 35, 34};
    for (int k = 0; k < 4 && count != 0; k++)
    {
        if (facesH[k][0][0] == 37)
        {
            left = leftFaceIndex(k);
            color = facesH[left][0][2];
            colorFace = getIndex(colors, color);
            right = rightFaceIndex(colorFace);
            value += distance(left, colorFace);
            if(facesH[colorFace][1][2] != color || facesH[right][1][0] != 37){
                // Si el valor del borde no esta en la posicion que permite
                //  colocar la esquina en su posicion, entonces la cantidad
                //  estimada a subir de movimientos es 3 + la distancia.
                value += 3;
            }
            count--;
        }

        if (facesH[k][0][2] == 37)
        {
            right = rightFaceIndex(k);
            color = facesH[right][0][0];
            colorFace = getIndex(colors, color);
            left = leftFaceIndex(colorFace);
            value += distance(right, colorFace);
            if (facesH[colorFace][1][0] != color || facesH[left][1][2] != 37)
            {
                // Si el valor del borde no esta en la posicion que permite
                //  colocar la esquina en su posicion, entonces la cantidad
                //  estimada a subir de movimientos es 3 + la distancia.
                value += 3;
            }
            count--;
        }

        if (facesH[k][2][0] == 37)
        {
            left = leftFaceIndex(k);
            color = facesH[left][2][2];
            colorFace = getIndex(colors, color);
            dist = distance(left, colorFace);
            if(dist != 0 || facesH[colorFace][1][2] != color || facesH[k][1][0] != 37){
                // Si el la esquina no esta en la posicion al lado del borde blanco
                //  más su color, entonces tomara aproximadamente 7 movimientos
                value += 7;
            }
            count--;
        }

        if (facesH[k][2][2] == 37)
        {
            right = rightFaceIndex(k);
            color = facesH[right][2][0];
            colorFace = getIndex(colors, color);
            dist = distance(right, colorFace);
            if (dist != 0 || facesH[colorFace][1][0] != color || facesH[k][1][2] != 37)
            {
                // Si el la esquina no esta en la posicion al lado del borde blanco
                //  más su color, entonces tomara aproximadamente 7 movimientos
                value += 7;
            }
            count--;
        }
    }

    if (count != 0 && cube->U[0][0] == 37)
    {
        color = facesH[2][0][2];
        colorFace = getIndex(colors, color);
        dist = distance(2, colorFace);
        value += 7;
        if (dist == 1)
        {
            value += 1;
        }
        count--;
    }
    if (count != 0 && cube->U[0][2] == 37)
    {
        color = facesH[2][0][0];
        colorFace = getIndex(colors, color);
        dist = distance(2, colorFace);
        value += 7;
        if (dist == 1)
        {
            value += 1;
        }
        count--;
    }
    if (count != 0 && cube->U[2][0] == 37)
    {
        color = facesH[0][0][0];
        colorFace = getIndex(colors, color);
        dist = distance(0, colorFace);
        value += 7;
        if (dist == 1)
        {
            value += 1;
        }
        count--;
    }
    if (count != 0 && cube->U[2][2] == 37)
    {
        color = facesH[0][0][0];
        colorFace = getIndex(colors, color);
        dist = distance(0, colorFace);
        value += 7;
        if (dist == 1)
        {
            value += 1;
        }
        count--;
    }

    if (count != 0 && cube->D[0][0] == 37)
    {
        color = facesH[0][2][0];
        colorFace = getIndex(colors, color);
        dist = distance(0, colorFace);
        if(dist != 0 || cube->D[0][1] != 37 || facesH[0][2][1] != color){
            // Si la esquina no esta en su lugar
            value += dist + 5;
        }
        count--;
    }
    if (count != 0 && cube->D[0][2] == 37)
    {
        color = facesH[0][2][2];
        colorFace = getIndex(colors, color);
        dist = distance(0, colorFace);
        if (dist != 0 || cube->D[0][1] != 37 || facesH[0][2][1] != color)
        {
            // Si la esquina no esta en su lugar
            value += dist + 5;
        }
    }
    if (count != 0 && cube->D[2][0] == 37)
    {
        color = facesH[2][2][2];
        colorFace = getIndex(colors, color);
        dist = distance(2, colorFace);
        if (dist != 0 || cube->D[2][1] != 37 || facesH[2][2][1] != color)
        {
            // Si la esquina no esta en su lugar
            value += dist + 5;
        }
    }
    if (count != 0 && cube->D[2][2] == 37)
    {
        color = facesH[2][2][0];
        colorFace = getIndex(colors, color);
        dist = distance(2, colorFace);
        if (dist != 0 || cube->D[2][1] != 37 || facesH[2][2][1] != color)
        {
            // Si la esquina no esta en su lugar
            value += dist + 5;
        }
    }
    delete[] facesH;

    return value;
}

int RubikSolver::getIndex(int arr[4], int val)
{
    for (int i = 0; i < 4; i++)
    {
        if (arr[i] == val)
        {
            return i;
        }
    }
    return -1;
}

int RubikSolver::leftFaceIndex(int i)
{
    int j = i - 1;
    if (j < 0)
    {
        j = 3;
    }
    return j;
}

int RubikSolver::rightFaceIndex(int i)
{
    int j = i + 1;
    if (j > 3)
    {
        j = 0;
    }
    return j;
}

int RubikSolver::distance(int i, int j)
{
    int r = i - j;
    if (r < 0)
    {
        r = r * -1;
    }
    if (r == 3)
    {
        r = 1;
    }

    return r;
}