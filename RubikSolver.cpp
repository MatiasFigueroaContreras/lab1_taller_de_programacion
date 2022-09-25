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
            delete open;
            delete openHash;
            delete closed;
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

    delete open;
    delete openHash;
    delete closed;
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
        break;
    case 4:
        return middleComplete(cube) && whiteComplete(cube) && yellowCross(cube);
        break;
    case 5:
        return middleComplete(cube) && whiteComplete(cube) && correctYellowCross(cube);
        break;
    case 6:
        return wellPosYellowCorners(cube) && middleComplete(cube) && whiteComplete(cube) && correctYellowCross(cube);
        break;
    case 7:
        return cube->isSolved();
        break;
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

bool RubikSolver::correctYellowCross(Rubik *cube)
{
    return cube->U[0][1] == 33 &&
           cube->U[1][0] == 33 &&
           cube->U[1][2] == 33 &&
           cube->U[2][1] == 33 &&
           cube->F[0][1] == 31 &&
           cube->R[0][1] == 32 &&
           cube->B[0][1] == 35 &&
           cube->L[0][1] == 34;
}

bool RubikSolver::wellPosYellowCorners(Rubik *cube)
{
    int colors[4][4] = {
        {YELLOW, BLUE, ORANGE, YELLOW},
        {YELLOW, GREEN, ORANGE, YELLOW},
        {YELLOW, BLUE, RED, YELLOW},
        {YELLOW, RED, GREEN, YELLOW}};
    int corners[4][3] = {
        {cube->U[0][0], cube->B[0][2], cube->L[0][0]},
        {cube->U[0][2], cube->B[0][0], cube->R[0][2]},
        {cube->U[2][0], cube->F[0][0], cube->L[0][2]},
        {cube->U[2][2], cube->F[0][2], cube->R[0][0]}};

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (getIndex(colors[i], corners[i][j]) == -1)
            {
                return false;
            }
        }
    }
    return true;
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
        return middleCompleteHeuristic(cube);
        break;
    case 4:
        return yellowCrossHeuristic(cube);
        break;
    case 5:
        return correctYellowCrossHeuristic(cube);
        break;
    case 6:
        return wellPosYellowCornersHeuristic(cube);
        break;
    case 7:
        return toSolvedHeuristic(cube);
        break;
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
            if (facesH[colorFace][1][2] != color || facesH[right][1][0] != 37)
            {
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
            if (dist != 0 || facesH[colorFace][1][2] != color || facesH[k][1][0] != 37)
            {
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
        if (dist != 0 || cube->D[0][1] != 37 || facesH[0][2][1] != color)
        {
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
        count--;
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
        count--;
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

int RubikSolver::middleCompleteHeuristic(Rubik *cube)
{
    int left, right, dist, color, colorFace, upColor, upColorFace, edgeFace, oppFace, useFace, useFace2;
    int value = 0;
    int count = 4;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {31, 32, 35, 34};
    for (int k = 0; k < 4 && count != 0; k += 2)
    {
        left = leftFaceIndex(k);
        right = rightFaceIndex(k);
        color = facesH[k][1][1];
        if (facesH[k][1][0] != 37 &&
            facesH[k][1][0] != 33 &&
            facesH[left][1][2] != 37 &&
            facesH[left][1][2] != 33)
        {
            // Entra si el color del borde horizontal no es blanco ni amarillo.
            if (facesH[right][1][0] == 37 ||
                facesH[leftFaceIndex(left)][1][2] == 37)
            {
                // Si alguna cara que afecte al posicionamiento de el borde que se esta
                //  consultando esta rotada (sin el color blanco en la posicion correcta)
                //  entonces tomara 7 movimientos aproximadamente dejarlo en su lugar.
                value += 7;
                // std::cout << "+7 en borde (1, 0) " << k << std::endl;
            }
            else if (facesH[k][1][0] != color ||
                     facesH[left][1][2] != facesH[left][1][1])
            {
                // Si el borde no esta posicionado correctamente, entonces toma
                //  aproximadamente 16 movimientos llevarlo a su lugar.
                value += 16;
                // std::cout << "+14 en borde (1, 0) " << k << std::endl;
            }
            // En otro caso el borde esta en la posicion correcta.
            // std::cout << "+0 en borde (1, 0) " << k << std::endl;
            count--;
        }

        if (facesH[k][1][2] != 37 &&
            facesH[k][1][2] != 33 &&
            facesH[right][1][0] != 37 &&
            facesH[right][1][0] != 33)
        {
            // Entra si el color del borde horizontal no es blanco ni amarillo.
            if (facesH[left][1][2] == 37 ||
                facesH[leftFaceIndex(left)][1][0] == 37)
            {
                // Si alguna cara que afecte al posicionamiento de el borde que se esta
                //  consultando esta rotada (sin el color blanco en la posicion correcta)
                //  entonces tomara 7 movimientos aproximadamente dejarlo en su lugar.
                value += 7;
                // std::cout << "+7 en borde (1, 2) " << k << std::endl;
            }
            else if (facesH[k][1][2] != color ||
                     facesH[right][1][0] != facesH[right][1][1])
            {
                // Si el borde no esta posicionado correctamente, entonces toma
                //  aproximadamente 16 movimientos llevarlo a su lugar.
                value += 16;
                // std::cout << "+14 en borde (1, 2) " << k << std::endl;
            }
            // En otro caso el borde esta en la posicion correcta.
            // std::cout << "+0 en borde (1, 2) " << k << std::endl;
            count--;
        }
    }

    int prueba;   // BORRAR!!!!
    edgeFace = 2; // Cara trasera, la cual es parte del cubito del borde a revisar.
    upColor = cube->U[0][1];
    color = facesH[edgeFace][0][1];
    prueba = value;
    if (upColor != 37 &&
        upColor != 33 &&
        color != 37 &&
        color != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        oppFace = 0; // Cara contraria/ al frente del cubito del borde a revisar.
        colorFace = getIndex(colors, color);
        upColorFace = getIndex(colors, upColor);
        useFace = -1;
        useFace2 = -1;
        left = leftFaceIndex(edgeFace);
        right = rightFaceIndex(edgeFace);
        if (facesH[left][0][2] == 37)
        {
            useFace = left;
        }
        else if (facesH[right][0][0] == 37)
        {
            useFace = right;
        }

        if (facesH[left][0][0] == 37)
        {
            useFace2 = left;
        }
        else if (facesH[right][0][2] == 37)
        {
            useFace2 = right;
        }

        if (useFace != -1 &&
            upColor != cube->U[0][3 - useFace])
        {
            if (facesH[useFace][1][3 - useFace] == 37)
            {
                value += 15;
            }
            else if (facesH[edgeFace][1][3 - useFace] == 37)
            {
                value += 14;
            }
            else if (facesH[edgeFace][0][useFace - 1] == facesH[edgeFace][1][1])
            {
                value += 12;
            }
            else
            {
                value += 13;
            }
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][3 - useFace2] != facesH[oppFace][0][1] &&
                 cube->U[2][1] != cube->U[2][3 - useFace2] &&
                 facesH[oppFace][1][3 - useFace2] == facesH[oppFace][1][1] &&
                 facesH[useFace2][1][useFace2 - 1] == 37)
        {
            value += 10;
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][3 - useFace2] != facesH[oppFace][0][1] &&
                 cube->U[2][1] != cube->U[2][3 - useFace2])
        {
            value += 11;
        }
        else if (oppFace == upColorFace)
        {
            // Entra si el color del cubito del borde esta posicionado al frente de su color.
            if (facesH[colorFace][0][colorFace - 1] == 37 &&
                facesH[oppFace][0][3 - colorFace] == facesH[oppFace][1][1])
            {
                if (facesH[colorFace][1][colorFace - 1] == 37 &&
                    facesH[oppFace][1][3 - colorFace] == facesH[oppFace][1][1])
                {
                    value += 6;
                }
                else
                {
                    value += 3;
                }
            }
            else if (facesH[edgeFace][0][colorFace - 1] == color &&
                     facesH[colorFace][0][3 - colorFace] == 37)
            {
                value += 2;
            }
            else
            {
                value += 7;
            }
        }
        else if (facesH[oppFace][1][1] == color &&
                 facesH[oppFace][0][upColorFace - 1] == upColor &&
                 facesH[leftFaceIndex(leftFaceIndex(upColorFace))][0][3 - upColorFace] == 37)
        {
            if (facesH[upColorFace][1][upColorFace - 1] == upColor &&
                facesH[oppFace][1][3 - upColorFace] == 37)
            {
                value += 5;
            }
            else
            {
                value += 4;
            }
        }
        else if (colorFace == edgeFace &&
                 facesH[edgeFace][0][upColorFace - 1] == color &&
                 facesH[edgeFace][1][upColorFace - 1] == color &&
                 facesH[upColorFace][0][3 - upColorFace] == 37 &&
                 facesH[upColorFace][1][3 - upColorFace] == 37)
        {
            value += 1;
        }
        else
        {
            dist = distance(upColorFace, edgeFace);
            value += 9 - dist;
        }
    }
    // std::cout << "+" << value - prueba << " en UP (0, 1)" << std::endl;

    edgeFace = 3; // Cara trasera, la cual es parte del cubito del borde a revisar.
    upColor = cube->U[1][0];
    color = facesH[edgeFace][0][1];
    prueba = value;
    if (upColor != 37 &&
        upColor != 33 &&
        color != 37 &&
        color != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        oppFace = 1; // Cara contraria/ al frente del cubito del borde a revisar.
        colorFace = getIndex(colors, color);
        upColorFace = getIndex(colors, upColor);
        useFace = -1;
        useFace2 = -1;
        left = leftFaceIndex(edgeFace);
        right = rightFaceIndex(edgeFace);
        if (facesH[left][0][2] == 37)
        {
            useFace = left;
        }
        else if (facesH[right][0][0] == 37)
        {
            useFace = right;
        }

        if (facesH[left][0][0] == 37)
        {
            useFace2 = left;
        }
        else if (facesH[right][0][2] == 37)
        {
            useFace2 = right;
        }

        if (useFace != -1 &&
            upColor != cube->U[2 - useFace][0])
        {
            if (facesH[useFace][1][useFace] == 37)
            {
                value += 15;
            }
            else if (facesH[edgeFace][1][useFace] == 37)
            {
                value += 14;
            }
            else if (facesH[edgeFace][0][2 - useFace] == facesH[edgeFace][1][1])
            {
                value += 12;
            }
            else
            {
                value += 13;
            }
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][useFace2] != facesH[oppFace][0][1] &&
                 cube->U[1][2] != cube->U[2 - useFace2][2] &&
                 facesH[oppFace][1][useFace2] == facesH[oppFace][1][1] &&
                 facesH[useFace2][1][2 - useFace2] == 37)
        {
            value += 10;
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][useFace2] != facesH[oppFace][0][1] &&
                 cube->U[1][2] != cube->U[2 - useFace2][2])
        {
            value += 11;
        }
        else if (oppFace == upColorFace)
        {
            // Entra si el color del cubito del borde esta posicionado al frente de su color.
            if (facesH[colorFace][0][2 - colorFace] == 37 &&
                facesH[oppFace][0][colorFace] == facesH[oppFace][1][1])
            {
                if (facesH[colorFace][1][2 - colorFace] == 37 &&
                    facesH[oppFace][1][colorFace] == facesH[oppFace][1][1])
                {
                    value += 6;
                }
                else
                {
                    value += 3;
                }
            }
            else if (facesH[edgeFace][0][2 - colorFace] == color && // Mejorable (se puede especificar más)
                     facesH[colorFace][0][colorFace] == 37)         // facesH[oppFace][1][colorFace] == 37 && facesH[colorFace][1][2 - colorFace]
            {
                value += 2;
            }
            else
            {
                value += 7;
            }
        }
        else if (facesH[oppFace][1][1] == color &&
                 facesH[oppFace][0][2 - upColorFace] == upColor &&
                 facesH[leftFaceIndex(leftFaceIndex(upColorFace))][0][upColorFace] == 37)
        {
            if (facesH[upColorFace][1][2 - upColorFace] == upColor &&
                facesH[oppFace][1][upColorFace] == 37)
            {
                value += 5;
            }
            else
            {
                value += 4;
            }
        }
        else if (colorFace == edgeFace &&
                 facesH[edgeFace][0][2 - upColorFace] == color &&
                 facesH[edgeFace][1][2 - upColorFace] == color &&
                 facesH[upColorFace][0][upColorFace] == 37 &&
                 facesH[upColorFace][1][upColorFace] == 37)
        {
            value += 1;
        }
        else
        {
            dist = distance(upColorFace, edgeFace);
            value += 9 - dist;
        }
    }
    // std::cout << "+" << value - prueba << " en UP (1, 0)" << std::endl;

    edgeFace = 0; // Cara trasera, la cual es parte del cubito del borde a revisar.
    upColor = cube->U[2][1];
    color = facesH[edgeFace][0][1];
    prueba = value;
    if (upColor != 37 &&
        upColor != 33 &&
        color != 37 &&
        color != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        oppFace = 2; // Cara contraria/ al frente del cubito del borde a revisar.
        colorFace = getIndex(colors, color);
        upColorFace = getIndex(colors, upColor);
        useFace = -1;
        useFace2 = -1;
        left = leftFaceIndex(edgeFace);
        right = rightFaceIndex(edgeFace);
        if (facesH[left][0][2] == 37)
        {
            useFace = left;
        }
        else if (facesH[right][0][0] == 37)
        {
            useFace = right;
        }

        if (facesH[left][0][0] == 37)
        {
            useFace2 = left;
        }
        else if (facesH[right][0][2] == 37)
        {
            useFace2 = right;
        }

        if (useFace != -1 &&
            upColor != cube->U[2][3 - useFace])
        {
            if (facesH[useFace][1][useFace - 1] == 37)
            {
                value += 15;
            }
            else if (facesH[edgeFace][1][useFace - 1] == 37)
            {
                value += 14;
            }
            else if (facesH[edgeFace][0][3 - useFace] == facesH[edgeFace][1][1])
            {
                value += 12;
            }
            else
            {
                value += 13;
            }
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][useFace2 - 1] != facesH[oppFace][0][1] &&
                 cube->U[0][1] != cube->U[0][3 - useFace2])
        {
            if (facesH[oppFace][1][useFace2 - 1] == facesH[oppFace][1][1] &&
                facesH[useFace2][1][3 - useFace2] == 37)
            {
                value += 10;
            }
            else
            {
                value += 11;
            }
        }
        else if (oppFace == upColorFace)
        {
            // Entra si el color del cubito del borde esta posicionado al frente de su color.
            if (facesH[colorFace][0][3 - colorFace] == 37 &&
                facesH[oppFace][0][colorFace - 1] == facesH[oppFace][1][1])
            {
                if (facesH[colorFace][1][3 - colorFace] == 37 &&
                    facesH[oppFace][1][colorFace - 1] == facesH[oppFace][1][1])
                {
                    value += 6;
                }
                else
                {
                    value += 3;
                }
            }
            else if (facesH[edgeFace][0][3 - colorFace] == color &&
                     facesH[colorFace][0][colorFace - 1] == 37)
            {
                value += 2;
            }
            else
            {
                value += 7;
            }
        }
        else if (facesH[oppFace][1][1] == color &&
                 facesH[oppFace][0][3 - upColorFace] == upColor &&
                 facesH[leftFaceIndex(leftFaceIndex(upColorFace))][0][upColorFace - 1] == 37)
        {
            if (facesH[upColorFace][1][3 - upColorFace] == upColor &&
                facesH[oppFace][1][upColorFace - 1] == 37)
            {
                value += 5;
            }
            else
            {
                value += 4;
            }
        }
        else if (colorFace == edgeFace &&
                 facesH[edgeFace][0][3 - upColorFace] == color &&
                 facesH[edgeFace][1][3 - upColorFace] == color &&
                 facesH[upColorFace][0][upColorFace - 1] == 37 &&
                 facesH[upColorFace][1][upColorFace - 1] == 37)
        {
            value += 1;
        }
        else
        {
            dist = distance(upColorFace, edgeFace);
            value += 9 - dist;
        }
    }
    // std::cout << "+" << value - prueba << " en UP (2, 1)" << std::endl;

    edgeFace = 1; // Cara trasera, la cual es parte del cubito del borde a revisar.
    upColor = cube->U[1][2];
    color = facesH[edgeFace][0][1];
    prueba = value;
    if (upColor != 37 &&
        upColor != 33 &&
        color != 37 &&
        color != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        oppFace = 3; // Cara contraria/ al frente del cubito del borde a revisar.
        colorFace = getIndex(colors, color);
        upColorFace = getIndex(colors, upColor);
        useFace = -1;
        useFace2 = -1;
        left = leftFaceIndex(edgeFace);
        right = rightFaceIndex(edgeFace);
        if (facesH[left][0][2] == 37)
        {
            useFace = left;
        }
        else if (facesH[right][0][0] == 37)
        {
            useFace = right;
        }

        if (facesH[left][0][0] == 37)
        {
            useFace2 = left;
        }
        else if (facesH[right][0][2] == 37)
        {
            useFace2 = right;
        }

        if (useFace != -1 &&
            upColor != cube->U[2 - useFace][2])
        {
            if (facesH[useFace][1][2 - useFace] == 37)
            {
                value += 15;
            }
            else if (facesH[edgeFace][1][2 - useFace] == 37)
            {
                value += 14;
            }
            else if (facesH[edgeFace][0][useFace] == facesH[edgeFace][1][1])
            {
                value += 12;
            }
            else
            {
                value += 13;
            }
        }
        else if (useFace2 != -1 &&
                 facesH[oppFace][0][2 - useFace2] != facesH[oppFace][0][1] &&
                 cube->U[1][0] != cube->U[2 - useFace2][0])
        {
            if (facesH[oppFace][1][2 - useFace2] == facesH[oppFace][1][1] &&
                facesH[useFace2][1][useFace2] == 37)
            {
                value += 10;
            }
            else
            {
                value += 11;
            }
        }
        else if (oppFace == upColorFace)
        {
            // Entra si el color del cubito del borde esta posicionado al frente de su color.
            if (facesH[colorFace][0][colorFace] == 37 &&
                facesH[oppFace][0][2 - colorFace] == facesH[oppFace][1][1])
            {
                if (facesH[colorFace][1][colorFace] == 37 &&
                    facesH[oppFace][1][2 - colorFace] == facesH[oppFace][1][1])
                {
                    value += 6;
                }
                else
                {
                    value += 3;
                }
            }
            else if (facesH[edgeFace][0][colorFace] == color &&
                     facesH[colorFace][0][2 - colorFace] == 37)
            {
                value += 2;
            }
            else
            {
                value += 7;
            }
        }
        else if (facesH[oppFace][1][1] == color &&
                 facesH[oppFace][0][upColorFace] == upColor &&
                 facesH[leftFaceIndex(leftFaceIndex(upColorFace))][0][2 - upColorFace] == 37)
        {
            if (facesH[upColorFace][1][upColorFace] == upColor &&
                facesH[oppFace][1][2 - upColorFace] == 37)
            {
                value += 5;
            }
            else
            {
                value += 4;
            }
        }
        else if (colorFace == edgeFace &&
                 facesH[edgeFace][0][upColorFace] == color &&
                 facesH[edgeFace][1][upColorFace] == color &&
                 facesH[upColorFace][0][2 - upColorFace] == 37 &&
                 facesH[upColorFace][1][2 - upColorFace] == 37)
        {
            value += 1;
        }
        else
        {
            dist = distance(upColorFace, edgeFace);
            value += 9 - dist;
        }
    }
    // std::cout << "+" << value - prueba << " en UP (1, 2)" << std::endl;

    edgeFace = 0;
    color = cube->D[0][1];
    if (color != 37 &&
        color != 33 &&
        facesH[edgeFace][2][1] != 37 &&
        facesH[edgeFace][2][1] != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        colorFace = getIndex(colors, color);
        oppFace = leftFaceIndex(leftFaceIndex(colorFace));
        if (colorFace != 3 ||
            colorFace != 1 ||
            facesH[edgeFace][2][1] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][2][colorFace - 1] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][1][colorFace - 1] != facesH[edgeFace][1][1] ||
            facesH[oppFace][2][3 - colorFace] != 37 ||
            facesH[oppFace][1][3 - colorFace] != 37)
        {
            // Entra si el cubito del borde no esta posicionado correctamente
            value += 16;
            // std::cout << "+14 en D (0, 1)" << std::endl;
        }
        // std::cout << "+0 en D (0, 1)" << std::endl;
    }

    edgeFace = 3;
    color = cube->D[1][0];
    if (color != 37 &&
        color != 33 &&
        facesH[edgeFace][2][1] != 37 &&
        facesH[edgeFace][2][1] != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        colorFace = getIndex(colors, color);
        oppFace = leftFaceIndex(leftFaceIndex(colorFace));
        if (colorFace != 0 ||
            colorFace != 2 ||
            facesH[edgeFace][2][1] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][2][colorFace] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][1][colorFace] != facesH[edgeFace][1][1] ||
            facesH[oppFace][2][2 - colorFace] != 37 ||
            facesH[oppFace][1][2 - colorFace] != 37)
        {
            // Entra si el cubito del borde no esta posicionado correctamente
            value += 16;
            // std::cout << "+14 en D (1, 0)" << std::endl;
        }
        // std::cout << "+0 en D (1, 0)" << std::endl;
    }

    edgeFace = 2;
    color = cube->D[2][1];
    if (color != 37 &&
        color != 33 &&
        facesH[edgeFace][2][1] != 37 &&
        facesH[edgeFace][2][1] != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        colorFace = getIndex(colors, color);
        oppFace = leftFaceIndex(leftFaceIndex(colorFace));
        if (colorFace != 3 ||
            colorFace != 1 ||
            facesH[edgeFace][2][1] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][2][3 - colorFace] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][1][3 - colorFace] != facesH[edgeFace][1][1] ||
            facesH[oppFace][2][colorFace - 1] != 37 ||
            facesH[oppFace][1][colorFace - 1] != 37)
        {
            // Entra si el cubito del borde no esta posicionado correctamente
            value += 16;
            // std::cout << "+14 en D (2, 1)" << std::endl;
        }
        // std::cout << "+0 en D (2, 1)" << std::endl;
    }

    edgeFace = 1;
    color = cube->D[1][2];
    if (color != 37 &&
        color != 33 &&
        facesH[edgeFace][2][1] != 37 &&
        facesH[edgeFace][2][1] != 33)
    {
        // Entra si el cubito del borde no tiene color blanco ni amarillo.
        colorFace = getIndex(colors, color);
        oppFace = leftFaceIndex(leftFaceIndex(colorFace));
        if (colorFace != 0 ||
            colorFace != 2 ||
            facesH[edgeFace][2][1] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][2][2 - colorFace] != facesH[edgeFace][1][1] ||
            facesH[edgeFace][1][2 - colorFace] != facesH[edgeFace][1][1] ||
            facesH[oppFace][2][colorFace] != 37 ||
            facesH[oppFace][1][colorFace] != 37)
        {
            // Entra si el cubito del borde no esta posicionado correctamente
            value += 16;
            // std::cout << "+14 en D (1, 2)" << std::endl;
        }
        // std::cout << "+0 en D (1, 2)" << std::endl;
    }

    delete[] facesH;
    return value;
}

int RubikSolver::yellowCrossHeuristic(Rubik *cube)
{
    int left, right, opp, face;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {31, 32, 35, 34};

    if (stopPoint(cube, 4))
    {
        return 0;
    }

    if (face = yellowLineForm(cube); face != -1)
    {
        left = leftFaceIndex(face);
        right = rightFaceIndex(face);
        opp = leftFaceIndex(left);
        if (facesH[right][0][0] == WHITE &&
            facesH[right][1][0] == WHITE &&
            facesH[right][2][0] == WHITE)
        {
            if (facesH[face][1][0] == WHITE &&
                facesH[face][2][0] == WHITE)
            {
                return 4;
            }
            else if (cube->U[2][1] == YELLOW && cube->U[1][2] == YELLOW)
            {
                return 1;
            }
            else
            {
                return 5;
            }
        }
        else if (facesH[opp * (3 - face) + face * (face - 2)][1][0] == WHITE &&
                 facesH[opp * (3 - face) + face * (face - 2)][2][0] == WHITE &&
                 facesH[left * (3 - face) + right * (face - 2)][0][0] == WHITE)
        {
            if (facesH[right * (3 - face) + left * (face - 2)][1][0] == WHITE &&
                facesH[right * (3 - face) + left * (face - 2)][2][0] == WHITE)
            {
                return 3;
            }
            else
            {
                return 2;
            }
        }
        else if (whiteComplete(cube))
        {
            return 6;
        }
        else
        {
            return 36;
        }
    }
    else if (face = yellowSeatedForm(cube); face != -1)
    {
        left = leftFaceIndex(face);
        right = rightFaceIndex(face);
        opp = leftFaceIndex(left);
        if (facesH[right][0][0] == WHITE &&
            facesH[right][1][0] == WHITE &&
            facesH[right][2][0] == WHITE)
        {
            if (facesH[face][1][0] == WHITE &&
                facesH[face][2][0] == WHITE)
            {
                return 2;
            }
            else
            {
                return 5;
            }
        }
        else if (facesH[face][1][0] == WHITE &&
                 facesH[face][2][0] == WHITE &&
                 facesH[right][0][0] == WHITE)
        {
            if (facesH[left][1][0] == WHITE &&
                facesH[left][2][0] == WHITE)
            {
                return 3;
            }
            else
            {
                return 4;
            }
        }
        else if (whiteComplete(cube))
        {
            return 6;
        }
        else
        {
            return 36;
        }
    }
    else
    {
        face = 2;
        left = leftFaceIndex(face);
        right = rightFaceIndex(face);
        opp = leftFaceIndex(left);
        if (facesH[right][0][0] == WHITE &&
            facesH[right][1][0] == WHITE &&
            facesH[right][2][0] == WHITE)
        {
            if (facesH[face][1][0] == WHITE &&
                facesH[face][2][0] == WHITE)
            {
                return 4;
            }
            else
            {
                return 5;
            }
        }
        else if (facesH[right][1][0] == WHITE &&
                 facesH[right][2][0] == WHITE &&
                 facesH[opp][0][0] == WHITE)
        {
            if (facesH[face][1][0] == WHITE &&
                facesH[face][2][0] == WHITE)
            {
                return 3;
            }
            else
            {
                return 2;
            }
        }
        else if (whiteComplete(cube))
        {
            return 12;
        }
        else
        {
            return 36;
        }
    }
}

int RubikSolver::correctYellowCrossHeuristic(Rubik *cube)
{
    int aux, left, right, dist, cornerSteps, count, color, colorFace, correctColors, whiteCornerFace, whiteGoalFace, mateCornerFace;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {31, 32, 35, 34};

    whiteCornerFace = -1;
    correctColors = 0;
    count = 0;
    for (int i = 0; i < 4; i++)
    {
        if (facesH[i][0][0] == WHITE)
        {
            whiteCornerFace = i;
            count++;
        }

        if (i < 3)
        {
            color = facesH[i][0][1];
            colorFace = getIndex(colors, color);
            color = facesH[i + 1][0][1];
            aux = getIndex(colors, color);
            if (rightFaceIndex(colorFace) == aux)
            {
                correctColors += 2;
            }
        }
    }

    correctColors = correctColors / 2 + 1;

    if (whiteComplete(cube))
    {
        if (correctColors == 4)
        {
            color = facesH[0][0][1];
            colorFace = getIndex(colors, color);
            dist = distance(colorFace, 0);
            return dist;
        }
        else if (correctColors == 2)
        {
            return 10;
        }
        else
        {
            return 20;
        }
    }

    if (whiteCornerFace != -1 && count == 1)
    {
        left = leftFaceIndex(whiteCornerFace);
        color = facesH[left][0][2];
        mateCornerFace = getIndex(colors, color);
        whiteGoalFace = rightFaceIndex(mateCornerFace);
        cornerSteps = distance(whiteCornerFace, whiteGoalFace);
        if (whiteCornerFace == mateCornerFace)
        {
            cornerSteps = 3;
        }

        if (facesH[whiteGoalFace][1][0] == WHITE &&
            facesH[whiteGoalFace][2][0] == WHITE)
        {
            if (cornerSteps == 0)
            {
                color = facesH[whiteGoalFace][0][1];
                colorFace = getIndex(colors, color);
                color = facesH[mateCornerFace][1][0];
                aux = getIndex(colors, color);

                if (correctColors == 3 || rightFaceIndex(aux) == colorFace)
                {
                    return 3;
                }
                else if (correctColors == 2)
                {
                    return 12;
                }
                else
                {
                    return 9;
                }
            }
            else if (cornerSteps == 1)
            {
                return 8;
            }
            else if (cornerSteps == 2)
            {
                return 5;
            }
            else if (cornerSteps == 3)
            {
                return 4;
            }
        }
        else
        {
            if (cornerSteps == 1)
            {
                return 7;
            }
            else if (cornerSteps == 2)
            {
                return 6;
            }
        }
    }

    return 40;
}

int RubikSolver::wellPosYellowCornersHeuristic(Rubik *cube)
{
    int aux, left, right, dist, color, colorFace, correctCorners, whiteFormFace, extraH;
    bool check;
    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {31, 32, 35, 34};
    int colorsToCheck[4][4] = {
        {YELLOW, cube->B[0][1], cube->L[0][1], YELLOW},
        {YELLOW, cube->B[0][1], cube->R[0][1], YELLOW},
        {YELLOW, cube->F[0][1], cube->L[0][1], YELLOW},
        {YELLOW, cube->F[0][1], cube->R[0][1], YELLOW}};
    int corners[4][3] = {
        {cube->U[0][0], cube->B[0][2], cube->L[0][0]},
        {cube->U[0][2], cube->B[0][0], cube->R[0][2]},
        {cube->U[2][0], cube->F[0][0], cube->L[0][2]},
        {cube->U[2][2], cube->F[0][2], cube->R[0][0]}};

    correctCorners = 0;
    whiteFormFace = -1;
    aux = 0;
    for (int i = 0; i < 4; i++)
    {
        check = true; 
        for (int j = 0; j < 3; j++)
        {
            if(colorsToCheck[i][1] != colorsToCheck[i][2])
            {
                if (getIndex(colorsToCheck[i], corners[i][j]) == -1)
                {
                    check = false;                    
                }
            }
        }
        if(check)
        {
            correctCorners++;
        }

        if ((facesH[i][1][0] == WHITE &&
             facesH[i][2][0] == WHITE) ||
            (facesH[i][1][2] == WHITE &&
             facesH[i][2][2] == WHITE))
        {
            whiteFormFace = i;
            aux++;
        }
    }

    if(aux != 1)
    {
        whiteFormFace = -1;
    }

    if (whiteComplete(cube))
    {
        if (correctCorners == 4)
        {
            color = facesH[0][0][1];
            colorFace = getIndex(colors, color);
            dist = distance(colorFace, 0);
            return dist;
        }
        else if (correctCorners == 1)
        {
            return 19;
        }
        else
        {
            return 29;
        }
    }

    if (whiteFormFace != -1)
    {
        left = leftFaceIndex(whiteFormFace);
        right = rightFaceIndex(whiteFormFace);
        extraH = 0;
        if (correctCorners < 1)
        {
            extraH = 10;
        }

        if (facesH[whiteFormFace][0][2] == WHITE &&
            facesH[whiteFormFace][1][2] == WHITE &&
            facesH[whiteFormFace][2][2] == WHITE)
        {
            if (facesH[left][0][0] == WHITE &&
                facesH[whiteFormFace][1][0] == WHITE &&
                facesH[whiteFormFace][2][0] == WHITE)
            {
                return 15 + extraH;
            }
            else
            {
                return 18 + extraH;
            }
        }
        else if (facesH[right][0][2] == WHITE &&
                 facesH[whiteFormFace][1][2] == WHITE &&
                 facesH[whiteFormFace][2][2] == WHITE)
        {
            if (facesH[whiteFormFace][0][0] == WHITE &&
                facesH[whiteFormFace][1][0] == WHITE &&
                facesH[whiteFormFace][2][0] == WHITE)
            {
                return 16 + extraH;
            }
            else
            {
                return 17 + extraH;
            }
        }
        else if (facesH[whiteFormFace][1][0] == WHITE &&
                 facesH[whiteFormFace][2][0] == WHITE)
        {
            if(facesH[left][0][0] == WHITE)
            {
                return 14 + extraH;
            }
            else if(facesH[whiteFormFace][0][0] == WHITE)
            {
                return 13 + extraH;
            }
        }
    }

    return 60;
}

int RubikSolver::toSolvedHeuristic(Rubik *cube)
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
    
}

int RubikSolver::yellowLineForm(Rubik *cube)
{
    if (cube->U[1][0] == YELLOW && cube->U[1][2] == YELLOW)
    {
        return 2;
    }

    if (cube->U[0][1] == YELLOW && cube->U[2][1] == YELLOW)
    {
        return 3;
    }

    return -1;
}

int RubikSolver::yellowSeatedForm(Rubik *cube)
{
    if (cube->U[1][0] == YELLOW && cube->U[2][1] == YELLOW)
    {
        return 2;
    }

    if (cube->U[1][0] == YELLOW && cube->U[0][1] == YELLOW)
    {
        return 1;
    }

    if (cube->U[0][1] == YELLOW && cube->U[1][2] == YELLOW)
    {
        return 0;
    }

    if (cube->U[1][2] == YELLOW && cube->U[2][1] == YELLOW)
    {
        return 3;
    }

    return -1;
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