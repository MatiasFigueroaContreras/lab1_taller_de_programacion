#include "RubikSide.h"

class RubikCube
{
private:
    /* data */
    RubikSide *up;    // U
    RubikSide *down;  // D
    RubikSide *right; // R
    RubikSide *left;  // L
    RubikSide *front; // F
    RubikSide *back;  // B
    
public:
    RubikCube();
    ~RubikCube();
    void move(int direction, char side);
    void disarm();
    bool isArm();
};
