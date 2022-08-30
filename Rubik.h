#include <iostream>

#define YELLOW 33;
#define WHITE 37;
#define BLUE 34;
#define GREEN 32;
#define RED 31;
#define ORANGE 35;

class Rubik{
    public:
        int **U;
        int **D;
        int **L;
        int **R;
        int **F;
        int **B;
        Rubik();
        ~Rubik();
        Rubik *rotate(int cw, char face);
        void print();
        bool equals(Rubik *r);
    private:
        void rotateFace(int cw, int **nFace, int **oFace);
        void rotateAround(int cw, int **list);
        void rotateAroundHorizontal(int cw, int ***nFaces, int ***oFaces, int i);
        void rotateAroundVertical(int cw, int ***nFaces, int ***oFaces, int i);
        void printFace(int **face);
};