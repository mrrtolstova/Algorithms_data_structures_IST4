#include <iostream>
#include "board.h"
int main()
{
    Board board;
    board.PrintBoard();
    board.Input();
    board.PrintBoard();
    board.Answer();
    board.PrintBoard();
    return 0;
}
