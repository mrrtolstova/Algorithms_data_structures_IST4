#ifndef BOARD_H
#define BOARD_H

#include "cell.h"

class Board
{
public:
    Board();
    ~Board();
    void PrintBoard();
    void Clear();
    bool Solution();
    void Answer();
    void Input();
private:
    int* mData;
    int count_of_val;
    int* pos_of_val_X;
    int* pos_of_val_Y;
    int mSize_of_board;
    Cell** mBoard;
};

#endif // BOARD_H
