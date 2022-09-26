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
    State *state1 = new State(startingCube, nullptr, 0, ' ', 0);
    State *state2 = partialSolve(state1, 1);
    State *state3 = partialSolve(state2, 2);
    State *state4 = partialSolve(state3, 3);
    State *state5 = partialSolve(state4, 4);
    State *state6 = partialSolve(state5, 5);
    State *state7 = partialSolve(state6, 6);
    State *state8 = partialSolve(state7, 7);
    State *state9 = partialSolve(state8, 8);
    State *state10 = partialSolve(state9, 9);
    State *state11 = partialSolve(state10, 10);
    state11->printPath();
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
        // std::cout << std::endl;
        // std::cout << std::endl;
        // std::cout << "Cubo en profundidad: " << current->depth << std::endl;
        // current->cube->print();
        // std::cout << std::endl;
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
        return edgeRedBlue(cube) && whiteComplete(cube);
        break;
    case 4:
        return edgeRedGreen(cube) && edgeRedBlue(cube) && whiteComplete(cube);
        break;
    case 5:
        return edgeOrangeBlue(cube) && edgeRedGreen(cube) && edgeRedBlue(cube) && whiteComplete(cube);
        break;
    case 6:
        return edgeOrangeGreen(cube) && edgeOrangeBlue(cube) && edgeRedGreen(cube) && edgeRedBlue(cube) && whiteComplete(cube);
        break;
    case 7:
        return middleComplete(cube) && whiteComplete(cube) && yellowCross(cube);
        break;
    case 8:
        return middleComplete(cube) && whiteComplete(cube) && correctYellowCross(cube);
        break;
    case 9:
        return wellPosYellowCorners(cube) && middleComplete(cube) && whiteComplete(cube) && correctYellowCross(cube);
        break;
    case 10:
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

bool RubikSolver::edgeRedBlue(Rubik *cube)
{
    return cube->F[1][0] == RED && cube->L[1][2] == BLUE;
}

bool RubikSolver::edgeRedGreen(Rubik *cube)
{
    return cube->F[1][2] == RED && cube->R[1][0] == GREEN;
}

bool RubikSolver::edgeOrangeBlue(Rubik *cube)
{
    return cube->B[1][2] == ORANGE && cube->L[1][0] == BLUE;
}

bool RubikSolver::edgeOrangeGreen(Rubik *cube)
{
    return cube->B[1][0] == ORANGE && cube->R[1][2] == GREEN;
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
        return edgeRedBlueHeuristic(cube);
        break;
    case 4:
        return edgeRedGreenHeuristic(cube);
        break;
    case 5:
        return edgeOrangeBlueHeuristic(cube);
        break;
    case 6:
        return edgeOrangeGreenHeuristic(cube);
        break;
    case 7:
        return yellowCrossHeuristic(cube);
        break;
    case 8:
        return correctYellowCrossHeuristic(cube);
        break;
    case 9:
        return wellPosYellowCornersHeuristic(cube);
        break;
    case 10:
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

int RubikSolver::edgeRedBlueHeuristic(Rubik *cube)
{
    int left, right, opp, colorFace, oppU, distU, distH, color, colorFaceH, colorFaceU, aux;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {RED, GREEN, ORANGE, BLUE};
    int edgeColors[4] = {RED, BLUE, RED, BLUE};
    int edgesH[4][2] = {
        {cube->F[1][0], cube->L[1][2]},
        {cube->F[1][2], cube->R[1][0]},
        {cube->B[1][0], cube->R[1][2]},
        {cube->B[1][2], cube->L[1][0]}};

    int edgesU[4][3] = {
        {cube->U[0][1], cube->B[0][1], 2},
        {cube->U[1][0], cube->L[0][1], 3},
        {cube->U[2][1], cube->F[0][1], 0},
        {cube->U[1][2], cube->R[0][1], 1}};

    if (whiteComplete(cube))
    {
        if (edgeRedBlue(cube))
        {
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesH[i]))
            {
                return 16;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesU[i]))
            {
                colorFaceU = getIndex(colors, edgesU[i][0]);
                distU = distance(colorFaceU, edgesU[i][2]);
                return 9 - distU;
            }
        }

        return 150;
    }

    for (int i = 0; i < 4; i++)
    {
        if (isEdgeInPos(edgeColors, edgesU[i]))
        {
            colorFaceH = getIndex(colors, edgesU[i][1]);
            distH = distance(colorFaceH, edgesU[i][2]);
            colorFaceU = getIndex(colors, edgesU[i][0]);
            distU = distance(colorFaceU, edgesU[i][2]);
            oppU = leftFaceIndex(leftFaceIndex(colorFaceU));
            colorFace = edgesU[i][2];
            left = leftFaceIndex(colorFace);
            right = rightFaceIndex(colorFace);
            opp = leftFaceIndex(left);

            if (colorFaceH == 3)
            {
                aux = 2;
            }
            else
            {
                aux = 0;
            }

            if (distU == 2 &&
                facesH[colorFaceH][0][aux] == WHITE &&
                facesH[colorFaceH][1][aux] == WHITE &&
                facesH[colorFaceH][2][aux] == WHITE &&
                numCorrectColorsFace(cube->D) == 6)
            {
                return 6;
            }
            else if (distH == 2 &&
                     facesH[colorFaceH][1][aux] == WHITE &&
                     facesH[colorFaceH][2][aux] == WHITE &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 5;
            }
            else if (distH == 2 &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 4;
            }
            else if (distU == 2 &&
                     facesH[colorFaceH][0][aux] == WHITE &&
                     facesH[colorFaceU][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 3;
            }
            else if (distU == 2 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][0][2 - aux] == WHITE &&
                     facesH[oppU][0][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 2;
            }
            else if (distH == 0 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][0][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 1;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[left][1][2] == WHITE &&
                     facesH[left][2][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[right][1][0] == WHITE &&
                     facesH[right][2][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     facesH[colorFace][1][2] == WHITE &&
                     facesH[colorFace][2][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][0][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     facesH[opp][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[colorFaceH][1][2] == WHITE &&
                     facesH[colorFaceH][2][2] == WHITE &&
                     facesH[right][0][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     facesH[opp][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[left][0][0] == WHITE &&
                     facesH[left][1][0] == WHITE &&
                     facesH[left][2][0] == WHITE &&
                     facesH[opp][0][2] == facesH[opp][1][1] &&
                     facesH[opp][1][2] == facesH[opp][1][1] &&
                     facesH[opp][2][2] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else if (facesH[right][0][2] == WHITE &&
                     facesH[right][1][2] == WHITE &&
                     facesH[right][2][2] == WHITE &&
                     facesH[opp][0][0] == facesH[opp][1][1] &&
                     facesH[opp][1][0] == facesH[opp][1][1] &&
                     facesH[opp][2][0] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else
            {
                return 150;
            }
        }
    }

    return 150;
}

int RubikSolver::edgeRedGreenHeuristic(Rubik *cube)
{
    int left, right, opp, colorFace, oppU, distU, distH, color, colorFaceH, colorFaceU, aux;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {RED, GREEN, ORANGE, BLUE};
    int edgeColors[4] = {RED, GREEN, RED, GREEN};
    int edgesH[4][2] = {
        {cube->F[1][0], cube->L[1][2]},
        {cube->F[1][2], cube->R[1][0]},
        {cube->B[1][0], cube->R[1][2]},
        {cube->B[1][2], cube->L[1][0]}};

    int edgesU[4][3] = {
        {cube->U[0][1], cube->B[0][1], 2},
        {cube->U[1][0], cube->L[0][1], 3},
        {cube->U[2][1], cube->F[0][1], 0},
        {cube->U[1][2], cube->R[0][1], 1}};

    int edgesD[4][2] = {
        {cube->D[0][1], cube->F[2][1]},
        {cube->D[1][0], cube->L[2][1]},
        {cube->D[2][1], cube->B[2][1]},
        {cube->D[1][2], cube->R[2][1]}};

    if (whiteComplete(cube))
    {
        if (edgeRedGreen(cube))
        {
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesH[i]))
            {
                return 16;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesU[i]))
            {
                colorFaceU = getIndex(colors, edgesU[i][0]);
                distU = distance(colorFaceU, edgesU[i][2]);
                return 9 - distU;
            }
        }

        return 150;
    }

    for (int i = 0; i < 4; i++)
    {
        if (isEdgeInPos(edgeColors, edgesU[i]))
        {
            colorFaceH = getIndex(colors, edgesU[i][1]);
            distH = distance(colorFaceH, edgesU[i][2]);
            colorFaceU = getIndex(colors, edgesU[i][0]);
            distU = distance(colorFaceU, edgesU[i][2]);
            oppU = leftFaceIndex(leftFaceIndex(colorFaceU));
            colorFace = edgesU[i][2];
            left = leftFaceIndex(colorFace);
            right = rightFaceIndex(colorFace);
            opp = leftFaceIndex(left);
            if (colorFaceH == 0)
            {
                aux = 2;
            }
            else
            {
                aux = 0;
            }

            if (distU == 2 &&
                facesH[colorFaceH][0][aux] == WHITE &&
                facesH[colorFaceH][1][aux] == WHITE &&
                facesH[colorFaceH][2][aux] == WHITE &&
                numCorrectColorsFace(cube->D) == 6)
            {
                return 6;
            }
            else if (distH == 2 &&
                     facesH[colorFaceH][1][aux] == WHITE &&
                     facesH[colorFaceH][2][aux] == WHITE &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 5;
            }
            else if (distH == 2 &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 4;
            }
            else if (distU == 2 &&
                     facesH[colorFaceH][0][aux] == WHITE &&
                     facesH[colorFaceU][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 3;
            }
            else if (distU == 2 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][0][2 - aux] == WHITE &&
                     facesH[oppU][0][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 2;
            }
            else if (distH == 0 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][0][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 1;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[left][1][2] == WHITE &&
                     facesH[left][2][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[right][1][0] == WHITE &&
                     facesH[right][2][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     facesH[colorFace][1][2] == WHITE &&
                     facesH[colorFace][2][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][0][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     facesH[opp][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[colorFaceH][1][2] == WHITE &&
                     facesH[colorFaceH][2][2] == WHITE &&
                     facesH[right][0][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     facesH[opp][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[left][0][0] == WHITE &&
                     facesH[left][1][0] == WHITE &&
                     facesH[left][2][0] == WHITE &&
                     facesH[opp][0][2] == facesH[opp][1][1] &&
                     facesH[opp][1][2] == facesH[opp][1][1] &&
                     facesH[opp][2][2] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else if (facesH[right][0][2] == WHITE &&
                     facesH[right][1][2] == WHITE &&
                     facesH[right][2][2] == WHITE &&
                     facesH[opp][0][0] == facesH[opp][1][1] &&
                     facesH[opp][1][0] == facesH[opp][1][1] &&
                     facesH[opp][2][0] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else
            {
                return 150;
            }
        }
    }

    return 150;
}

int RubikSolver::edgeOrangeBlueHeuristic(Rubik *cube)
{
    int left, right, opp, colorFace, oppU, distU, distH, color, colorFaceH, colorFaceU, aux;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {RED, GREEN, ORANGE, BLUE};
    int edgeColors[4] = {ORANGE, BLUE, ORANGE, BLUE};
    int edgesH[4][2] = {
        {cube->F[1][0], cube->L[1][2]},
        {cube->F[1][2], cube->R[1][0]},
        {cube->B[1][0], cube->R[1][2]},
        {cube->B[1][2], cube->L[1][0]}};

    int edgesU[4][3] = {
        {cube->U[0][1], cube->B[0][1], 2},
        {cube->U[1][0], cube->L[0][1], 3},
        {cube->U[2][1], cube->F[0][1], 0},
        {cube->U[1][2], cube->R[0][1], 1}};

    int edgesD[4][2] = {
        {cube->D[0][1], cube->F[2][1]},
        {cube->D[1][0], cube->L[2][1]},
        {cube->D[2][1], cube->B[2][1]},
        {cube->D[1][2], cube->R[2][1]}};

    if (whiteComplete(cube))
    {
        if (edgeOrangeBlue(cube))
        {
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesH[i]))
            {
                return 16;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesU[i]))
            {
                colorFaceU = getIndex(colors, edgesU[i][0]);
                distU = distance(colorFaceU, edgesU[i][2]);
                return 9 - distU;
            }
        }

        return 150;
    }

    for (int i = 0; i < 4; i++)
    {
        if (isEdgeInPos(edgeColors, edgesU[i]))
        {
            colorFaceH = getIndex(colors, edgesU[i][1]);
            distH = distance(colorFaceH, edgesU[i][2]);
            colorFaceU = getIndex(colors, edgesU[i][0]);
            distU = distance(colorFaceU, edgesU[i][2]);
            oppU = leftFaceIndex(leftFaceIndex(colorFaceU));
            colorFace = edgesU[i][2];
            left = leftFaceIndex(colorFace);
            right = rightFaceIndex(colorFace);
            opp = leftFaceIndex(left);

            if (colorFaceH == 3)
            {
                aux = 2;
            }
            else
            {
                aux = 0;
            }

            if (distU == 2 &&
                facesH[colorFaceH][0][aux] == WHITE &&
                facesH[colorFaceH][1][aux] == WHITE &&
                facesH[colorFaceH][2][aux] == WHITE &&
                numCorrectColorsFace(cube->D) == 6)
            {
                return 6;
            }
            else if (distH == 2 &&
                     facesH[colorFaceH][1][aux] == WHITE &&
                     facesH[colorFaceH][2][aux] == WHITE &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 5;
            }
            else if (distH == 2 &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 4;
            }
            else if (distU == 2 &&
                     facesH[colorFaceH][0][aux] == WHITE &&
                     facesH[colorFaceU][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 3;
            }
            else if (distU == 2 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][0][2 - aux] == WHITE &&
                     facesH[oppU][0][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 2;
            }
            else if (distH == 0 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][0][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 1;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[left][1][2] == WHITE &&
                     facesH[left][2][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[right][1][0] == WHITE &&
                     facesH[right][2][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     facesH[colorFace][1][2] == WHITE &&
                     facesH[colorFace][2][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][0][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     facesH[opp][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[colorFaceH][1][2] == WHITE &&
                     facesH[colorFaceH][2][2] == WHITE &&
                     facesH[right][0][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     facesH[opp][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[left][0][0] == WHITE &&
                     facesH[left][1][0] == WHITE &&
                     facesH[left][2][0] == WHITE &&
                     facesH[opp][0][2] == facesH[opp][1][1] &&
                     facesH[opp][1][2] == facesH[opp][1][1] &&
                     facesH[opp][2][2] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else if (facesH[right][0][2] == WHITE &&
                     facesH[right][1][2] == WHITE &&
                     facesH[right][2][2] == WHITE &&
                     facesH[opp][0][0] == facesH[opp][1][1] &&
                     facesH[opp][1][0] == facesH[opp][1][1] &&
                     facesH[opp][2][0] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else
            {
                return 150;
            }
        }
    }

    return 150;
}

int RubikSolver::edgeOrangeGreenHeuristic(Rubik *cube)
{
    int left, right, opp, colorFace, oppU, distU, distH, color, colorFaceH, colorFaceU, aux;

    int ***facesH = new int **[4];
    facesH[0] = cube->F;
    facesH[1] = cube->R;
    facesH[2] = cube->B;
    facesH[3] = cube->L;

    int colors[4] = {RED, GREEN, ORANGE, BLUE};
    int edgeColors[4] = {ORANGE, GREEN, ORANGE, GREEN};
    int edgesH[4][2] = {
        {cube->F[1][0], cube->L[1][2]},
        {cube->F[1][2], cube->R[1][0]},
        {cube->B[1][0], cube->R[1][2]},
        {cube->B[1][2], cube->L[1][0]}};

    int edgesU[4][3] = {
        {cube->U[0][1], cube->B[0][1], 2},
        {cube->U[1][0], cube->L[0][1], 3},
        {cube->U[2][1], cube->F[0][1], 0},
        {cube->U[1][2], cube->R[0][1], 1}};

    int edgesD[4][2] = {
        {cube->D[0][1], cube->F[2][1]},
        {cube->D[1][0], cube->L[2][1]},
        {cube->D[2][1], cube->B[2][1]},
        {cube->D[1][2], cube->R[2][1]}};

    if (whiteComplete(cube))
    {
        if (edgeOrangeGreen(cube))
        {
            return 0;
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesH[i]))
            {
                return 16;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            if (isEdgeInPos(edgeColors, edgesU[i]))
            {
                colorFaceU = getIndex(colors, edgesU[i][0]);
                distU = distance(colorFaceU, edgesU[i][2]);
                return 9 - distU;
            }
        }

        return 150;
    }

    for (int i = 0; i < 4; i++)
    {
        if (isEdgeInPos(edgeColors, edgesU[i]))
        {
            colorFaceH = getIndex(colors, edgesU[i][1]);
            distH = distance(colorFaceH, edgesU[i][2]);
            colorFaceU = getIndex(colors, edgesU[i][0]);
            distU = distance(colorFaceU, edgesU[i][2]);
            oppU = leftFaceIndex(leftFaceIndex(colorFaceU));
            colorFace = edgesU[i][2];
            left = leftFaceIndex(colorFace);
            right = rightFaceIndex(colorFace);
            opp = leftFaceIndex(left);
            if (colorFaceH == 1)
            {
                aux = 2;
            }
            else
            {
                aux = 0;
            }

            if (distU == 2 &&
                facesH[colorFaceH][0][aux] == WHITE &&
                facesH[colorFaceH][1][aux] == WHITE &&
                facesH[colorFaceH][2][aux] == WHITE &&
                numCorrectColorsFace(cube->D) == 6)
            {
                return 6;
            }
            else if (distH == 2 &&
                     facesH[colorFaceH][1][aux] == WHITE &&
                     facesH[colorFaceH][2][aux] == WHITE &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 5;
            }
            else if (distH == 2 &&
                     facesH[oppU][0][aux] == WHITE &&
                     facesH[colorFaceH][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 4;
            }
            else if (distU == 2 &&
                     facesH[colorFaceH][0][aux] == WHITE &&
                     facesH[colorFaceU][0][2 - aux] == edgesU[i][0] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 3;
            }
            else if (distU == 2 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][0][2 - aux] == WHITE &&
                     facesH[oppU][0][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 2;
            }
            else if (distH == 0 &&
                     facesH[colorFaceU][1][2 - aux] == WHITE &&
                     facesH[colorFaceU][2][2 - aux] == WHITE &&
                     facesH[colorFaceH][0][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][1][aux] == edgesU[i][1] &&
                     facesH[colorFaceH][2][aux] == edgesU[i][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 1;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[left][1][2] == WHITE &&
                     facesH[left][2][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][0] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[right][1][0] == WHITE &&
                     facesH[right][2][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][1][2] == facesH[colorFace][1][1] &&
                     facesH[colorFace][2][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 15;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     facesH[colorFace][1][2] == WHITE &&
                     facesH[colorFace][2][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 14;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 13;
            }
            else if (facesH[left][0][2] == WHITE &&
                     facesH[colorFace][0][0] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[right][0][0] == WHITE &&
                     facesH[colorFace][0][2] == facesH[colorFace][1][1] &&
                     numCorrectColorsFace(cube->D) == 8)
            {
                return 12;
            }
            else if (facesH[colorFace][1][0] == WHITE &&
                     facesH[colorFace][2][0] == WHITE &&
                     facesH[left][0][0] == WHITE &&
                     facesH[left][1][2] == facesH[left][1][1] &&
                     facesH[left][2][2] == facesH[left][1][1] &&
                     facesH[opp][0][2] == facesH[left][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[colorFaceH][1][2] == WHITE &&
                     facesH[colorFaceH][2][2] == WHITE &&
                     facesH[right][0][2] == WHITE &&
                     facesH[right][1][0] == facesH[right][1][1] &&
                     facesH[right][2][0] == facesH[right][1][1] &&
                     facesH[opp][0][0] == facesH[right][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 11;
            }
            else if (facesH[left][0][0] == WHITE &&
                     facesH[left][1][0] == WHITE &&
                     facesH[left][2][0] == WHITE &&
                     facesH[opp][0][2] == facesH[opp][1][1] &&
                     facesH[opp][1][2] == facesH[opp][1][1] &&
                     facesH[opp][2][2] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else if (facesH[right][0][2] == WHITE &&
                     facesH[right][1][2] == WHITE &&
                     facesH[right][2][2] == WHITE &&
                     facesH[opp][0][0] == facesH[opp][1][1] &&
                     facesH[opp][1][0] == facesH[opp][1][1] &&
                     facesH[opp][2][0] == facesH[opp][1][1] &&
                     numCorrectColorsFace(cube->D) == 6)
            {
                return 10;
            }
            else
            {
                return 150;
            }
        }
    }

    return 150;
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
                return 10;
            }
            else
            {
                return 11;
            }
        }
        else if (facesH[right][1][0] == WHITE &&
                 facesH[right][2][0] == WHITE &&
                 facesH[opp][0][0] == WHITE)
        {
            if (facesH[face][1][0] == WHITE &&
                facesH[face][2][0] == WHITE)
            {
                return 9;
            }
            else
            {
                return 8;
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
    int aux, extraH, left, oppWhiteGoalFace, dist, cornerSteps, count, color, colorFace, correctColors, whiteCornerFace, whiteGoalFace, mateCornerFace;

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
        oppWhiteGoalFace = leftFaceIndex(leftFaceIndex(whiteGoalFace));
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
            extraH = 10;
            if (correctColors == 2)
            {
                extraH = 0;
            }

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
        if (isCornerCorrectlyPos(colorsToCheck[i], corners[i]))
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

    if (aux != 1)
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
            if (facesH[left][0][0] == WHITE)
            {
                return 14 + extraH;
            }
            else if (facesH[whiteFormFace][0][0] == WHITE)
            {
                return 13 + extraH;
            }
        }
    }

    return 60;
}

int RubikSolver::toSolvedHeuristic(Rubik *cube)
{
    int dist, color, colorFace;
    int value = 0;

    int colors[4] = {31, 32, 35, 34};
    int colorsToCheck[4][4] = {
        {YELLOW, cube->B[0][1], cube->L[0][1], YELLOW},
        {YELLOW, cube->B[0][1], cube->R[0][1], YELLOW},
        {YELLOW, cube->F[0][1], cube->L[0][1], YELLOW},
        {YELLOW, cube->F[0][1], cube->R[0][1], YELLOW}};
    int corners[4][3] = {
        {cube->U[0][0], cube->L[0][0], cube->B[0][2]},
        {cube->U[0][2], cube->B[0][0], cube->R[0][2]},
        {cube->U[2][0], cube->F[0][0], cube->L[0][2]},
        {cube->U[2][2], cube->R[0][0], cube->F[0][2]}};

    bool redCheck = cube->F[1][0] == RED && cube->F[2][0] == RED && cube->F[2][1] == RED;
    if (isCornerCorrectlyPos(colorsToCheck[0], corners[0]))
    {
        if (corners[0][1] == YELLOW)
        {
            value += 10;
        }
        else if (corners[0][2] == YELLOW)
        {
            value += 18;
        }
    }
    else
    {
        return 360;
    }

    if (cube->U[1][2] == YELLOW)
    {
        if (isCornerCorrectlyPos(colorsToCheck[1], corners[1]))
        {
            if (corners[1][1] == YELLOW)
            {
                value += 9;
            }
            else if (corners[1][2] == YELLOW)
            {
                value += 17;
            }
        }
        else
        {
            return 360;
        }
    }
    else if (cube->F[1][2] != YELLOW)
    {
        return 360;
    }

    if (isCornerCorrectlyPos(colorsToCheck[2], corners[2]))
    {
        if (corners[2][1] == YELLOW)
        {
            value += 9;
        }
        else if (corners[2][2] == YELLOW)
        {
            value += 17;
        }
    }
    else
    {
        return 360;
    }

    if (cube->F[1][2] == YELLOW)
    {
        colorsToCheck[3][1] = cube->R[1][0];
        colorsToCheck[3][2] = cube->B[0][1];
        if (isCornerCorrectlyPos(colorsToCheck[3], corners[3]))
        {
            if (corners[3][1] == YELLOW)
            {
                value += 17;
            }
            else if (corners[3][0] == YELLOW)
            {
                value += 9;
            }
        }
        else
        {
            return 360;
        }
    }

    if (cube->U[0][1] == YELLOW &&
        cube->U[1][0] == YELLOW &&
        cube->U[2][1] == YELLOW)
    {
        if (cube->U[1][2] == YELLOW)
        {
            if (cube->F[0][2] == YELLOW && redCheck)
            {
                value += 16;
            }
            else if (cube->D[0][0] == YELLOW && !redCheck)
            {
                value += 13;
            }
            else if (cube->D[0][2] == YELLOW && redCheck)
            {
                value += 12;
            }
            else if (cube->R[0][0] == YELLOW && !redCheck)
            {
                value += 9;
            }
            else if (cube->R[0][0] == YELLOW && redCheck)
            {
                value += 8;
            }
            else if (cube->F[2][0] == YELLOW)
            {
                value += 5;
            }
            else if (cube->R[2][0] == YELLOW && redCheck)
            {
                value += 4;
            }
            else if (cube->U[2][2] == YELLOW && !redCheck)
            {
                value += 1;
            }
            else if (cube->U[2][2] != YELLOW || !redCheck)
            {
                return 360;
            }
        }
        else if (cube->F[1][2] == YELLOW)
        {
            if (cube->D[0][2] == YELLOW && redCheck)
            {
                value += 15;
            }
            else if (cube->D[0][0] == YELLOW)
            {
                value += 14;
            }
            else if (cube->B[2][0] == YELLOW && redCheck)
            {
                value += 11;
            }
            else if (cube->R[2][0] == YELLOW && !redCheck)
            {
                value += 10;
            }
            else if (cube->R[2][0] == YELLOW && redCheck)
            {
                value += 7;
            }
            else if (cube->F[2][0] == YELLOW)
            {
                value += 6;
            }
            else if (cube->R[2][2] == YELLOW && redCheck)
            {
                value += 3;
            }
            else if (cube->F[2][2] == YELLOW)
            {
                value += 2;
            }
        }
        else
        {
            return 360;
        }
    }
    else
    {
        return 360;
    }

    return value;
}

int RubikSolver::numCorrectColorsFace(int **face)
{
    int count = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (face[i][j] == face[1][1])
            {
                count++;
            }
        }
    }
    return count;
}

bool RubikSolver::isEdgeInPos(int *colorsToCheck, int *edge)
{
    for (int i = 0; i < 2; i++)
    {
        if (getIndex(colorsToCheck, edge[i]) == -1)
        {
            return false;
        }
    }
    return true;
}

bool RubikSolver::isCornerCorrectlyPos(int *colorsToCheck, int *corner)
{
    for (int i = 0; i < 3; i++)
    {
        if (getIndex(colorsToCheck, corner[i]) == -1)
        {
            return false;
        }
    }

    return true;
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