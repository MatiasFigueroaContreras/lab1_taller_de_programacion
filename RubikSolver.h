#include "HashTable.h"
#include "MinHeap.h"

class RubikSolver
{
private:
    bool stopPoint(Rubik *cube, int step);
    bool whiteCross(Rubik *cube);
    bool whiteComplete(Rubik *cube);
    bool middleComplete(Rubik *cube);
    bool edgeRedBlue(Rubik *cube);
    bool edgeRedGreen(Rubik *cube);
    bool edgeOrangeBlue(Rubik *cube);
    bool edgeOrangeGreen(Rubik *cube);
    bool yellowCross(Rubik *cube);
    bool correctYellowCross(Rubik *cube);
    bool wellPosYellowCorners(Rubik *cube);

    int whiteCrossHeuristic(Rubik *cube);
    int whiteCompleteHeuristic(Rubik *cube);
    int middleCompleteHeuristic(Rubik *cube);
    int edgeRedBlueHeuristic(Rubik *cube);
    int edgeRedGreenHeuristic(Rubik *cube);
    int edgeOrangeBlueHeuristic(Rubik *cube);
    int edgeOrangeGreenHeuristic(Rubik *cube);
    int yellowCrossHeuristic(Rubik *cube);
    int correctYellowCrossHeuristic(Rubik *cube);
    int wellPosYellowCornersHeuristic(Rubik *cube);
    int toSolvedHeuristic(Rubik *cube);

    int numCorrectColorsFace(int **face);
    bool isEdgeInPos(int *colorsToCheck, int *edge);
    bool isCornerCorrectlyPos(int *colorsToCheck, int *corners);
    int yellowLineForm(Rubik *cube);
    int yellowSeatedForm(Rubik *cube);
    int getIndex(int arr[4], int val);
    int leftFaceIndex(int i);
    int rightFaceIndex(int i);
    int distance(int i, int j);

public:
    RubikSolver();
    ~RubikSolver();
    void solve(Rubik *cube);
    State *partialSolve(State *startingState, int step);
    int heuristicValue(Rubik *cube, int step);
};
