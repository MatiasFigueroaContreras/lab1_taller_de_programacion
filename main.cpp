#include <ctime>
#include "RubikSolver.h"

/*
    Se mide el tiempo que se demora en resolver
        el cubo Rubik
*/
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
        cube = new Rubik();
        cube->disarm(1000);
        std::cout << "Cubo a resolver: " << std::endl;
        cube->print();
        solver = new RubikSolver();
        ti = clock();
        solver->solve(cube);
        tf = clock();
        dt = (tf - ti) / (double)CLOCKS_PER_SEC;
        tavg += dt;
        std::cout << "Tiempo de ejecucion: " << dt << " segundos" << std::endl;
    }
    std::cout << "Tiempo promedio: " << tavg / N << " segundos" << std::endl;
    return 0;
}
