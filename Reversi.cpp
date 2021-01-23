#include <iostream>
#include "Board.h"

int main()
{
    Board board;
    board.Print();
    board.PlacePiece(2, 4, 0);
    board.Print();
    board.PlacePiece(2, 5, 1);
    board.Print();
    board.PlacePiece(5, 5, 1);
    board.Print();

}