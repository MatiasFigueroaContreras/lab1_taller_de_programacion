#ifndef RUBIK_H
#define RUBIK_H
#include <iostream>
#define YELLOW 33;
#define WHITE 37;
#define BLUE 34;
#define GREEN 32;
#define RED 31;
#define ORANGE 35;

class Rubik
{
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
    void disarm();
    Rubik *copy();
    int getValue();
    void print();
    bool isSolved();
    bool equals(Rubik *r);

private:
    void rotateFace(int cw, int **nFace, int **oFace);
    void rotateAround(int cw, int **list);
    void rotateAroundHorizontal(int cw, int ***nFaces, int ***oFaces, int i);
    void rotateAroundVertical(int cw, int ***nFaces, int ***oFaces, int i);
    void rotateAroundFrontal(int cw, int ***nFaces, int ***oFaces);
    void rotateAroundBack(int cw, int ***nFaces, int ***oFaces);
    void printFace(int **face);
};
#endif
