#include "RubikSide.h"

RubikSide::RubikSide(int color){
    side = new int*[3];
    for (int i = 0; i < 3; i++)
    {
        side[i] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            side[i][j] = color;
        }
    }
}

void RubikSide::rotate(int dir){
    int** rotatedSide = new int*[3];
    int x = -1 * (dir - 1);
    int y = dir + 1;
    for (int i = 0; i < 3; i++)
    {
        rotatedSide[x - i * (x - 1)] = new int[3];
        for (int j = 0; j < 3; j++)
        {
            rotatedSide[x - i * (x - 1)][y - j * (y - 1)] = side[j][i];
        }
    }
    
    side = rotatedSide;
}

void RubikSide::changeRowColor(int colors[3], int row)
{
    side[row] = colors;
}

void RubikSide::changeColColor(int colors[3], int col)
{
    for(int i = 0; i < 3; i++)
    {
        side[i][col] = colors[i];
    }
}

void RubikSide::fill(int color){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; i++){
            side[i][j] = color;
        }
    }
}

bool RubikSide::isSameColor(){
    int color = side[0][0];
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(color != side[i][j]){
                return false;
            }
        }
    }
    return true;
}

int RubikSide::get(int i, int j){
    return side[i][j];
}

int *RubikSide::getRow(int row)
{
    return side[row];
}

int *RubikSide::getCol(int col)
{
    int *r = new int[3];
    for(int i = 0; i < 3; i++){
        r[i] = side[i][col];
    }

    return r;
}