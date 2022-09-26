#include <iostream>
#include "RubikSolver.h"

int main(){
    clock_t ti, tf;
    double dt = 0, tavg = 0;
    int N = 0;

    RubikSolver *solver;
    Rubik *cube;

    std::cout << "Ingrese cantidad de ciclos: ";
    std::cin >> N;
    std::cout << "Se ejecutaran " << N << " ciclos" << std::endl;
    for (int i = 0; i < N; i++)
    {
        ti = clock();
        cube = new Rubik();
        cube->disarm(1000);
        solver = new RubikSolver();
        solver->solve(cube);
        tf = clock();
        dt = (tf - ti) / (double)CLOCKS_PER_SEC;
        tavg += dt;
        std::cout << "Tiempo de ejecucion: " << dt << " segundos" << std::endl;
    }
    std::cout << "Tiempo promedio: " << tavg / N << " segundos" << std::endl;
    return 0;
}
