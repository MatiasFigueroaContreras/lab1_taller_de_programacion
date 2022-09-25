#include "HashTable.h"
#include "MinHeap.h"

class RubikSolver
{
private:
    bool stopPoint(Rubik *cube, int step);
    bool whiteCross(Rubik *cube);
    bool whiteComplete(Rubik *cube);
    bool middleComplete(Rubik *cube);
    bool yellowCross(Rubik *cube);
    bool correctYellowCross(Rubik *cube);
    bool wellPosYellowCorners(Rubik *cube);

    int whiteCrossHeuristic(Rubik *cube);
    int whiteCompleteHeuristic(Rubik *cube);
    int middleCompleteHeuristic(Rubik *cube);
    int yellowCrossHeuristic(Rubik *cube);
    int correctYellowCrossHeuristic(Rubik *cube);
    int wellPosYellowCornersHeuristic(Rubik *cube);
    int toSolvedHeuristic(Rubik *cube);

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
