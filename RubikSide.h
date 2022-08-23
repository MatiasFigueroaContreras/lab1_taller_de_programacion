class RubikSide
{
private:
    int** side;
public:
    RubikSide(int color);
    ~RubikSide();
    void rotate(int direction);
    void changeRowColor(int colors[3], int row);
    void changeColColor(int colors[3], int col);
    void fill(int color);
    bool isSameColor();
    int get(int i, int j);
    int *getRow(int row);
    int *getCol(int col);
};
