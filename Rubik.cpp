#include "Rubik.h"
/*
    Descripcion de la clase Rubik:
    Esta clase representa un cubo Rubik, y esta
    implementada mediante matrices para cada una
    de las caras del cubo:
    -U -> UP
    -D -> Down
    -L -> Left
    -R -> Right
    -F -> Front
    -B -> Back
    esta clase permite principalmente realizar
    los movimientos que permite el cubo Rubik,
    girando alguna de las caras en sentido del
    reloj (estipulado con el valor 1), o en
    contra del sentido del reloj (con el valor -1).
    Ademas, permite imprimir la representacion de
    este, desarmarlo, consultar si esta resuelto,
    consultar si es igual a otro cubo dado, copiar
    el cubo y obtener su valor entero representativo.
*/

/*
    Metodo: Constructor
    Descripcion: este metodo permite crear un cubo Rubik armado de
        partida.
    Retorno: La direccion del objeto creado.
*/
Rubik::Rubik(){
    U = new int*[3];
    D = new int*[3]; 
    L = new int*[3];
    R = new int*[3];
    F = new int*[3];
    B = new int*[3];
    for (int i = 0; i < 3; i++){
        U[i] = new int [3];
        D[i] = new int [3];
        L[i] = new int [3];
        R[i] = new int [3];
        F[i] = new int [3];
        B[i] = new int [3];
        for (int j = 0; j < 3; j++){
            U[i][j] = YELLOW;
            D[i][j] = WHITE;
            L[i][j] = BLUE;
            R[i][j] = GREEN;
            F[i][j] = RED;
            B[i][j] = ORANGE;
        }
    }
}

/*
    Metodo: Destructor
    Descripcion: este metodo permite eliminar el Rubik,
        liberando la memoria en donde se encuentran los
        valores de este.
    Retorno: vacio.
*/
Rubik::~Rubik(){
    for(int i = 0; i < 3; i++){
        delete[] U[i];
        delete[] D[i];
        delete[] L[i];
        delete[] R[i];
        delete[] F[i];
        delete[] B[i];
    }
    delete[] U;
    delete[] D;
    delete[] L;
    delete[] R;
    delete[] F;
    delete[] B;
}

/*
    Metodo:
    Descripcion: este metodo rota una cara del cubo Rubik
        segun la cara y el sentido de rotacion de este.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
    Retorno: cubo Rubik rotado.
*/
Rubik *Rubik::rotate(int cw, char face){
    Rubik *cube = copy();

    int ***nFaces = new int **[4];
    int ***oFaces = new int **[4];

    switch (face){
    case 'U':
        rotateFace(cw, cube->U, U);
        nFaces[0] = cube->F;
        nFaces[1] = cube->R;
        nFaces[2] = cube->B;
        nFaces[3] = cube->L;

        oFaces[0] = F;
        oFaces[1] = R;
        oFaces[2] = B;
        oFaces[3] = L;
        rotateAroundHorizontal(cw, nFaces, oFaces, 0);
        break;
    case 'D':
        rotateFace(cw, cube->D, D);
        nFaces[0] = cube->F;
        nFaces[1] = cube->R;
        nFaces[2] = cube->B;
        nFaces[3] = cube->L;

        oFaces[0] = F;
        oFaces[1] = R;
        oFaces[2] = B;
        oFaces[3] = L;
        rotateAroundHorizontal(cw*-1, nFaces, oFaces, 2);
        break;
    case 'L':
        rotateFace(cw, cube->L, L);
        nFaces[0] = cube->F;
        nFaces[1] = cube->U;
        nFaces[2] = cube->B;
        nFaces[3] = cube->D;

        oFaces[0] = F;
        oFaces[1] = U;
        oFaces[2] = B;
        oFaces[3] = D;
        rotateAroundVertical(cw, nFaces, oFaces, 0);
        break;
    case 'R':
        rotateFace(cw, cube->R, R);
        nFaces[0] = cube->F;
        nFaces[1] = cube->U;
        nFaces[2] = cube->B;
        nFaces[3] = cube->D;

        oFaces[0] = F;
        oFaces[1] = U;
        oFaces[2] = B;
        oFaces[3] = D;
        rotateAroundVertical(cw, nFaces, oFaces, 2);
        break;
    case 'F':
        rotateFace(cw, cube->F, F);
        nFaces[0] = cube->U;
        nFaces[1] = cube->R;
        nFaces[2] = cube->D;
        nFaces[3] = cube->L;

        oFaces[0] = U;
        oFaces[1] = R;
        oFaces[2] = D;
        oFaces[3] = L;
        rotateAroundFrontal(cw, nFaces, oFaces);
        break;
    case 'B':
        rotateFace(cw, cube->B, B);
        nFaces[0] = cube->U;
        nFaces[1] = cube->R;
        nFaces[2] = cube->D;
        nFaces[3] = cube->L;

        oFaces[0] = U;
        oFaces[1] = R;
        oFaces[2] = D;
        oFaces[3] = L;
        rotateAroundBack(cw, nFaces, oFaces);
        break;
    default:
        return nullptr;
        break;
    }
    delete [] nFaces;
    delete [] oFaces;

    return cube;
}

/*
    Metodo:
    Descripcion: este metodo rota una cara dada, segun los
        valores de la antigua cara.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
        -nFace: direccion de la cara que tendra los valores
            rotados.
        -oFace: direccion de la cara antes de la rotacion,
            la cual es utilizada para pasar los valores
            a la cara que se rotara.
    Retorno: vacio.
*/
void Rubik::rotateFace(int cw, int **nface, int **oface){
    int x = -1 * (cw - 1);
    int y = cw + 1;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            nface[x - i * (x - 1)][y - j * (y - 1)] = oface[j][i];
        }
    }
}

/*
    Metodo:
    Descripcion: este metodo rota los cubos alrededor de la
        cara a rotar horizontalmente en un sentido dado, 
        recibiendo las caras a cambiar y las caras antiguas,
        ademas de la posicion a rotar.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
        -nFace: direccion de las caras que tendra los valores
            rotados.
        -oFace: direccion de la cara antes de la rotacion,
            la cual es utilizada para pasar los valores
            a las caras que se rotara.
        -i: posicion de los cubos a rotar.
    Retorno: vacio.
*/
void Rubik::rotateAroundHorizontal(int cw, int ***nFaces, int ***oFaces, int i){
    //Valores para rotar en el sentido dado.
    int x = (cw + 1)/2;
    int y = (-1*cw + 1)/2;
    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
            nFaces[j + y][i][k] = oFaces[j + x][i][k];
        }
    }

    for (int k = 0; k < 3; k++){
        nFaces[3*x][i][k] = oFaces[3*y][i][k];
    }
}

/*
    Metodo:
    Descripcion: este metodo rota los cubos alrededor de la
        cara a rotar verticalmente en un sentido dado,
        recibiendo las caras a cambiar y las caras antiguas,
        ademas de la posicion a rotar.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
        -nFace: direccion de las caras que tendra los valores
            rotados.
        -oFace: direccion de la cara antes de la rotacion,
            la cual es utilizada para pasar los valores
            a las caras que se rotara.
        -i: posicion de los cubos a rotar.
    Retorno: vacio.
*/
void Rubik::rotateAroundVertical(int cw, int ***nFaces, int ***oFaces, int i){
    //Valores para rotar en el sentido dado, 
    // y la posicion correcta de las caras
    int z = 1 - i/2;
    int p = (-1 * cw + 1) / 2;
    int t = (cw + 1) / 2;
    int x = p + z * cw;
    int y = t - z * cw;

    for (int k = 0; k < 3; k++){
        nFaces[y][k][i] = oFaces[x][k][i];
        nFaces[y + 1][k][i*z + 2*p] = oFaces[x + 1][2 - k][i*z + 2*t];
        nFaces[y + 2][k][i*z + 2*t] = oFaces[x + 2][2 - k][i*z + 2*p];
        nFaces[3 * x][k][i] = oFaces[3 * y][k][i];
    }
}

/*
    Metodo:
    Descripcion: este metodo rota los cubos alrededor de la
        cara frontal en un sentido dado, recibiendo las caras 
        a cambiar y las caras antiguas, ademas de la posicion a rotar.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
        -nFace: direccion de las caras que tendra los valores
            rotados.
        -oFace: direccion de la cara antes de la rotacion,
            la cual es utilizada para pasar los valores
            a las caras que se rotara.
        -i: posicion de los cubos a rotar.
    Retorno: vacio.
*/
void Rubik::rotateAroundFrontal(int cw, int ***nFaces, int ***oFaces){
    int x = (cw + 1) / 2;
    int y = (-1 * cw + 1) / 2;

    for (int k = 0; k < 3; k++){
        nFaces[x][2*y+k*x][k*y] = oFaces[y][2*x+k*y][k*x];
        nFaces[x + 1][(2-k)*y][k*x] = oFaces[y + 1][(2-k)*x][k*y];
        nFaces[x + 2][k*x][2*x+k*y] = oFaces[y + 2][k*y][2*y+k*x];
        nFaces[3 * y][2*x+k*y][2*y+(2-k)*x] = oFaces[3 * x][2*y+k*x][2*x+(2-k)*y];
    }
}

/*
    Metodo:
    Descripcion: este metodo rota los cubos alrededor de la
        cara trasera en un sentido dado, recibiendo las caras
        a cambiar y las caras antiguas, ademas de la posicion a rotar.
    Parametros:
        -cw: sentido de la rotacion, en donde 1 es en
            el sentido del reloj, y -1 contra reloj.
        -nFace: direccion de las caras que tendra los valores
            rotados.
        -oFace: direccion de la cara antes de la rotacion,
            la cual es utilizada para pasar los valores
            a las caras que se rotara.
        -i: posicion de los cubos a rotar.
    Retorno: vacio.
*/
void Rubik::rotateAroundBack(int cw, int ***nFaces, int ***oFaces){
    int x = (cw + 1) / 2;
    int y = (-1 * cw + 1) / 2;

    for (int k = 0; k < 3; k++){
        nFaces[y][k*y][2*y+k*x] = oFaces[x][k*x][2*x+k*y];
        nFaces[y + 1][2*y+(2-k)*x][2*x+k*y] = oFaces[x + 1][2*x+(2-k)*y][2*y+k*x];
        nFaces[y + 2][k*y+2*x][k*x] = oFaces[x + 2][k*x+2*y][k*y];
        nFaces[3 * x][k*x][(2-k)*y] = oFaces[3 * y][k*y][(2-k)*x];
    }
}

/*
    Metodo:
    Descripcion: este metodo desarma el cubo de manera
        aleatoria, aplicando 1000 movimientos.
    Retorno: vacio.
*/
void Rubik::disarm(){
    int randFace, randCw;
    Rubik *temp;
    Rubik *dCube = copy();
    char faces[6] = {'U', 'D', 'L', 'R', 'F', 'B'};
    int cws[2] = {1, -1};

    std::srand(time(NULL));
    for(int i = 0; i < 1000; i++){
        temp = dCube;
        randFace = std::rand() % 6;
        randCw = std::rand() % 2;
        dCube = dCube->rotate(cws[randCw], faces[randFace]);
        delete temp;
    }
    U = dCube->U;
    D = dCube->D;
    L = dCube->L;
    R = dCube->R;
    F = dCube->F;
    B = dCube->B;
}

/*
    Metodo:
    Descripcion: este metodo permite copiar el cubo
    Retorno: la copia del cubo Rubik.
*/
Rubik *Rubik::copy(){
    Rubik *cube = new Rubik();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            cube->U[i][j] = U[i][j];
            cube->D[i][j] = D[i][j];
            cube->L[i][j] = L[i][j];
            cube->R[i][j] = R[i][j];
            cube->F[i][j] = F[i][j];
            cube->B[i][j] = B[i][j];
        }
    }
    return cube;
}

/*
    Metodo:
    Descripcion: este metodo permite obtener un valor
        entero que representa al cubo.
    Retorno: entero que representa al cubo.
*/
int Rubik::getValue(){
    int u = 0, d = 0, l = 0, r = 0, f = 0, b = 0;
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            u += U[i][j];
            d += D[i][j];
            l += L[i][j];
            r += R[i][j];
            f += F[i][j];
            b += B[i][j];
        }
    }
    return u * 1 + d * 2 + l * 3 + r * 4 + f * 5 + b * 6;
}

/*
    Metodo:
    Descripcion: este metodo imprime la representacion
        del cubo Rubik, mostrando por consola las caras
        de este.
    Retorno: vacio.
*/
void Rubik::print(){
    std::cout << "--- UP FACE ---" << std::endl;
    printFace(U);
    std::cout << "--- DOWN FACE ---" << std::endl;
    printFace(D);
    std::cout << "--- LEFT FACE ---" << std::endl;
    printFace(L);
    std::cout << "--- RIGHT FACE ---" << std::endl;
    printFace(R);
    std::cout << "--- FRONT FACE ---" << std::endl;
    printFace(F);
    std::cout << "--- BACK FACE ---" << std::endl;
    printFace(B);
    std::cout << std::endl;
}

/*
    Metodo:
    Descripcion: este metodo imprime por consola una 
        cara dada del cubo Rubik.
    Retorno: vacio.
*/
void Rubik::printFace(int **face){
    for (int i = 0; i < 3; i++){
        std::cout << "   ";
        for (int j = 0; j < 3; j++){
            std::cout << "\033[1;" << face[i][j] << "m[=]\033[0m" << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/*
    Metodo:
    Descripcion: permite saber si el cubo Rubik esta
        resuelto.
    Retorno:
        -true: si el cubo esta resuelto.
        -false: si el cubo no esta resuelto.
*/
bool Rubik::isSolved(){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (U[i][j] != 33 || 
                D[i][j] != 37 ||
                L[i][j] != 34 ||
                R[i][j] != 32 ||
                F[i][j] != 31 ||
                B[i][j] != 35){
                return false;
            }
        }
    }
    return true;
}

/*
    Metodo:
    Descripcion: permite saber si un cubo Rubik dado
        es igual al del objeto que lo llama.
    Parametro:
        -r: cubo Rubik a comparar.
    Retorno:
        -true: si los cubos son iguales.
        -false: si los cubos no son iguales.
*/
bool Rubik::equals(Rubik *r){
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (U[i][j] != r->U[i][j] ||
                D[i][j] != r->D[i][j] ||
                L[i][j] != r->L[i][j] ||
                R[i][j] != r->R[i][j] ||
                F[i][j] != r->F[i][j] ||
                B[i][j] != r->B[i][j]){
                return false;
            }
        }
    }
    return true;
}
