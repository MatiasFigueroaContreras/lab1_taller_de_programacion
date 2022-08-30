#include "Rubik.h"


Rubik::Rubik(){
    U = new int*[3];
    D = new int*[3]; 
    L = new int*[3];
    R = new int*[3];
    F = new int*[3];
    B = new int*[3];
    for (int i = 0; i < 3; i++)
    {
        U[i] = new int [3];
        D[i] = new int [3];
        L[i] = new int [3];
        R[i] = new int [3];
        F[i] = new int [3];
        B[i] = new int [3];
        for (int j = 0; j < 3; j++)
        {
            U[i][j] = YELLOW;
            D[i][j] = WHITE;
            L[i][j] = BLUE;
            R[i][j] = GREEN;
            F[i][j] = RED;
            B[i][j] = ORANGE;
        }
    }
}

Rubik::~Rubik()
{
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

bool Rubik::equals(Rubik *r)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (U[i][j] != r->U[i][j] ||
                D[i][j] != r->D[i][j] ||
                L[i][j] != r->L[i][j] ||
                R[i][j] != r->R[i][j] ||
                F[i][j] != r->F[i][j] ||
                B[i][j] != r->B[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

Rubik *Rubik::rotate(int cw, char face){
    Rubik *r = new Rubik();
    for (int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++){
            r->U[i][j] = U[i][j];
            r->D[i][j] = D[i][j];
            r->L[i][j] = L[i][j];
            r->R[i][j] = R[i][j];
            r->F[i][j] = F[i][j];
            r->B[i][j] = B[i][j];
        }
    }

    int ***nFaces = new int **[4];
    int ***oFaces = new int **[4];

    switch (face)
    {
    case 'U':
        rotateFace(cw, r->U, U);
        nFaces[0] = r->F;
        nFaces[1] = r->R;
        nFaces[2] = r->B;
        nFaces[3] = r->L;

        oFaces[0] = F;
        oFaces[1] = R;
        oFaces[2] = B;
        oFaces[3] = L;
        rotateAroundHorizontal(cw, nFaces, oFaces, 0);
        break;
    case 'D':
        rotateFace(cw, r->D, D);
        nFaces[0] = r->F;
        nFaces[1] = r->R;
        nFaces[2] = r->B;
        nFaces[3] = r->L;

        oFaces[0] = F;
        oFaces[1] = R;
        oFaces[2] = B;
        oFaces[3] = L;
        rotateAroundHorizontal(cw, nFaces, oFaces, 2);
        break;
    case 'L':
        rotateFace(cw, r->L, L);
        nFaces[0] = r->F;
        nFaces[1] = r->U;
        nFaces[2] = r->B;
        nFaces[3] = r->D;

        oFaces[0] = F;
        oFaces[1] = U;
        oFaces[2] = B;
        oFaces[3] = D;
        rotateAroundVertical(cw, nFaces, oFaces, 0);
        break;
    case 'R':
        rotateFace(cw, r->R, R);
        nFaces[0] = r->F;
        nFaces[1] = r->U;
        nFaces[2] = r->B;
        nFaces[3] = r->D;

        oFaces[0] = F;
        oFaces[1] = U;
        oFaces[2] = B;
        oFaces[3] = D;
        rotateAroundVertical(cw, nFaces, oFaces, 2);
        break;
    case 'F':
        rotateFace(cw, r->F, F);
        for (int i = 0; i < 3; i++)
        {
            r->U[i][2] = R[0][i];
            r->R[0][i] = D[i][0];
            r->D[i][0] = L[2][i];
            r->L[2][i] = U[i][2];
        }
        break;
    case 'B':
        rotateFace(cw, r->B, B);
        for (int i = 0; i < 3; i++)
        {
            r->U[i][0] = R[2][i];
            r->R[2][i] = D[i][2];
            r->D[i][2] = L[0][i];
            r->L[0][i] = U[i][0];
        }
        break;
    default:
        return nullptr;
        break;
    }

    return r;
}

void Rubik::rotateFace(int cw, int **nface, int **oface)
{
    int x = -1 * (cw - 1);
    int y = cw + 1;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            nface[x - i * (x - 1)][y - j * (y - 1)] = oface[j][i];
        }
    }
}

void Rubik::rotateAroundHorizontal(int cw, int ***nFaces, int ***oFaces, int i)
{
    int x = (cw + 1)/2;
    int y = (-1*cw + 1)/2;
    for(int j = 0; j < 3; j++){
        for(int k = 0; k < 3; k++){
            nFaces[j + y][i][k] = oFaces[j + x][i][k];
        }
    }

    for (int k = 0; k < 3; k++)
    {
        nFaces[3*x][i][k] = oFaces[3*y][i][k];
    }
}

void Rubik::rotateAroundVertical(int cw, int ***nFaces, int ***oFaces, int i)
{
    // int z = i/2;
    // int x = (cw + 1) / 2 - z*cw;
    // int y = (-1 * cw + 1) / 2 + z*cw;
    int z = 1 - i/2;
    int p = (-1 * cw + 1) / 2;
    int t = (cw + 1) / 2;
    int x = p + z * cw;
    int y = t - z * cw;


    for (int k = 0; k < 3; k++)
    {
        nFaces[3 * x][k][i] = oFaces[3 * y][k][i];
        nFaces[y][k][i] = oFaces[x][k][i];
        nFaces[y + 1][k][i*z + 2*p] = oFaces[x + 1][2 - k][i*z + 2*t];
        nFaces[y + 2][k][i*z + 2*t] = oFaces[x + 2][2 - k][i*z + 2*p];
    }
}

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

void Rubik::printFace(int **face){
    for (int i = 0; i < 3; i++)
    {
        std::cout << "   ";
        for (int j = 0; j < 3; j++)
        {
            std::cout << "\033[1;" << face[i][j] << "m[=]\033[0m" << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
